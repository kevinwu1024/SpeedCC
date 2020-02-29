/****************************************************************************
 
 Copyright (c) 2017-2020 Kevin Wu (Wu Feng)
 
 github: http://github.com/kevinwu1024
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
    http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON  . IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

#include "SCRadioGroup.h"
#include "SCNodeAttachment.h"
#include "../system/SCSystem.h"


NAMESPACE_SPEEDCC_BEGIN

///----------- SCRadioGroup
    
SCRadioGroup::SCRadioGroup()
:_nActiveID(INT_MAX)
{
}
    
SCRadioGroup::~SCRadioGroup()
{
}
    
bool SCRadioGroup::addRadio(cocos2d::MenuItemToggle* pToggle)
{
    SCASSERT(pToggle!=nullptr);
        
    auto ptrAttachment = SCNodeAttach(pToggle);
    if(!ptrAttachment->hasRadioID())
    {
        SCLog("Must set radio id first. It may use 'radio' style key");
        return false;
    }
    int nRadioID = ptrAttachment->getRadioID();
        
    if(this->hasRadioID(nRadioID))
    {
        SCLog("Radio ID %d already exist.",nRadioID);
        return false;
    }
        
    for(auto& it : _radioID2ToggleMap)
    {
        if(it.second==pToggle)
        {
            SCLog("MenuItemToggle already exist.");
            return false;
        }
    }
        
    _radioID2ToggleMap[nRadioID] = pToggle;
        
    pToggle->setCallback([this,nRadioID](cocos2d::Ref*)
                            {
                                this->setRadioActive(nRadioID);
                            });
        
    return true;
}
    
void SCRadioGroup::removeRadio(const int nRadioID)
{
    auto it = _radioID2ToggleMap.find(nRadioID);
    if(it!=_radioID2ToggleMap.end())
    {
        _radioID2ToggleMap.erase(it);
    }
}
    
void SCRadioGroup::removeRadio(cocos2d::MenuItemToggle* pToggle)
{
    SC_RETURN_V_IF(pToggle==nullptr);
        
    for(auto it : _radioID2ToggleMap)
    {
        if(it.second==pToggle)
        {
            _radioID2ToggleMap.erase(it.first);
            return;
        }
    }
}
    
cocos2d::MenuItemToggle* SCRadioGroup::getMenuItemToggle(const int nRadioID)
{
    auto it = _radioID2ToggleMap.find(nRadioID);
    SC_RETURN_IF(it==_radioID2ToggleMap.end(), nullptr);
    return (*it).second;
}
    
void SCRadioGroup::setRadioActive(const int nRadioID)
{
    if(this->hasRadioID(nRadioID) && nRadioID!=_nActiveID)
    {
        int nOldID = _nActiveID;
        _nActiveID = nRadioID;
        for(auto it : _radioID2ToggleMap)
        {
            if(it.first==_nActiveID)
            {
                it.second->setSelectedIndex(0);
                it.second->setEnabled(false); // prevent to select it again
            }
            else
            {
                it.second->setSelectedIndex(1);
                it.second->setEnabled(true);
            }
        }
            
        if(_listenerFunc!=nullptr)
        {
            _listenerFunc(this->makeObjPtr(this),_nActiveID,nOldID);
        }
    }
}
    
int SCRadioGroup::getActivedRadioID() const
{
    return _nActiveID;
}
    
bool SCRadioGroup::hasRadioID(const int nID) const
{
    auto it = _radioID2ToggleMap.find(nID);
    return (it!=_radioID2ToggleMap.end());
}
    
void SCRadioGroup::setListenerFunc(const radioListenerFunc_t& func)
{
    _listenerFunc = func;
}
NAMESPACE_SPEEDCC_END

