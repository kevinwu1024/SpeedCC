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

#ifndef __SPEEDCC__SCUIARG_H__
#define __SPEEDCC__SCUIARG_H__

#include "../base/SCString.h"
#include "../base/SCObject.h"
#include "../base/SCWatchNumberT.h"

#include "../stage/SCBehaviorCommon.h"

#include "SCBinderCocos.h"
#include "SCNodeStyle.h"
#include "SCRefHolder.h"
#include "SCRadioGroup.h"

#include "cocos2d.h"
#include "ui/CocosGUI.h"

NAMESPACE_SPEEDCC_BEGIN

class SCViewController;
class SCViewBuilder;
    
typedef void (*FUN_SCSetStyle_t)(cocos2d::Node* pNode,const SCString& strStyle,SCNodeStyle::SFilterConfig* pFilterConfig);
    
namespace SCUIArg
{
    struct StringPurifier
    {
        StringPurifier(void*){}
        StringPurifier(decltype(nullptr)){}
        StringPurifier(const char* psz):strResult(psz){}
        StringPurifier(const SCString& str):strResult(str){}
            
        SCString strResult;
    };
        
    struct LabelStringPurifier
    {
        LabelStringPurifier(...) {}
        LabelStringPurifier(void*) {}
        LabelStringPurifier(const char* psz):strResult(psz){}
        LabelStringPurifier(const SCString& str):strResult(str) {}
        LabelStringPurifier(long n):strResult(n){}
        LabelStringPurifier(int n):strResult(n) {}
        LabelStringPurifier(float n):strResult(n) {}
        LabelStringPurifier(double n):strResult(n) {}
            
        template<typename T,
        typename = typename std::enable_if<SCIsWatchClassT<typename T::type>::value==1,T>::type >
        LabelStringPurifier(T ptrWatch)
        {
            if(ptrWatch!=nullptr)
            {
                ptrLabelBinder = SCBinderUILabel::create();
                ptrLabelBinder->setWatch(ptrWatch);
            }
        }
            
        LabelStringPurifier(SCBinderUILabel::Ptr ptrBinder): ptrLabelBinder(ptrBinder) {}
            
        SCString strResult;
        SCBinderUILabel::Ptr    ptrLabelBinder;
    };
        
    struct BehaviorPurifier
    {
        BehaviorPurifier(cocos2d::SEL_CallFunc func);
        BehaviorPurifier(cocos2d::SEL_MenuHandler func);
            
        template<typename T,
        typename = typename std::enable_if<std::is_convertible<T,SCBehavior::Ptr>::value,T>::type >
        BehaviorPurifier(T bvr)
        :callFunc(nullptr)
        ,menuFunc(nullptr)
        ,ptrResultBvr(bvr)
        {
        }
            
        BehaviorPurifier(decltype(nullptr));
        void setupBehavior(cocos2d::Ref* pCall,cocos2d::Ref* pSender);
            
        SCBehavior::Ptr     ptrResultBvr;
            
    private:
        cocos2d::SEL_CallFunc callFunc;
        cocos2d::SEL_MenuHandler menuFunc;
    };
        
    struct BoolPurifier
    {
        BoolPurifier(const bool bValue);
        BoolPurifier(SCWatchBool::Ptr ptrBool);
            
        bool bResult;
        SCWatchBool::Ptr    ptrWatch;
    };
        
    struct NodePurifier
    {
        template<typename T>
        NodePurifier(T* node):
        pfunSetStyle(&SCNodeStyle::setStyle<T>)
        {
			SCASSERT(node != nullptr);
            ptrNodeHolder = SCRef2Ptr::create(node);
        }
            
        SCRef2Ptr::Ptr        ptrNodeHolder;
        FUN_SCSetStyle_t     pfunSetStyle;
    };
        
    struct MenuItemPurifier
    {
        MenuItemPurifier(const char* pszImage);
        MenuItemPurifier(const SCString& strImage);
        MenuItemPurifier(const SCString& strText,const float size);
        MenuItemPurifier(cocos2d::MenuItem* pMenuItem);
            
    public:
        SCRef2Ptr::Ptr    ptrHolder;
    };
        
    struct PTNumberPurifier
    {
        template<typename T,
        typename = typename std::enable_if<SCIsWatchNumberableT<typename T::type>::value==1,T>::type >
        PTNumberPurifier(T ptrWatch)
        {
            if(ptrWatch!=nullptr)
            {
                ptrBinderProgress = SCBinderUIProgress::create();
                ptrBinderProgress->setWatch(ptrWatch);
            }
        }
            
        PTNumberPurifier(const int nValue)
        :nPercentage(nValue)
        {}
            
        SCBinderUIProgress::Ptr     ptrBinderProgress;
        int                         nPercentage;
    };
        
    struct SliderNumberPurifier
    {
        template<typename T,
        typename = typename std::enable_if<SCIsWatchNumberableT<typename T::type>::value==1,T>::type >
        SliderNumberPurifier(T ptrWatch)
        {
            if(ptrWatch!=nullptr)
            {
                ptrBinderSlider = SCBinderUISlider::create();
                ptrBinderSlider->setWatch(ptrWatch);
            }
        }
            
        SliderNumberPurifier(const int nValue)
        :nPercentage(nValue)
        {}
            
        SCBinderUISlider::Ptr       ptrBinderSlider;
        int                         nPercentage;
    };
        
    struct SizePurifier
    {
        SizePurifier(const cocos2d::Size& size0)
        :size(size0)
        {}
            
        SizePurifier(decltype(nullptr))
        :size(cocos2d::Size::ZERO)
        {}
            
        cocos2d::Size size;
    };
        
    struct ScrollViewDirectionPurifier
    {
        ScrollViewDirectionPurifier(const bool bHor);
        ScrollViewDirectionPurifier(const cocos2d::ui::ScrollView::Direction dir);
            
        cocos2d::ui::ScrollView::Direction direction;
    };
        
    struct DockPurifier
    {
        DockPurifier(std::nullptr_t)
        :nDock(0)
        {}
            
        DockPurifier(const int n)
        :nDock(n)
        {}
            
        int     nDock;
    };
        
    struct MaskStencilPurifier
    {
        MaskStencilPurifier(const SCString& image);
        MaskStencilPurifier(const cocos2d::Size& s);
        MaskStencilPurifier(decltype(nullptr));
        MaskStencilPurifier(cocos2d::Node* pNode);

        cocos2d::Node*      pNode;
        cocos2d::Size       size;
    };
        
    template<typename T>
    struct NodeAssignment
    {
        NodeAssignment(decltype(nullptr))
        :nID(0)
        {
            assignFunc = [](T*) {};
        }
        
        NodeAssignment(int id1)
        :nID(id1)
        {
            assignFunc = [](T*) {};
        }
            
        template<typename T2,
        typename = typename std::enable_if<std::is_convertible<T*,T2*>::value>::type>
        NodeAssignment(T2** ppNode)
        :nID(0)
        {
            assignFunc = [ppNode](T* p) { *ppNode = p; };
        }
            
        void assign(T* pNode)
        {
            assignFunc(pNode);
        }
        
    public:
        int         nID;
        
    private:
        std::function<void(T*)> assignFunc;
    };
 
}
    
namespace SCUITypeDef
{
    typedef void (*FUN_SCSetStyle_t)(cocos2d::Node* pNode,const SCString& strStyle);
        
    struct ContainerEndFunctor
    {
        cocos2d::Node*              pNode;
        SCString                    strStyle;
        FUN_SCSetStyle_t         pfunSetStyle;
            
        ContainerEndFunctor()
        :pfunSetStyle(nullptr)
        ,pNode(nullptr)
        {}
            
        virtual void operator()()
        {
            if(pNode!=nullptr && pfunSetStyle!=nullptr && !strStyle.isEmpty())
            {
                (*pfunSetStyle)(pNode,strStyle);
            }
        }
    };
        
    enum class EContainerType
    {
        kNormal,
        kAlignment,
        kMultiplexLayer
    };
        
    struct SUIContext
    {
        cocos2d::Node*                      pContainerNode;
        std::list<cocos2d::Node*>           childNodeList;
        std::function<void(SUIContext&)>    endFunc;
        EContainerType                      containerType;
            
        SUIContext()
        :pContainerNode(nullptr)
        ,containerType(EContainerType::kNormal)
        {}
    };
}

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCUIARG_H__
