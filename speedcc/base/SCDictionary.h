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

#ifndef __SPEEDCC__SCDICTIONARY_H__
#define __SPEEDCC__SCDICTIONARY_H__

#include "SCObjRefT.h"
#include "SCValue.h"

NAMESPACE_SPEEDCC_BEGIN

class SCDictionary
:public SCObjRefT<std::map<SCString,SCValue> >
{
public:
    struct SKVPair
    {
        SCString    strKey;
        SCValue     value;
        
        SKVPair()
        {    
        }
        
        SKVPair(const SCString& key, const SCValue& val):
        strKey(key),
        value(val)
        {
        }
        
        SKVPair(const SKVPair& pair):
        strKey(pair.strKey),
        value(pair.value)
        {
        }
    };
        
public:
	SC_DEFINE_CLASS_PTR(SCDictionary)

    SCDictionary();
    SCDictionary(const SCString& strKey,const SCValue& value);
    SCDictionary(const SKVPair& pair);
    SCDictionary(const SKVPair* pPairArray,const int nCount);
    SCDictionary(const std::vector<SKVPair>& pairVct);
    SCDictionary(const SCString& strJson);
        
    bool loadFromJsonString(const SCString& strJson);
    SCString exportJson(const bool bPrettyPrint=true);
    SCValue& operator[](const SCString& strKey);
    SCValue operator[](const SCString& strKey) const;
        
    void setValue(const SCString& strKey,const SCValue& value);
    void setValue(const SKVPair& pair);
    void setValue(const SKVPair* pPairArray,const int nCount);
    void setValue(const std::vector<SKVPair>& pairVct);
    //void setDictionary(const SCString& strKey,const SCDictionary& dic);
        
    SCValue getValue(const SCString& strKey) const;
    //SCDictionary getDictionary(const SCString& strKey) const;
        
    bool hasKey(const SCString& strKey) const;
    void removeKey(const SCString& strKey);
    void removeAllKeys();
    int getCount() const;
    bool isEmpty() const;
    void forEach(const std::function<bool(const SCString& strKey,const SCValue& value)>& func) const;
    void forEach(const std::function<bool(const SCString& strKey,SCValue& value)>& func);
        
};

NAMESPACE_SPEEDCC_END

#endif //__SPEEDCC__SCDICTIONARY_H__
