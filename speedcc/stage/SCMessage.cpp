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

#include "SCMessage.h"
#include "../base/SCBaseMacros.h"

NAMESPACE_SPEEDCC_BEGIN

SCMessage::Ptr SCMessage::clone()
{
    return SCMessage::create(nMsgID,parameters, pTargetListener);
}

SCViewController* SCMessage::getController()
{
    bool bResult = false;
    return static_cast<SCViewController*>(this->parameters.getValue(SC_KEY_CONTROLLER).getPointer(&bResult,true));
}

SCString SCMessage::getCommand() const
{
    SC_RETURN_IF(nMsgID != SCID::Msg::kMsgCommand, "");
    return this->getParameter(SC_KEY_COMMAND).getString();
}

SCValue SCMessage::getParameter(const SCString& strKey) const
{
    return this->parameters.getValue(strKey);
}
    
///----------------- SCMessageGroup
SCMessageGroup::SCMessageGroup(const int nMsgID)
{
    auto ptrMsg = SCMessage::create(nMsgID);
    _msgList.push_back(ptrMsg);
}
    
SCMessageGroup::SCMessageGroup(const SCString& strCmd)
{
    auto ptrMsg = SCMessage::create(strCmd);
    _msgList.push_back(ptrMsg);
}
    
SCMessageGroup::SCMessageGroup(const int nMsgID,const SCDictionary& dic)
{
    auto ptrMsg = SCMessage::create(nMsgID,dic);
    _msgList.push_back(ptrMsg);
}
    
SCMessageGroup::SCMessageGroup(const SCString& strCmd,const SCDictionary& dic)
{
    auto ptrMsg = SCMessage::create(strCmd,dic);
    _msgList.push_back(ptrMsg);
}
    
SCMessageGroup::SCMessageGroup(SCMessageGroup::Ptr ptr1, SCMessageGroup::Ptr ptr2)
{
    SCASSERT(ptr1!=nullptr);
    SCASSERT(ptr2!=nullptr);
        
    auto list1 = ptr1->getMessageList();
    auto list2 = ptr2->getMessageList();
        
    _msgList.assign(list1.begin(), list1.end());
    _msgList.insert(_msgList.end(), list2.begin(),list2.end());
}
    
///--------------- SCMessageMatcher
SCMessageMatcher::SCMessageMatcher(const int nMsgID,const MatchFunc_t& func)
:_nMsgID(nMsgID)
,_func(func)
{
}
    
SCMessageMatcher::SCMessageMatcher(const SCString& strCommand,const MatchFunc_t& func)
:_strCommand(strCommand)
,_nMsgID(SCID::Msg::kMsgCommand)
,_func(func)
{
    SCASSERT(!_strCommand.isEmpty());
}
    
SCMessageMatcher::SCMessageMatcher(const int nMsgID,const SCDictionary& dic)
:_nMsgID(nMsgID)
,_paraDic(dic)
,_func(nullptr)
{
}
    
SCMessageMatcher::SCMessageMatcher(const SCString& strCommand,const SCDictionary& dic)
:_nMsgID(SCID::Msg::kMsgCommand)
,_strCommand(strCommand)
,_paraDic(dic)
,_func(nullptr)
{
    SCASSERT(!_strCommand.isEmpty());
}
    
bool SCMessageMatcher::isMatch(const SCMessage::Ptr ptrMsg) const
{
    SCASSERT(ptrMsg!=nullptr);
    SC_RETURN_IF((_func==nullptr || ptrMsg==nullptr || _nMsgID!=ptrMsg->nMsgID), false);
        
    if(_nMsgID==SCID::Msg::kMsgCommand)
    {
        SC_RETURN_IF(_strCommand.isEmpty(),false);
            
        auto value = ptrMsg->parameters.getValue(SC_KEY_COMMAND);
        SC_RETURN_IF(!value.isValidObject<SCString>(),false);
            
        auto command = value.getString();
        SC_RETURN_IF(command!=_strCommand,false);
    }
        
    if(!_paraDic.isEmpty())
    {
        bool bResult = true;
        _paraDic.forEach([this,ptrMsg,&bResult](const SCString& strKey,const SCValue& value) -> bool
                            {
                                auto value2 = ptrMsg->parameters.getValue(strKey);
                                 
                                do
                                {
                                    if(value2.isNumberType() && value.isNumberType())
                                    {
                                        if((value2.getType()==SCValue::kTypeFloat || value2.getType()==SCValue::kTypeDouble) &&
                                        (value.getType()==SCValue::kTypeFloat || value.getType()==SCValue::kTypeDouble))
                                        {
                                            bResult = (value2.getFloat()==value.getFloat());
                                        }
                                        else
                                        {
                                            bResult = (value2.getInt()==value.getInt());
                                        }
                                             
                                        break;
                                    }
                                    else if(value2.getType()==value.getType())
                                    {
                                        if(value2.getType()==SCValue::kTypeBool)
                                        {
                                            bResult = (value2.getBool()==value.getBool());
                                        }
                                        else if(value2.getType()==SCValue::kTypeString)
                                        {
                                            bResult = (value2.getString()==value.getString());
                                        }
                                    }
                                     
                                }while(0);
                                 
                                return bResult;
                            });
            
        SC_RETURN_IF(!bResult, false);
    }
        
    return (_func==nullptr) ? true : _func(ptrMsg);
}
    
///--------------- SCMessageMatcherGroup
SCMessageMatcherGroup::SCMessageMatcherGroup(const int nMsgID)
{
    _msgMatcherList.push_back(SCMessageMatcher::create(nMsgID,SCDictionary()));
}
    
SCMessageMatcherGroup::SCMessageMatcherGroup(const int nMsgID,const SCDictionary& dic)
{
    _msgMatcherList.push_back(SCMessageMatcher::create(nMsgID,dic));
}
    
SCMessageMatcherGroup::SCMessageMatcherGroup(const SCString& strCmd)
{
    _msgMatcherList.push_back(SCMessageMatcher::create(strCmd,SCDictionary()));
}
    
SCMessageMatcherGroup::SCMessageMatcherGroup(const SCString& strCmd,const SCDictionary& dic)
{
    _msgMatcherList.push_back(SCMessageMatcher::create(strCmd,dic));
}
    
SCMessageMatcherGroup::SCMessageMatcherGroup(SCMessageMatcher::Ptr ptrMatcher)
{
    _msgMatcherList.push_back(ptrMatcher);
}
    
SCMessageMatcherGroup::SCMessageMatcherGroup(SCMessageMatcherGroup::Ptr ptr1, SCMessageMatcherGroup::Ptr ptr2)
{
    auto list1 = ptr1->getMsgMatcherList();
    auto list2 = ptr2->getMsgMatcherList();
        
    _msgMatcherList.assign(list1.begin(), list1.end());
    _msgMatcherList.insert(_msgMatcherList.end(), list2.begin(),list2.end());
}
NAMESPACE_SPEEDCC_END

