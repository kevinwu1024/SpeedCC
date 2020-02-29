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


#include "SCView.h"
#include "SCViewController.h"
#include "SCNodeUtils.h"
#include "../system/SCSystem.h"

using namespace cocos2d;

NAMESPACE_SPEEDCC_BEGIN

///------------- SCView
    
SCView* SCView::create(SCViewController::Ptr ptrController)
{
    SCASSERT(ptrController==nullptr);
    SCASSERT(ptrController.cast<SCViewController::Ptr>()!=nullptr);
        
    auto pView = SCView::create();
    pView->setController(ptrController);
    return pView;
}
    
bool SCView::init()
{
    SC_RETURN_IF(!Node::init(),false);
    this->setContentSize(SCWinSize());
    return true;
}
    
void SCView::setController(SCViewController::Ptr ptrController)
{
    if(_ptrController!=nullptr)
    {
//            auto ptr = ptrController.cast<SCViewController::Ptr>();
        if(ptrController->getView()!=nullptr)
        {
            SCLog("current view controller must not associate view");
            SCASSERT(false);
            return;
        }
    }
        
    SCASSERT(ptrController.cast<SCViewController::Ptr>()!=nullptr);
    _ptrController = ptrController;
}
    
    
void SCView::onEnter()
{
    cocos2d::Node::onEnter();
        
    SCMessage::Ptr ptrMsg = SCMessage::create();
    ptrMsg->nMsgID = SCID::Msg::kMsgViewEnter;
    ptrMsg->parameters.setValue(SC_KEY_CONTROLLER,dynamic_cast<SCViewController*>(_ptrController.getRawPointer()));
    SCMsgDisp()->sendMessage(ptrMsg);
}
    
void SCView::onEnterTransitionDidFinish()
{
    cocos2d::Node::onEnterTransitionDidFinish();
        
    SCMessage::Ptr ptrMsg = SCMessage::create();
    ptrMsg->nMsgID = SCID::Msg::kMsgViewEnterTransitionDidFinish;
    ptrMsg->parameters.setValue(SC_KEY_CONTROLLER,dynamic_cast<SCViewController*>(_ptrController.getRawPointer()));
    SCMsgDisp()->sendMessage(ptrMsg);
}
    
void SCView::onExit()
{
    cocos2d::Node::onExit();
        
    SCMessage::Ptr ptrMsg = SCMessage::create();
    ptrMsg->nMsgID = SCID::Msg::kMsgViewExit;
    ptrMsg->parameters.setValue(SC_KEY_CONTROLLER,dynamic_cast<SCViewController*>(_ptrController.getRawPointer()));
    SCMsgDisp()->sendMessage(ptrMsg);
}
    
void SCView::onExitTransitionDidStart()
{
    cocos2d::Node::onExitTransitionDidStart();
        
    SCMessage::Ptr ptrMsg = SCMessage::create();
    ptrMsg->nMsgID = SCID::Msg::kMsgViewExitTransitionDidStart;
    ptrMsg->parameters.setValue(SC_KEY_CONTROLLER,dynamic_cast<SCViewController*>(_ptrController.getRawPointer()));
    SCMsgDisp()->sendMessage(ptrMsg);
}

///-------------- SCScene
    
SCScene::SCScene()
:_pRootNode(nullptr)
,cocos2d::Scene()
{
}
    
bool SCScene::init()
{
    SC_RETURN_IF(!Scene::init(),false);
        
    _pRootNode = SCView::create();
    _pRootNode->setContentSize(SCWinSize());
    _pRootNode->setPosition(SCNodeUtils::posP2A(Vec2(0,0),SCWinSize()));
    this->addChild(_pRootNode);
        
    return true;
}
    
void SCScene::onEnter()
{
    cocos2d::Scene::onEnter();
}

void SCScene::onEnterTransitionDidFinish()
{
    cocos2d::Scene::onEnterTransitionDidFinish();
}

void SCScene::onExit()
{
    cocos2d::Scene::onExit();
}

void SCScene::onExitTransitionDidStart()
{
    cocos2d::Scene::onExitTransitionDidStart();
}
    
//    void SCScene::replaceView(SCView* pView)
//    {
//        SCASSERT(pView!=nullptr);
//        SCASSERT(pView->getParent()==nullptr);
//
//        if(_pRootNode!=nullptr)
//        {
//            _pRootNode->removeFromParent();
//        }
//
//        this->addChild(pView);
//        _pRootNode = pView;
//    }
    
SCView* SCScene::getView()
{
    return _pRootNode;
}
    
///-------------- SCDisableTouchLayer
    
void SCLayerDisableTouch::onEnter()
{
    EventListenerTouchOneByOne* pEventListener = EventListenerTouchOneByOne::create();
    pEventListener->setSwallowTouches(true);
        
    pEventListener->onTouchBegan = SC_MAKE_FUNC(onSCTouchBegan, this);
        
    SCCCTouchDispatch()->removeEventListenersForTarget(this);
    SCCCTouchDispatch()->addEventListenerWithSceneGraphPriority(pEventListener,this);
        
    this->setTag(kTAG);
        
    Layer::onEnter();
}
    
void SCLayerDisableTouch::onExit()
{
    SCCCTouchDispatch()->removeEventListenersForTarget(this);
    Layer::onExit();
}
    
bool SCLayerDisableTouch::onSCTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    return true;
}

NAMESPACE_SPEEDCC_END


