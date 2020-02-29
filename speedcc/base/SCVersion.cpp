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

#include "SCVersion.h"
#include "SCBaseMacros.h"

NAMESPACE_SPEEDCC_BEGIN

SCVersion::SCVersion()
:nMajor(0)
,nMinor(0)
,nFix(0)
{}
    
SCVersion::SCVersion(const SCVersion& info)
{
    memcpy(this,&info,sizeof(*this));
}
    
SCVersion::SCVersion(const char* pszVersion)
{
    SCASSERT(pszVersion!=nullptr);
    this->setString(pszVersion);
}
    
SCVersion::SCVersion(const SCString& str)
{
    this->setString(str);
}
    
SCVersion::SCVersion(unsigned uVersion)
{
    nMajor = (uVersion&0x00ff0000) >> 16;
    nMinor = (uVersion&0x0000ff00) >> 8;
    nFix = uVersion&0x000000ff;
}
    
SCString SCVersion::getString(int nBit) const
{
    switch(nBit)
    {
        default:
        case 3: return SCString(0,"%d.%d.%d",nMajor,nMinor,nFix);
        case 2: return SCString(0,"%d.%d",nMajor,nMinor);
        case 1: return nMajor;
    }
}
    
unsigned SCVersion::getHexValue(int nBit) const
{
    switch(nBit)
    {
        default:
        case 3: return ((nMajor<<16) | (nMinor<<8) | nFix);
        case 2: return (nMajor<<16 | nMinor<<8);
        case 1: return nMajor<<16;
    }
}
    
int SCVersion::compare(const SCVersion& info) const
{
    int nRet = 0;
        
    do
    {
        nRet = 1;
        SC_BREAK_IF(nMajor>info.nMajor);
        nRet = -1;
        SC_BREAK_IF(nMajor<info.nMajor);
            
        nRet = 1;
        SC_BREAK_IF(nMinor>info.nMinor);
        nRet = -1;
        SC_BREAK_IF(nMinor<info.nMinor);
            
        nRet = 1;
        SC_BREAK_IF(nFix>info.nFix);
        nRet = -1;
        SC_BREAK_IF(nFix<info.nFix);
            
        nRet = 0;
    }
    while(0);
        
    return nRet;
}
    
bool SCVersion::operator<(const SCVersion& info) const
{
    return this->compare(info)<0;
}
    
bool SCVersion::operator<=(const SCVersion& info) const
{
    return this->compare(info)<=0;
}
    
bool SCVersion::operator>(const SCVersion& info) const
{
    return this->compare(info)>0;
}
    
bool SCVersion::operator>=(const SCVersion& info) const
{
    return this->compare(info)>=0;
}
    
bool SCVersion::operator==(const SCVersion& info) const
{
    return this->compare(info)==0;
}
    
void SCVersion::setString(const SCString& strVersion)
{
    memset(this,0,sizeof(*this));
        
    std::vector<SCString> strVor = strVersion.split(".");
        
    switch(strVor.size())
    {
        case 3:
            nMajor = strVor[0].asInt(false,0);
            nMinor = strVor[1].asInt(false,0);
            nFix = strVor[2].asInt(false,0);
            break;
                
        case 2:
            nMajor = strVor[0].asInt(false,0);
            nMinor = strVor[1].asInt(false,0);
            break;
                
        case 1:
            nMajor = strVor[0].asInt(false,0);
            break;
                
        default: break;
    }
}
NAMESPACE_SPEEDCC_END

