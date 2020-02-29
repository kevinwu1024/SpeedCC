/****************************************************************************
 
 Copyright (c) 2017-2020 Kevin Wu (Wu Feng)
 
 github: http://github.com/kevinwu1024
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

#include "cocos2d.h"
#include "SCAssetUtils.h"
#include "../platform/SCOSSystem.h"

#include <stdio.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <Rpc.h>
#pragma comment(lib,"Rpcrt4.lib") 
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <uuid/uuid.h>
#endif

#include "SCSystem.h"

using namespace cocos2d;

NAMESPACE_SPEEDCC_BEGIN

SCString SCAssetUtils::createUUID()
{
    char szUUID[37] = {0};
    
#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
    UUID uuid;
    UuidCreate(&uuid);
    
    unsigned char* str;
    UuidToStringA(&uuid, &str);
    strcpy(szUUID,(char*)str);
    RpcStringFreeA(&str);
#else
    uuid_t uuid;
    uuid_generate_random(uuid);
    uuid_unparse(uuid, szUUID);
#endif
    return szUUID;
}


bool SCAssetUtils::readFile(const SCString& strFile,const std::function<bool(const void*,unsigned int)>& funCallback)
{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    if(strFile[0]!='/')
    {
        SCString androidFullPath = strFile;
        if(androidFullPath.find("assets/")!=0)
        {
            androidFullPath = "assets/" + androidFullPath;
        }
        SCLog("SCAssetUtils::readFile() from apk:%s",androidFullPath.c_str());
        return SCAssetUtils::uncompressFile(::getApkPath(), androidFullPath, funCallback);
    }
#endif
    SCString strFullPathFile = cocos2d::FileUtils::getInstance()->fullPathForFilename(strFile.c_str());
    SCLog("SCAssetUtils::readFile() file:%s",strFullPathFile.c_str());
    SC_RETURN_IF(!FileUtils::getInstance()->isFileExist(strFullPathFile.c_str()), false);
    
    FILE* fHandle = ::fopen(strFullPathFile.c_str(), "r");
    
    if(fHandle)
    {
        //rectrive file length
        fseek(fHandle, 0, SEEK_END);
        const unsigned long nTotalFileLength = (unsigned long)ftell(fHandle);
        rewind(fHandle);
        
        funCallback(NULL,(int)nTotalFileLength);
        
        unsigned char buf[64];
        do
        {
            auto sizeRead = fread(buf,1,sizeof(buf),fHandle);
            SC_BREAK_IF(sizeRead==0);
            SC_BREAK_IF(!funCallback(buf,(unsigned int)sizeRead));
        }while(1);
        
        funCallback(NULL,0xffffffff);
        ::fclose(fHandle);
        return true;
    }
    
    return false;
}

void SCAssetUtils::readFileAsyn(const SCString& strFile,const std::function<bool(const void*,unsigned int)>& funCallback)
{
    auto func = [=]()
    {
        SCAssetUtils::readFileAsyn(strFile,funCallback);
	};

    AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_IO,std::move(func));
}

bool SCAssetUtils::goThroughDirectory(SCString strDirectory,int nMaxDepth,const std::function<bool(const SCString& strFullPathFile,const bool bDirectory)>& funCallback)
{
    SCString strWritablePath = FileUtils::getInstance()->getWritablePath();
    
    if(strDirectory.find(strWritablePath)<0)
    {
        strDirectory = strWritablePath + strDirectory;
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA findFileData;
	bool bLoop = true;

	if ((hFind = ::FindFirstFileA(strDirectory.c_str(), &findFileData)) != INVALID_HANDLE_VALUE)
	{
		do 
		{
			SC_CONTINUE_IF((!strcmp(findFileData.cFileName, ".") || !strcmp(findFileData.cFileName, "..")));

			if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				bLoop = funCallback(findFileData.cFileName, true);
				if (nMaxDepth != 0)
				{
					SCAssetUtils::goThroughDirectory(findFileData.cFileName, nMaxDepth - 1, funCallback);
				}
			}
			else
			{
				bLoop = funCallback(findFileData.cFileName, false);
			}
		} 
		while (::FindNextFileA(hFind, &findFileData));

		::FindClose(hFind);
	}
#else
	DIR *d = opendir(strDirectory);
	SCASSERT(d != 0);
	SC_RETURN_IF(d == 0, false);

	struct dirent *p;
	bool bLoop = true;

	while (bLoop && (p = readdir(d)))
	{
		SC_CONTINUE_IF((!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")));

		SCString strFullPathFile = strDirectory + "/" + p->d_name;

		struct stat statbuf;

		if (!stat(strFullPathFile, &statbuf))
		{
			if (S_ISDIR(statbuf.st_mode))
			{
				bLoop = funCallback(strFullPathFile, true);
				if (nMaxDepth != 0)
				{
					SCAssetUtils::goThroughDirectory(strFullPathFile, nMaxDepth - 1, funCallback);
				}
			}
			else
			{
				bLoop = funCallback(strFullPathFile, false);
			}
		}
	}

	closedir(d);
#endif
    
    return true;
}

void SCAssetUtils::goThroughDirectoryAsyn(SCString strDirectory, int nMaxDepth, const std::function<bool(const SCString& strFullPathFile, const bool bDirectory)>& funCallback)
{
	auto func = [=]()
	{
		SCAssetUtils::goThroughDirectory(strDirectory, nMaxDepth, funCallback);
	};

	AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_IO, std::move(func));
}

bool SCAssetUtils::copyResourceFile2Writable(const SCString& strSourceFile,const SCString& strDestinationFile,const std::function<void(const bool)>& funDoneCallback)
{
    auto func = [=]()
    {
        auto strWriteFile = strDestinationFile;
        auto strWritablePath = FileUtils::getInstance()->getWritablePath();
        
        if(strDestinationFile.find(strWritablePath.c_str())<0)
        {
            strWriteFile = strWritablePath + strWriteFile;
        }
        
        FILE* hWrite = ::fopen(strWriteFile,"w");
        
        SCASSERT(hWrite!=0);
        SC_RETURN_IF(hWrite==0, false);
        
        SCString strResourceFile = strSourceFile;
        if(strSourceFile.find(SCAssetUtils::getResourcePath())!=0)
        {
            strResourceFile = SCAssetUtils::getResourcePath() + strResourceFile;
        }
        
        bool bRet = SCAssetUtils::readFile(strResourceFile, [hWrite](const void* pData,unsigned int nSize)->bool
                                      {
                                          SC_RETURN_IF(pData==NULL, true);
                                          
                                          ::fwrite(pData, 1, nSize, hWrite);
                                          return true;
                                      });
        ::fflush(hWrite);
        ::fclose(hWrite);
        hWrite = 0;
        
        if(!bRet)
        {
            ::remove(strWriteFile);
        }

		if (funDoneCallback != nullptr)
		{
			funDoneCallback(bRet);
		}
        
        return bRet;
    };
    
    if(funDoneCallback == nullptr)
    {
        return func();
    }
    else
    {
        AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_IO, std::move(func));
    }
    
    return true;
}

SCString SCAssetUtils::getResourcePath()
{
	SCString strRet;

	char szPath[256] = { 0 };
	::scGetResourcePath(szPath, SC_ARRAY_LENGTH(szPath));
	if (szPath[strlen(szPath) - 1] != '/')
	{
		strcat(szPath, "/");
	}

	strRet = szPath;

	return strRet;
}

NAMESPACE_SPEEDCC_END


