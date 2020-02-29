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


#include "SCViewNavigator.h"
#include "../system/SCSystem.h"

using namespace cocos2d;

NAMESPACE_SPEEDCC_BEGIN

SCViewNavigator*           SCViewNavigator::s_pInstance = nullptr;
    
SCViewNavigator* SCViewNavigator::getInstance()
{
    if(s_pInstance==nullptr)
    {
        s_pInstance = new SCViewNavigator();
    }
        
    return s_pInstance;
}
    
void SCViewNavigator::setSceneParameter(const SCDictionary& dic)
{
	s_SceneParameterDic = dic;
}

bool SCViewNavigator::gotoView(const SSceneSwitchInfo& info)
{
    SStackSceneInfo navigateInfo;
    navigateInfo.sceneCreatorInfo = info;
        
    switch(navigateInfo.sceneCreatorInfo.switchType)
    {
        case kLayerModal: // modal
        {
            SC_RETURN_IF(s_pCurrentViewController==nullptr, false);
                
            auto call = [this,info,navigateInfo]()
            {
                auto ptrController = (info.pfunLayerCreator)(s_SceneParameterDic);
                s_SceneParameterDic.removeAllKeys();
                    
                s_pCurrentViewController->pushModalController(ptrController);
                s_sceneStack.push_front(navigateInfo);
                s_pCurrentViewController = ptrController;
            };
                
            if(info.bHasLoading)
            {
                SCViewController::FinishFunc_t finishFunc = [this,call](void*)
                {
                    s_pCurrentViewController = s_pCurrentViewController->popModalFromParent();
                    call();
                };
                    
                s_SceneParameterDic.setValue(SC_KEY_FINISHFUNC, finishFunc);
                auto ptrController = (info.pfunLoadingLayerCreator)(s_SceneParameterDic);
                s_pCurrentViewController->pushModalController(ptrController);
                s_sceneStack.push_front(navigateInfo);
                s_pCurrentViewController = ptrController;
            }
            else
            {
                call();
            }
        }
            break;
                
        case kSceneReplace: // scene replace
        case kScenePush: // scenen push
        {
            auto call = [this,info,navigateInfo]()
            {
                auto ptrController = (info.pfunSceneCreator)(s_SceneParameterDic);
                s_SceneParameterDic.removeAllKeys();
                    
                cocos2d::Scene* pScene = ptrController->getScene();
                    
                if(navigateInfo.sceneCreatorInfo.pfunSelfTransCreator)
                {
                    float fDuration = SCSystem::getSpeedCCOption(SC_OPTION_KEY_DURATIONOFTRANSITION).getFloat();
                    pScene = (*navigateInfo.sceneCreatorInfo.pfunSelfTransCreator)(fDuration,pScene);
                }
                    
                if(SCCCDirector()->getRunningScene())
                {
                    if(navigateInfo.sceneCreatorInfo.switchType==kSceneReplace)
                    {
                        SCCCDirector()->replaceScene(pScene);
                            
                        // remove previous modal scene
                        bool bRemoved = false;
                        s_sceneStack.remove_if([&bRemoved](const SStackSceneInfo& stackInfo) -> bool
                                                {
                                                    SC_RETURN_IF(bRemoved, false);
                                                    SC_RETURN_IF(!bRemoved && stackInfo.sceneCreatorInfo.switchType==kLayerModal, true);
                                                    bRemoved = true;
                                                    return false;
                                                });
                    }
                    else
                    {
                        SCCCDirector()->pushScene(pScene);
                    }
                }
                else
                {// the first scene
                    SCCCDirector()->runWithScene(pScene);
                }
                    
                s_sceneStack.push_front(navigateInfo);
                s_pCurrentViewController = ptrController;
            };
                
            if(info.bHasLoading)
            {
                SCViewController::FinishFunc_t finishFunc = [call](void*) { call(); };
                s_SceneParameterDic.setValue(SC_KEY_FINISHFUNC, finishFunc);
                auto ptrController = (info.pfunLoadingSceneCreator)(s_SceneParameterDic);
                cocos2d::Scene* pScene = ptrController->getScene();
                    
                if(SCCCDirector()->getRunningScene())
                {
                    if(navigateInfo.sceneCreatorInfo.switchType==kSceneReplace)
                    {
                        SCCCDirector()->replaceScene(pScene);
                    }
                    else
                    {
                        SCCCDirector()->pushScene(pScene);
                    }
                }
                else
                {
                    SCCCDirector()->runWithScene(pScene);
                }
                    
                s_pCurrentViewController = ptrController;
            }
            else
            {
                call();
            }
        }
            break;
                
        default:
            SCASSERT(false);
            break;
    }
        
    return true;
}
    
void SCViewNavigator::back(int nNumber)
{
    SC_RETURN_V_IF(s_sceneStack.empty());
    if(nNumber<1)
    {
        nNumber = 1;
    }
	int nSize = (int)s_sceneStack.size();
    SC_RETURN_V_IF(nSize<=nNumber);
        
    FUN_SCSceneTransitionCreateFunctor_t oppositeTrans = nullptr;
    auto switchType = kSceneReplace;
        
    SStackSceneInfo navigateInfo1;
        
    do
    {
        navigateInfo1 = s_sceneStack.front();

        oppositeTrans = navigateInfo1.sceneCreatorInfo.pfunOppositeTransCreator;
        switchType = navigateInfo1.sceneCreatorInfo.switchType;
        s_sceneStack.pop_front();
    }
    while(--nNumber>0);
        
    // use below scene as previous scene
    const auto& navigateInfo2 = s_sceneStack.front();
        
    switch(switchType)
    {
        case kLayerModal: // modal
        {
            s_pCurrentViewController = s_pCurrentViewController->popModalFromParent();
        }
            break;
                
        case kScenePush: // push
        {
            SCCCDirector()->popScene();
            SCScene* pScene = (SCScene*)SCCCDirector()->getRunningScene();
            auto pView = pScene->getView();
            SCASSERT(pView!=nullptr);
            s_pCurrentViewController = pView->getController();
            SCASSERT(s_pCurrentViewController!=nullptr);
        }
            break;
                
        case kSceneReplace: // replace
        {
            SCASSERT(navigateInfo2.sceneCreatorInfo.pfunSceneCreator!=nullptr);
                
            // remove all of kLayerModal layer from navigator stack
            size_t nStackSize = s_sceneStack.size();
            while(nStackSize>2)
            {
                SC_BREAK_IF(s_sceneStack.front().sceneCreatorInfo.switchType!=kLayerModal)
                s_sceneStack.pop_front();
                --nStackSize;
            }
                
            auto call = [navigateInfo2,oppositeTrans,this]()
            {
                auto ptrController = (*navigateInfo2.sceneCreatorInfo.pfunSceneCreator)(s_SceneParameterDic);
                cocos2d::Scene* pScene = ptrController->getScene();
                if(oppositeTrans)
                {
                    float fDuration = SCSystem::getSpeedCCOption(SC_OPTION_KEY_DURATIONOFTRANSITION).getFloat();
                    pScene = (*oppositeTrans)(fDuration,pScene);
                }
                    
                SCCCDirector()->replaceScene(pScene);
                    
                s_pCurrentViewController = ptrController;
                s_SceneParameterDic.removeAllKeys();
            };
                
            if(navigateInfo2.sceneCreatorInfo.bHasLoading)
            {
                SCViewController::FinishFunc_t finishFunc = [call](void*) { call(); };
                s_SceneParameterDic.setValue(SC_KEY_FINISHFUNC, finishFunc);
                auto ptrController = (*navigateInfo2.sceneCreatorInfo.pfunLoadingSceneCreator)(s_SceneParameterDic);
                cocos2d::Scene* pScene = ptrController->getScene();
                    
                SCCCDirector()->replaceScene(pScene);
                s_pCurrentViewController = ptrController;
            }
            else
            {
                call();
            }
        }
            break;
                
        default:
            SCASSERT(false);
            break;
    }
}
    
void SCViewNavigator::reset()
{
    SC_RETURN_V_IF(s_sceneStack.empty());
    auto info = s_sceneStack.front();
    s_sceneStack.clear();
    s_sceneStack.push_back(info);
}

NAMESPACE_SPEEDCC_END


