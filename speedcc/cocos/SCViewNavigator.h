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

#ifndef __SPEEDCC__SCVIEWNAVIGATOR_H__
#define __SPEEDCC__SCVIEWNAVIGATOR_H__

#include "cocos2d.h"
#include "SCCocosDef.h"
#include "SCView.h"
#include "SCViewController.h"

NAMESPACE_SPEEDCC_BEGIN
    
template<typename T>
class SCVCCreatorT
{
public:
    static cocos2d::Scene* createTransition(float duration,cocos2d::Scene* pScene)
    {
        return T::create(duration, pScene);
    }
        
    static SCViewController* createVCScene(const SCDictionary& parameterDic)
    {
        SCObjPtrT<T> ptrViewCtlr;
            
        do
        {
            ptrViewCtlr.createInstance();
                
            SC_BREAK_IF(ptrViewCtlr.isNull());
                
            auto scene = SCScene::create();
            auto pView = scene->getView();
            pView->setController(ptrViewCtlr);
            ptrViewCtlr->setScene(scene);
            ptrViewCtlr->setView(pView);
            ptrViewCtlr->onCreate(parameterDic);
                
        } while (0);
            
        return ptrViewCtlr.getRawPointer();
    }
        
    static SCViewController* createVC(const SCDictionary& parameterDic)
    {
        auto pView = SCView::create<T>(parameterDic);
        return pView->getController();
    }
    
    static SCObjPtrT<T> createVCPtr(const SCDictionary& parameterDic = SCDictionary())
    {
        auto pVC = createVC(parameterDic);
        auto pVC2 = dynamic_cast<T*>(pVC);
        SCObjPtrT<T> ptrRet = nullptr;
        
        if(pVC2)
        {
            ptrRet = pVC2->template makeObjPtr<SCObjPtrT<T>>();
        }
        
        return ptrRet;
    }
};
    
template<>
struct SCVCCreatorT<SCClassNull>
{
    static cocos2d::Scene* createTransition(float duration,cocos2d::Scene* pScene)
    {return pScene;}
        
    static SCViewController* createVCScene(const SCDictionary& parameterDic)
    { return nullptr; }
        
    static SCViewController* createVC(const SCDictionary& parameterDic)
    { return nullptr; }
    
    static nullptr_t createVCPtr(const SCDictionary& parameterDic = SCDictionary())
    { return nullptr; }
};
    
    
class SCViewNavigator final
{
    friend class SCBehaviorViewGoto;
public:
	enum ESceneSwitchType
	{
		kSceneReplace, // using cocos2d replace scene
		kScenePush, // using cocos2d push scene
		kLayerModal, // push SCView as modal layer
	};

private:
    typedef SCViewController* (*FUN_SCSceneCreateFunctor_t)(const SCDictionary& dic);
    typedef SCViewController* (*FUN_SCLayerCreateFunctor_t)(const SCDictionary& dic);
    typedef cocos2d::Scene* (*FUN_SCSceneTransitionCreateFunctor_t)(const float fDuration, cocos2d::Scene* pScene);
        
public:
	struct SSceneSwitchInfo
	{
		ESceneSwitchType						switchType;
		FUN_SCSceneTransitionCreateFunctor_t	pfunSelfTransCreator; 
		FUN_SCSceneTransitionCreateFunctor_t	pfunOppositeTransCreator;
		FUN_SCSceneCreateFunctor_t              pfunSceneCreator;
        FUN_SCLayerCreateFunctor_t              pfunLayerCreator;
        FUN_SCSceneCreateFunctor_t              pfunLoadingSceneCreator;
        FUN_SCLayerCreateFunctor_t              pfunLoadingLayerCreator;
        bool                                    bHasLoading;
            
		SSceneSwitchInfo()
        :switchType(kSceneReplace)
        ,pfunSelfTransCreator(nullptr)
        ,pfunOppositeTransCreator(nullptr)
        ,pfunSceneCreator(nullptr)
        ,pfunLayerCreator(nullptr)
        ,pfunLoadingSceneCreator(nullptr)
        ,pfunLoadingLayerCreator(nullptr)
        ,bHasLoading(false)
		{}

        SSceneSwitchInfo(ESceneSwitchType type,
                            FUN_SCSceneTransitionCreateFunctor_t pfunSelfTrans,
                            FUN_SCSceneTransitionCreateFunctor_t pfunOppositeTrans,
                            FUN_SCSceneCreateFunctor_t pfunScene,
                            FUN_SCLayerCreateFunctor_t pfunLayer,
                            FUN_SCSceneCreateFunctor_t pfunLoadingScene,
                            FUN_SCLayerCreateFunctor_t pfunLoadingLayer,
                            bool bLoading)
        :switchType(type)
        ,pfunSelfTransCreator(pfunSelfTrans)
        ,pfunOppositeTransCreator(pfunOppositeTrans)
        ,pfunSceneCreator(pfunScene)
        ,pfunLayerCreator(pfunLoadingScene)
        ,pfunLoadingSceneCreator(pfunScene)
        ,pfunLoadingLayerCreator(pfunLoadingScene)
        ,bHasLoading(bLoading)
        {}
            
        SSceneSwitchInfo(const SSceneSwitchInfo& info)
        :switchType(info.switchType)
        ,pfunSelfTransCreator(info.pfunSelfTransCreator)
        ,pfunOppositeTransCreator(info.pfunOppositeTransCreator)
        ,pfunSceneCreator(info.pfunSceneCreator)
        ,pfunLayerCreator(info.pfunLayerCreator)
        ,pfunLoadingSceneCreator(info.pfunLoadingSceneCreator)
        ,pfunLoadingLayerCreator(info.pfunLoadingLayerCreator)
        ,bHasLoading(info.bHasLoading)
        {
        }
            
        template<typename SceneT, typename TransT = SCClassNull, typename LoadingT=SCClassNull>
        void setUp(const ESceneSwitchType place = kSceneReplace)
        {
            static_assert(!SCIsEmptyClassT<SceneT>::value,"target scene should not empty class");
                
            TransT* pTrans = nullptr;
            switchType = place;
            pfunSelfTransCreator = &SCVCCreatorT<TransT>::createTransition;
            pfunOppositeTransCreator = &SCVCCreatorT< decltype(SCTraitsTransitionSceneOpposite(pTrans)) >::createTransition;
            pfunSceneCreator = (FUN_SCSceneCreateFunctor_t)(&SCVCCreatorT<SceneT>::createVCScene);
            pfunLayerCreator = (FUN_SCSceneCreateFunctor_t)(&SCVCCreatorT<SceneT>::createVC);
                
            pfunLoadingSceneCreator = (FUN_SCSceneCreateFunctor_t)(&SCVCCreatorT<LoadingT>::createVCScene);
            pfunLoadingLayerCreator = (FUN_SCSceneCreateFunctor_t)(&SCVCCreatorT<LoadingT>::createVC);
                
            bHasLoading = std::is_same<LoadingT,SCClassNull>::value ? false : true;
        }
	};
        
    struct SStackSceneInfo
    {
        SSceneSwitchInfo                sceneCreatorInfo;
    };

public:
    static SCViewNavigator* getInstance();
        
    template<typename SceneT, typename TransT = SCClassNull, typename LoadingT=SCClassNull>
    bool gotoView(const ESceneSwitchType place = kSceneReplace, const SCDictionary& dic = SCDictionary())
	{
        static_assert(std::is_base_of<SCViewController,SceneT>::value,
                        "Target Scene Must Derive From SCViewController");

		s_SceneParameterDic = dic;

		SSceneSwitchInfo switchInfo;

        switchInfo.setUp<SceneT,TransT,LoadingT>(place);
		return SCViewNavigator::getInstance()->gotoView(switchInfo);
	}

    inline SCViewController* getCurrentController() const {return s_pCurrentViewController;}
    void back(int nNumber = 1);
    void reset();
    void setSceneParameter(const SCDictionary& dic);
        
private:
    bool gotoView(const SSceneSwitchInfo& info);
        
private:
    SCViewController*                   s_pCurrentViewController;
    SCDictionary                        s_SceneParameterDic;
    std::list<SStackSceneInfo>          s_sceneStack;
    static SCViewNavigator*             s_pInstance;
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCViewNavigator_H__
