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

#ifndef __SPEEDCC__SCRADIOGROUP_H__
#define __SPEEDCC__SCRADIOGROUP_H__

#include "cocos2d.h"
#include "../base/SCObject.h"
#include "../base/SCWatchNumberT.h"

NAMESPACE_SPEEDCC_BEGIN

class SCViewBuilder;
    
///----------- SCRadioGroup
class SCRadioGroup : public SCObject
{
public:
    friend SCViewBuilder;
public:
    SC_AVOID_CLASS_COPY(SCRadioGroup)
    SC_DEFINE_CLASS_PTR(SCRadioGroup)
        
    virtual ~SCRadioGroup();
        
    SC_DEFINE_CREATE_FUNC_0(SCRadioGroup)
        
    typedef std::function<void(SCRadioGroup::Ptr ptrGroup,int nNewRadioID,int nOldRadioID)>  radioListenerFunc_t;
        
    void setRadioActive(const int nRadioID);
    int getActivedRadioID() const;
    void setListenerFunc(const radioListenerFunc_t& func);
    cocos2d::MenuItemToggle* getMenuItemToggle(const int nRadioID);
        
private:
    bool addRadio(cocos2d::MenuItemToggle* pToggle);
    void removeRadio(const int nRadioID);
    void removeRadio(cocos2d::MenuItemToggle* pToggle);
    bool hasRadioID(const int nID) const;
        
protected:
    SCRadioGroup();
        
private:
    radioListenerFunc_t                         _listenerFunc;
    SCWatchInt::Ptr                             _ptrActiveRadioID;
    int                                         _nActiveID;
    std::map<int,cocos2d::MenuItemToggle*>      _radioID2ToggleMap;
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCRADIOGROUP_H__
