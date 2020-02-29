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

#ifndef __SPEEDCC__SCVIEW_H__
#define __SPEEDCC__SCVIEW_H__

#include "cocos2d.h"
#include "SCCocosDef.h"
#include "SCViewController.h"

NAMESPACE_SPEEDCC_BEGIN

///----------- SCView
class SCView : public cocos2d::Node
{
public:
    CREATE_FUNC(SCView);
    void setController(SCViewController::Ptr controllerPtr);
    // return weak pointer to prevent resource leak
    inline SCViewController* getController() {return _ptrController.getRawPointer();}
        
    static SCView* create(SCViewController::Ptr ptrController);
        
    template<typename T>
    static SCView* create(const SCDictionary& parameterDic = SCDictionary())
    {
        SCObjPtrT<T> ptrViewCtlr;
        ptrViewCtlr.createInstance();
            
        auto pView = SCView::create();
        pView->setController(ptrViewCtlr);
        ptrViewCtlr->setView(pView);
        ptrViewCtlr->setScene(nullptr);
        ptrViewCtlr->onCreate(parameterDic);
            
        return pView;
    }
        
protected:
    virtual bool init() override;
//        void onAcceleration(cocos2d::Acceleration* pAcc, cocos2d::Event* pEvent);
    /*
        
    virtual void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* unused_event);
        
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    */
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    virtual void onExitTransitionDidStart() override;
        
private:
    SCViewController::Ptr       _ptrController; // view owns controller's strong pointer
    cocos2d::EventListener*     _accListener;
};
    
///----------- SCScene
class SCScene : public cocos2d::Scene
{
public:
    SCScene();
    CREATE_FUNC(SCScene);
        
    virtual bool init() override;

    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    virtual void onExitTransitionDidStart() override;
        
//        virtual void replaceView(SCView* pView);
        
    SCView* getView();
        
private:
    SCView*           _pRootNode;
};
    
///------------ SCLayerDisableTouch
class SCLayerDisableTouch : public cocos2d::Layer
{
public:
    CREATE_FUNC(SCLayerDisableTouch);
        
    enum {kTAG = 1200};
        
    virtual void onEnter() override;
    virtual void onExit() override;
    bool onSCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCVIEW_H__
