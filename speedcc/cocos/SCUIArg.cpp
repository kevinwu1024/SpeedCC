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

#include "SCUIArg.h"
#include "SCNodeUtils.h"

NAMESPACE_SPEEDCC_BEGIN

///--------- BoolPurifier
SCUIArg::BoolPurifier::BoolPurifier(const bool bValue)
:bResult(bValue)
{}
    
SCUIArg::BoolPurifier::BoolPurifier(SCWatchBool::Ptr ptrBool)
:ptrWatch(ptrBool)
{
    SCASSERT(ptrBool!=nullptr);
    bResult = (ptrBool==nullptr ? false : (bool)(*ptrBool));
}
    
///---------- BehaviorPurifier
SCUIArg::BehaviorPurifier::BehaviorPurifier(cocos2d::SEL_CallFunc func)
:callFunc(func)
,menuFunc(nullptr)
{
}
    
SCUIArg::BehaviorPurifier::BehaviorPurifier(cocos2d::SEL_MenuHandler func)
:menuFunc(func)
,callFunc(nullptr)
{
}
    
SCUIArg::BehaviorPurifier::BehaviorPurifier(decltype(nullptr))
:callFunc(nullptr)
,menuFunc(nullptr)
{}
    
void SCUIArg::BehaviorPurifier::setupBehavior(cocos2d::Ref* pCall,cocos2d::Ref* pSender)
{
    if(ptrResultBvr==nullptr)
    {
        if(menuFunc!=nullptr)
        {
            auto func = menuFunc;
            ptrResultBvr = SCBehaviorCallFunc::create([pCall,func,pSender]()
                                                        {
                                                            (pCall->*func)(pSender);
                                                        });
                
        }
        else if(callFunc!=nullptr)
        {
            auto func = callFunc;
            ptrResultBvr = SCBehaviorCallFunc::create([pCall,func]()
                                                        {
                                                            (pCall->*func)();
                                                        });
        }
    }
}
    
SCUIArg::MaskStencilPurifier::MaskStencilPurifier(const SCString& image)
:size(cocos2d::Size::ZERO)
{
    pNode = SCNodeUtils::createSprite(image);
}
    
SCUIArg::MaskStencilPurifier::MaskStencilPurifier(const cocos2d::Size& s)
:size(s)
,pNode(nullptr)
{}
    
SCUIArg::MaskStencilPurifier::MaskStencilPurifier(decltype(nullptr))
:size(cocos2d::Size::ZERO)
,pNode(nullptr)
{}
    
SCUIArg::MaskStencilPurifier::MaskStencilPurifier(cocos2d::Node* pNode)
:size(cocos2d::Size::ZERO)
,pNode(pNode)
{
}
    
///----------- ScrollViewDirectionPurifier
SCUIArg::ScrollViewDirectionPurifier::ScrollViewDirectionPurifier(const bool bHor)
{
    direction = bHor ? cocos2d::ui::ScrollView::Direction::HORIZONTAL : cocos2d::ui::ScrollView::Direction::VERTICAL;
}
    
SCUIArg::ScrollViewDirectionPurifier::ScrollViewDirectionPurifier(const cocos2d::ui::ScrollView::Direction dir):
direction(dir)
{
}
    
///------------ MenuItemPurifier
SCUIArg::MenuItemPurifier::MenuItemPurifier(const char* pszImage)
{
    SCASSERT(pszImage!=nullptr);
    SCString strImage = pszImage;
    SCASSERT(!strImage.isEmpty());
    auto pSprite1 = SCNodeUtils::createSprite(strImage);
    auto pSprite2 = cocos2d::Sprite::createWithSpriteFrame(pSprite1->getSpriteFrame());
    auto pSprite3 = cocos2d::Sprite::createWithSpriteFrame(pSprite1->getSpriteFrame());
    auto pMenuItem = cocos2d::MenuItemSprite::create(pSprite1,pSprite2,pSprite3);
    ptrHolder = SCRef2Ptr::create(pMenuItem);
}
    
SCUIArg::MenuItemPurifier::MenuItemPurifier(const SCString& strImage)
{
    SCASSERT(!strImage.isEmpty());
    auto pSprite1 = SCNodeUtils::createSprite(strImage);
    auto pSprite2 = cocos2d::Sprite::createWithSpriteFrame(pSprite1->getSpriteFrame());
    auto pSprite3 = cocos2d::Sprite::createWithSpriteFrame(pSprite1->getSpriteFrame());
    auto pMenuItem = cocos2d::MenuItemSprite::create(pSprite1,pSprite2,pSprite3);
    ptrHolder = SCRef2Ptr::create(pMenuItem);
}
    
SCUIArg::MenuItemPurifier::MenuItemPurifier(const SCString& strText,const float size)
{
    auto pLabel = cocos2d::Label::createWithSystemFont(strText.c_str(),"",size);
    auto pMenuItem = cocos2d::MenuItemLabel::create(pLabel);
        
    ptrHolder = SCRef2Ptr::create(pMenuItem);
}
    
SCUIArg::MenuItemPurifier::MenuItemPurifier(cocos2d::MenuItem* pMenuItem)
{
    SCASSERT(pMenuItem!=nullptr);
    ptrHolder = SCRef2Ptr::create(pMenuItem);
}
NAMESPACE_SPEEDCC_END


