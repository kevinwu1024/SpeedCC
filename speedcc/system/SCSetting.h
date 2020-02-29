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

#ifndef __SPEEDCC__SCSETTING_H__
#define __SPEEDCC__SCSETTING_H__

#include "../base/SCWatchNumberT.h"
#include "../base/SCWatchString.h"
#include "../base/SCDictionary.h"


NAMESPACE_SPEEDCC_BEGIN

class SCSetting
{
public:
    SC_AVOID_CLASS_COPY(SCSetting)
        
    static SCSetting* getInstance();
        
    SCWatchInt::Ptr getWatchInt(const SCString& strKey,const int nDefault=0);
    SCWatchBool::Ptr getWatchBool(const SCString& strKey,const bool bDefault=false);
    SCWatchFloat::Ptr getWatchFloat(const SCString& strKey,const float fDefault=0.0f);
    SCWatchDouble::Ptr getWatchDouble(const SCString& strKey,const double dDefault=0.0);
    SCWatchString::Ptr getWatchString(const SCString& strKey);
        
    SCWatchBool::Ptr getSoundWatch(const bool bDefault=true);
    SCWatchBool::Ptr getMusicWatch(const bool bDefault=true);
        
    void flush();
        
    SCDictionary asDictionary();
        
private:
    SCSetting();
        
private:
    std::map<SCString,SCObject::Ptr>        _key2WatchNumMap;
    static SCSetting*                       s_pInstance;
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCSETTING_H__
