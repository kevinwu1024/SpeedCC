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
#include "SCSetting.h"

#include "../cocos/SCCocosDef.h"
#include "../stage/SCStageMacros.h"
#include "../stage/SCMessageDispatch.h"
#include "SCSystem.h"


NAMESPACE_SPEEDCC_BEGIN

SCSetting*       SCSetting::s_pInstance = nullptr;
    
SCSetting* SCSetting::getInstance()
{
    if(s_pInstance==nullptr)
    {
        s_pInstance = new SCSetting();
    }
        
    return s_pInstance;
}
    
SCSetting::SCSetting()
{
}
    
SCWatchInt::Ptr SCSetting::getWatchInt(const SCString& strKey,const int nDefault)
{
    SCASSERT(!strKey.isEmpty());
    SC_RETURN_IF(strKey.isEmpty(), nullptr);
        
    auto it = _key2WatchNumMap.find(strKey);
        
    if(it!=_key2WatchNumMap.end())
    {
        SCASSERT((*it).second!=nullptr);
        return (*it).second.cast<SCWatchInt::Ptr>();
    }
        
    auto nValue = SCCCUserDefault()->getIntegerForKey(strKey,nDefault);
    SCWatchInt::Ptr ret = SCWatchInt::create(nValue);
        
    ret->addUpdateFunc([strKey](SCWatchInt::Ptr ptrWatch,const int nNew,const int nOld)
                            {
                                SCCCUserDefault()->setIntegerForKey(strKey, nNew);
                            });
        
    SCMapInsert(_key2WatchNumMap, strKey, ret);
    return ret;
}
    
    
SCWatchBool::Ptr SCSetting::getWatchBool(const SCString& strKey,const bool bDefault)
{
    SCASSERT(!strKey.isEmpty());
    SC_RETURN_IF(strKey.isEmpty(), nullptr);
        
    auto it = _key2WatchNumMap.find(strKey);
        
    if(it!=_key2WatchNumMap.end())
    {
        SCASSERT((*it).second!=nullptr);
        return (*it).second.cast<SCWatchBool::Ptr>();
    }
        
    bool bValue = SCCCUserDefault()->getBoolForKey(strKey,bDefault);
    auto ret = SCWatchBool::create(bValue);
        
    ret->addUpdateFunc([strKey](SCWatchBool::Ptr ptrWatch,const bool bNew,const bool bOld)
                        {
                            SCCCUserDefault()->setBoolForKey(strKey, bNew);
                            
                            auto strSettingKeySound = SCSystem::getSpeedCCOption(SC_OPTION_KEY_SETTINGKEYOFSOUND).getString();
                            auto strSettingKeyMusic = SCSystem::getSpeedCCOption(SC_OPTION_KEY_SETTINGKEYOFMUSIC).getString();
                            
                            if(strKey==strSettingKeySound)
                            {
                                SCMsgDisp()->postMessage(SCID::Msg::kMsgSettingSoundChanged);
                            }
                            else if(strKey==strSettingKeyMusic)
                            {
                                SCMsgDisp()->postMessage(SCID::Msg::kMsgSettingMusicChanged);
                            }
                        });
        
    SCMapInsert(_key2WatchNumMap, strKey, ret);
    return ret;
}
    
    
SCWatchFloat::Ptr SCSetting::getWatchFloat(const SCString& strKey,const float fDefault)
{
    SCASSERT(!strKey.isEmpty());
    SC_RETURN_IF(strKey.isEmpty(), nullptr);
        
    auto it = _key2WatchNumMap.find(strKey);
        
    if(it!=_key2WatchNumMap.end())
    {
        SCASSERT((*it).second!=nullptr);
        return (*it).second.cast<SCWatchFloat::Ptr>();
    }
        
    auto fValue = SCCCUserDefault()->getFloatForKey(strKey,fDefault);
    auto ret = SCWatchFloat::create(fValue);
        
    ret->addUpdateFunc([strKey](SCWatchFloat::Ptr ptrWatch,const float fNew,const float fOld)
                        {
                            SCCCUserDefault()->setFloatForKey(strKey, fNew);
                        });
        
        
    SCMapInsert(_key2WatchNumMap, strKey, ret);
    return ret;
}
    
SCWatchDouble::Ptr SCSetting::getWatchDouble(const SCString& strKey,const double dDefault)
{
    SCASSERT(!strKey.isEmpty());
    SC_RETURN_IF(strKey.isEmpty(), nullptr);
        
    auto it = _key2WatchNumMap.find(strKey);
        
    if(it!=_key2WatchNumMap.end())
    {
        SCASSERT((*it).second!=nullptr);
        return (*it).second.cast<SCWatchDouble::Ptr>();
    }
        
    auto duValue = SCCCUserDefault()->getDoubleForKey(strKey,dDefault);
    auto ret = SCWatchDouble::create(duValue);
        
    ret->addUpdateFunc([strKey](SCWatchDouble::Ptr ptrWatch,const double dNew,const double dOld)
                        {
                            SCCCUserDefault()->setDoubleForKey(strKey, dNew);
                        });
        
    SCMapInsert(_key2WatchNumMap, strKey, ret);
    return ret;
}
    
SCWatchString::Ptr SCSetting::getWatchString(const SCString& strKey)
{
    SCASSERT(!strKey.isEmpty());
    SC_RETURN_IF(strKey.isEmpty(), nullptr);
        
    auto it = _key2WatchNumMap.find(strKey);
        
    if(it!=_key2WatchNumMap.end())
    {
        SCASSERT((*it).second!=nullptr);
        return (*it).second.cast<SCWatchString::Ptr>();
    }
        
    auto strValue = SCCCUserDefault()->getStringForKey(strKey);
    auto ret = SCWatchString::create(strValue);
        
    ret->addUpdateFunc([strKey](SCWatchString::Ptr ptrWatch,const SCString& strNew,const SCString& strOld)
                        {
                            SCCCUserDefault()->setStringForKey(strKey, strNew.c_str());
                        });
        
        
    SCMapInsert(_key2WatchNumMap, strKey, ret);
    return ret;
}
    
SCWatchBool::Ptr SCSetting::getSoundWatch(const bool bDefault)
{
    auto strSettingKeySound = SCSystem::getSpeedCCOption(SC_OPTION_KEY_SETTINGKEYOFSOUND).getString();
    return this->getWatchBool(strSettingKeySound,bDefault);
}
    
SCWatchBool::Ptr SCSetting::getMusicWatch(const bool bDefault)
{
    auto strSettingKeyMusic = SCSystem::getSpeedCCOption(SC_OPTION_KEY_SETTINGKEYOFMUSIC).getString();
    return this->getWatchBool(strSettingKeyMusic,bDefault);
}
    
void SCSetting::flush()
{
    SCCCUserDefault()->flush();
}
    
SCDictionary SCSetting::asDictionary()
{
    SCDictionary ret;
        
    for(auto it : _key2WatchNumMap)
    {
        auto v1 = it.second.cast<SCWatchInt::Ptr>();
        if(v1!=nullptr)
        {
            ret.setValue(it.first,v1->getValue());
            continue;
        }
            
        auto v2 = it.second.cast<SCWatchString::Ptr>();
        if(v2!=nullptr)
        {
            ret.setValue(it.first,v2->getValue());
            continue;
        }
            
        auto v3 = it.second.cast<SCWatchBool::Ptr>();
        if(v3!=nullptr)
        {
            ret.setValue(it.first,v3->getValue());
            continue;
        }
            
        auto v4 = it.second.cast<SCWatchFloat::Ptr>();
        if(v4!=nullptr)
        {
            ret.setValue(it.first,v4->getValue());
            continue;
        }
            
        auto v5 = it.second.cast<SCWatchDouble::Ptr>();
        if(v5!=nullptr)
        {
            ret.setValue(it.first,v5->getValue());
            continue;
        }
            
        SCASSERT(false);
    }
        
    return ret;
        
}

NAMESPACE_SPEEDCC_END


