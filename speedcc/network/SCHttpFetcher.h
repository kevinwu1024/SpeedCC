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

#ifndef __SPEEDCC__SCHTTPDOWNLOAD_H__
#define __SPEEDCC__SCHTTPDOWNLOAD_H__

#include "../base/SCString.h"
#include "../base/SCDataBlock.h"
#include "../base/SCDictionary.h"

NAMESPACE_SPEEDCC_BEGIN

class SCHttpFetcher
{
public:
    enum class EMethod
    {
        GET,
        POST,
    };
    
    struct SRequestPara
    {
        std::vector<SCString>   headerVtr;
        EMethod                 method;
        SCDictionary            paramDic;
            
        SRequestPara()
        :method(EMethod::GET)
        {
        }
    };
        
public:
    static SCHttpFetcher* getInstance();
        
    int fetchData(const SCString& strURL,
                    const std::function<void(bool,int,SCDataBlock)>& func,
                    const SRequestPara* pPara = nullptr);
        
    int fetchText(const SCString& strURL,
                    const std::function<void(bool,int,SCString)>& func,
                    const SRequestPara* pPara = nullptr);
        
    int fetchJSON(const SCString& strURL,
                    const std::function<void(bool,int,SCDictionary)>& func,
                    const SRequestPara* pPara = nullptr);
        
    static SCString encodingURI(SCString strURI);
protected:
    SCHttpFetcher();
        
    inline int spawnID() { return ++_nIDCounter; }
        
private:
    static SCHttpFetcher*      s_pInstance;
    int                         _nIDCounter;
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCHTTPDOWNLOAD_H__
