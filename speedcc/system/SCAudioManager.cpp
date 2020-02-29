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

#include "SCAudioManager.h"
#include "../cocos/SCCocosDef.h"
#include "../stage/SCStageMacros.h"
#include "SimpleAudioEngine.h"
#include "SCSetting.h"

NAMESPACE_SPEEDCC_BEGIN

SCAudioManager*    SCAudioManager::s_pInstance = nullptr;
    
SCAudioManager::SCAudioManager()
:_bMsgProcessing(false)
,_nCurrentMusicIndex(-1)
{
    SCMsgDisp()->addListener(this);
    _ptrWatchSound = SCSetting::getInstance()->getSoundWatch();
    _ptrWatchMusic = SCSetting::getInstance()->getMusicWatch();
}
    
SCAudioManager::~SCAudioManager()
{
    SCMsgDisp()->removeListener(this);
}
    
SCAudioManager* SCAudioManager::getInstance()
{
    if(s_pInstance==nullptr)
    {
        s_pInstance = new SCAudioManager();
    }
        
    return s_pInstance;
}
    
void SCAudioManager::pauseMusic()
{
    SC_RETURN_V_IF(!this->getMusicEnabled());
    SCCCSoundEngine()->pauseBackgroundMusic();
}
    
void SCAudioManager::resumeMusic()
{
    SC_RETURN_V_IF(!this->getMusicEnabled());
    SCCCSoundEngine()->resumeBackgroundMusic();
}
    
void SCAudioManager::pauseSound(const int nID)
{
    SC_RETURN_V_IF(!this->getSoundEnabled());
    SCCCSoundEngine()->pauseEffect(nID);
}
    
void SCAudioManager::resumeSound(const int nID)
{
    SC_RETURN_V_IF(!this->getSoundEnabled());
    SCCCSoundEngine()->resumeEffect(nID);
}
    
void SCAudioManager::stopSound(const int nID)
{
    SCCCSoundEngine()->stopEffect(nID);
}
    
int SCAudioManager::playSound(const SCString& strFile,const bool bLoop)
{
    SC_RETURN_IF(!this->getSoundEnabled(),-1);
    return SCCCSoundEngine()->playEffect(strFile,bLoop);
}
    
void SCAudioManager::playMusic(const SCString& strFile,const bool bLoop)
{
    SC_RETURN_V_IF(!this->getMusicEnabled());
    SCCCSoundEngine()->playBackgroundMusic(strFile,bLoop);
}
    
void SCAudioManager::preloadSound(const SCString& strFile)
{
    SCCCSoundEngine()->preloadEffect(strFile);
}
    
void SCAudioManager::unloadSound(const SCString& strFile)
{
    SCCCSoundEngine()->unloadEffect(strFile);
}
    
void SCAudioManager::preloadMusic(const SCString& strFile)
{
    SCCCSoundEngine()->preloadBackgroundMusic(strFile);
}
    
void SCAudioManager::stopMusic(const bool bRelease)
{
    SCCCSoundEngine()->stopBackgroundMusic(bRelease);
}
    
void SCAudioManager::stopAllSound()
{
    SCCCSoundEngine()->stopAllEffects();
}
    
void SCAudioManager::setMusicVolume(const float fPercent)
{
    SCCCSoundEngine()->setBackgroundMusicVolume(fPercent);
}
    
void SCAudioManager::setSoundVolume(const float fPercent)
{
    SCCCSoundEngine()->setEffectsVolume(fPercent);
}
    
float SCAudioManager::getMusicVolume() const
{
    return SCCCSoundEngine()->getBackgroundMusicVolume();
}
    
float SCAudioManager::getSoundVolume() const
{
    return SCCCSoundEngine()->getEffectsVolume();
}
    
void SCAudioManager::unsetup()
{
    SC_RETURN_V_IF(_bMsgProcessing);
        
    for(auto it : _audioInfoVtr)
    {
        if(SC_BIT_HAS_OR(it.byAudioFlag, kMaskBitIsPreload) && !SC_BIT_HAS_OR(it.byAudioFlag, kMaskBitIsMusic))
        {
            SCCCSoundEngine()->unloadEffect(it.pszAudioFile);
        }
    }
        
    _audioInfoVtr.clear();
    _msgID2AudioIndexMap.clear();
    _cmd2AudioIndexMap.clear();
}
    
void SCAudioManager::setupSwitchList(const std::list<SCMessage::Ptr>& ptrMsg,const bool bOn,const int nIndex)
{
    for(auto it : ptrMsg)
    {
        if(it->nMsgID==SCID::Msg::kMsgCommand)
        {
            auto cmd = it->parameters.getValue(SC_KEY_COMMAND).getString();
            if(!cmd.isEmpty())
            {
                auto it2 = _cmd2AudioIndexMap.find(cmd);
                if(_cmd2AudioIndexMap.end()==it2)
                {
                    SSwitchIDSet sis;
                    std::list<int>& indexList = (bOn ? sis.onIndexList : sis.offIndexList);
                    indexList.push_back(nIndex);
                        
                    SCMapInsert(_cmd2AudioIndexMap, cmd, sis);
                }
                else
                {
                    std::list<int>& indexList = (bOn ? (*it2).second.onIndexList : (*it2).second.offIndexList);
                    indexList.push_back(nIndex);
                }
            }
        }
        else
        {
            auto it2 = _msgID2AudioIndexMap.find(it->nMsgID);
            if(_msgID2AudioIndexMap.end()==it2)
            {
                SSwitchIDSet sis;
                std::list<int>& indexList = (bOn ? sis.onIndexList : sis.offIndexList);
                indexList.push_back(nIndex);
                    
                SCMapInsert(_msgID2AudioIndexMap, it->nMsgID, sis);
            }
            else
            {
                std::list<int>& indexList = (bOn ? (*it2).second.onIndexList : (*it2).second.offIndexList);
                indexList.push_back(nIndex);
            }
        }
    }
}
    
bool SCAudioManager::setup(const SAudioListInfo* pInfo,const int nSize)
{
    SC_RETURN_IF(_bMsgProcessing, false);
    SC_RETURN_IF(pInfo==nullptr || nSize<=0, false);
        
    this->unsetup();
        
    _audioInfoVtr.resize(nSize);
        
    for(int i=0; i<nSize; ++i)
    {
        if(pInfo[i].ptrOffMsgGroup!=nullptr || pInfo[i].ptrOnMsgGroup!=nullptr)
        {
            SAudioInfo ai = {pInfo[i].pszAudioFile, pInfo[i].byAudioFlag,0};
            _audioInfoVtr[i] = ai;
                
            if(SC_BIT_HAS_OR(pInfo[i].byAudioFlag, kMaskBitIsPreload))
            {
                if(SC_BIT_HAS_OR(pInfo[i].byAudioFlag, kMaskBitIsMusic))
                {
                    this->preloadMusic(pInfo[i].pszAudioFile);
                }
                else
                {
                    this->preloadSound(pInfo[i].pszAudioFile);
                }
            }
                
            if(pInfo[i].ptrOffMsgGroup!=nullptr)
            {
                auto msgList = pInfo[i].ptrOffMsgGroup->getMessageList();
                this->setupSwitchList(msgList,false,i);
            }
                
            if(pInfo[i].ptrOnMsgGroup!=nullptr)
            {
                auto msgList = pInfo[i].ptrOnMsgGroup->getMessageList();
                    
                this->setupSwitchList(msgList,true,i);
            }
        }
    }
        
    return true;
}
    
void SCAudioManager::performAudio(const SSwitchIDSet& sis)
{
    for(auto it2 : sis.onIndexList)
    {
        if(SC_BIT_HAS_OR(_audioInfoVtr[it2].byAudioFlag, kMaskBitIsMusic))
        {
            this->playMusic(_audioInfoVtr[it2].pszAudioFile);
            _nCurrentMusicIndex = it2;
        }
        else
        {
            _audioInfoVtr[it2].nSoundID = this->playSound(_audioInfoVtr[it2].pszAudioFile);
        }
    }
        
    for(auto it2 : sis.offIndexList)
    {
        if(SC_BIT_HAS_OR(_audioInfoVtr[it2].byAudioFlag, kMaskBitIsMusic))
        {
            if(_nCurrentMusicIndex==it2)
            {
                this->stopMusic();
                _nCurrentMusicIndex = -1;
            }
        }
        else
        {
            this->stopSound(_audioInfoVtr[it2].nSoundID);
        }
    }
}
    
bool SCAudioManager::onSCMessageProcess(SCMessage::Ptr ptrMsg)
{
    SCASSERT(ptrMsg!=nullptr);
    _bMsgProcessing = true;
        
    switch(ptrMsg->nMsgID)
    {
        case SCID::Msg::kMsgSettingSoundChanged:
            if(!(*_ptrWatchSound))
            {
                this->stopAllSound();
            }
            break;
                
        case SCID::Msg::kMsgSettingMusicChanged:
            if((*_ptrWatchMusic))
            {
                this->stopMusic();
            }
            break;
                
        default: break;
    }
        
    if(ptrMsg->nMsgID==SCID::Msg::kMsgCommand)
    {
        if(!_cmd2AudioIndexMap.empty())
        {
            auto cmd = ptrMsg->parameters.getValue(SC_KEY_COMMAND).getString();
            if(!cmd.isEmpty())
            {
                auto it = _cmd2AudioIndexMap.find(cmd);
                if(_cmd2AudioIndexMap.end()!=it)
                {
                    this->performAudio((*it).second);
                }
            }
        }
    }
    else
    {
        if(!_msgID2AudioIndexMap.empty())
        {
            auto it = _msgID2AudioIndexMap.find(ptrMsg->nMsgID);
            if(it!=_msgID2AudioIndexMap.end())
            {
                this->performAudio((*it).second);
            }
        }
    }
        
    _bMsgProcessing = false;
    return true;
}

NAMESPACE_SPEEDCC_END

