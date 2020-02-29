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

#include "SCHttpFetcher.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"
#include "../stage/SCMessageDispatch.h"

using namespace cocos2d::extension;
using namespace cocos2d::network;

NAMESPACE_SPEEDCC_BEGIN

HttpRequest* createRequest(const SCString& strURL,const SCHttpFetcher::SRequestPara* pPara);
std::string url_encode(const std::string &value);
    
SCHttpFetcher*  SCHttpFetcher::s_pInstance = nullptr;
    
SCHttpFetcher::SCHttpFetcher()
:_nIDCounter(0)
{
}
    
SCHttpFetcher* SCHttpFetcher::getInstance()
{
    if(s_pInstance==nullptr)
    {
        s_pInstance = new SCHttpFetcher();
    }
        
    return s_pInstance;
}
    
int SCHttpFetcher::fetchData(const SCString& strURL,
                                    const std::function<void(bool,int,SCDataBlock dataBlock)>& func,
                                    const SRequestPara* pPara)
{
    SC_RETURN_IF(strURL.isEmpty(), -1);
    int nID = this->spawnID();
        
    auto pRequest = createRequest(strURL,pPara);
    pRequest->setResponseCallback([func,nID](HttpClient* client, HttpResponse* response)
                                    {
                                        auto ptrMsg = SCMessage::create();
                                        SCDataBlock data;
                                        bool bSuccess;
                                        if(response->isSucceed())
                                        {
                                            bSuccess = true;
                                            ptrMsg->nMsgID = SCID::Msg::kMsgHttpDownloadCompleted;
                                            auto pDataVtr = response->getResponseData();
                                            if(pDataVtr->size()>0)
                                            {
                                                data.assign(&(*pDataVtr)[0], (int)pDataVtr->size());
                                            }
                                              
                                            ptrMsg->parameters.setValue(SC_KEY_RESULT, data);
                                        }
                                        else
                                        {
                                            bSuccess = false;
                                            ptrMsg->nMsgID = SCID::Msg::kMsgHttpDownloadFailed;
                                        }
                                          
                                        SCMessageDispatch::getInstance()->sendMessage(ptrMsg);
                                          
                                        if(func!=nullptr)
                                        {
                                            func(bSuccess,(int)response->getResponseCode(), data);
                                        }
                                    });
    HttpClient::getInstance()->send(pRequest);
    pRequest->release();
        
    return nID;
}
    
int SCHttpFetcher::fetchText(const SCString& strURL,
                                    const std::function<void(bool,int,SCString strText)>& func,
                                    const SRequestPara* pPara)
{
    SC_RETURN_IF(strURL.isEmpty(), -1);
    return this->fetchData(strURL, [func](bool bSuccess,int nResponseCode,SCDataBlock db)
                                {
                                    if(func)
                                    {
                                        SCString strText;
                                        if(db.getSize()>0)
                                        {
                                            SCString s(db.getDataPtr(),db.getSize());
                                            strText = s;
                                        }
                                        func(bSuccess,nResponseCode,strText);
                                          
                                    }
                                },pPara);
}
    
int SCHttpFetcher::fetchJSON(const SCString& strURL,
                                    const std::function<void(bool,int,SCDictionary dic)>& func,
                                    const SRequestPara* pPara)
{
    SC_RETURN_IF(strURL.isEmpty(), -1);
    return this->fetchText(strURL, [func](bool bSuccess,int nResponseCode,SCString strText)
                                {
                                    if(func)
                                    {
                                        SCDictionary dic(strText);
                                        func(bSuccess,nResponseCode,dic);
                                    }
                                },pPara);
}
    
HttpRequest* createRequest(const SCString& strURL,const SCHttpFetcher::SRequestPara* pPara)
{
    HttpRequest* request = new (std::nothrow) HttpRequest();
    request->setUrl(strURL.c_str());
    if(pPara==nullptr)
    {
        request->setRequestType(HttpRequest::Type::GET);
    }
    else
    {
        request->setRequestType((pPara->method == SCHttpFetcher::EMethod::GET) ? HttpRequest::Type::GET : HttpRequest::Type::POST);
        if(!pPara->headerVtr.empty())
        {// header
            std::vector<std::string> stringVector;
            for(const auto& it : pPara->headerVtr)
            {
                stringVector.push_back(it.c_str());
            }
                
            request->setHeaders(stringVector);
        }
            
        if(!pPara->paramDic.isEmpty())
        {// parameter
            SCString strParam;
            pPara->paramDic.forEach([&strParam] (const SCString& strKey, const SCValue& value) -> bool
                                    {
                                        SCString strEncodedKey = SCHttpFetcher::encodingURI(strKey.c_str());
                                        SCString strEncodedValue = SCHttpFetcher::encodingURI(value.getString().c_str());
                                            
                                        if(strParam.isEmpty())
                                        {
                                            strParam = strEncodedKey + "=" + strEncodedValue;
                                        }
                                        else
                                        {
                                            strParam += "&" + strEncodedKey + "=" + strEncodedValue;
                                        }
                                            
                                        return true;
                                    });
            if(pPara->method == SCHttpFetcher::EMethod::GET)
            { // GET
                auto stringVector = strURL.split("?");
                SCASSERT(stringVector.size()<=2);
                SCString strNewUrl;
                if(stringVector.size()==2)
                {
                    strNewUrl = stringVector[0] + "?" + stringVector[1] + "&" + strParam;
                }
                else
                {
                    strNewUrl = strURL + "?" + strParam;
                }
                    
                request->setUrl(strNewUrl.c_str());
            }
            else
            {// POST
                request->setRequestData(strParam.c_str(), strParam.getLength());
            }
        }
    }
        
    return request;
}
    
SCString SCHttpFetcher::encodingURI(SCString strURI)
{
    SCString strRet;
        
    for(int i=0; i<strURI.getLength(); ++i)
    {
        const char c = strURI[i];
            
        if(::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
        {
            strRet += c;
        }
        else
        {
            SCString str(0,"%%%02X",int((unsigned char) c));
            strRet += str;
        }
    }
        
    return strRet;
}

NAMESPACE_SPEEDCC_END


