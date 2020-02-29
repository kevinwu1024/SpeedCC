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

#include "SCObject.h"

NAMESPACE_SPEEDCC_BEGIN

std::list<SCObject::Ptr>*    SCObject::s_pFrameRetainList = nullptr;

SCObject::SCObject()
:_pObjPtrData(nullptr)
,_pScriptContainer(nullptr)
,_castFunc(nullptr)
{
}
    
SCObject::~SCObject()
{
}

void SCObject::setScriptContainer(void* pContainer)
{
	_pScriptContainer = pContainer;
}
    
void SCObject::setObjPtrData(void* pData)
{
    _pObjPtrData = pData;
}

void SCObject::setCastFromOriginObjectFunc(funCastFromOriginObject_t p)
{
    _castFunc = p;
}
    
void SCObject::addObject(SCObject::Ptr ptrObj)
{
    SC_RETURN_V_IF(ptrObj==nullptr);
    SC_RETURN_V_IF(ptrObj.getRawPointer()==this);
    _objList.push_back(ptrObj);
}
    
void SCObject::removeObject(SCObject::Ptr ptrObj)
{
    SC_RETURN_V_IF(ptrObj==nullptr);
    SC_RETURN_V_IF(ptrObj.getRawPointer()==this);
        
    _objList.remove_if([ptrObj](SCObject::Ptr ptrIt)
                        {
                            return (ptrIt==ptrObj);
                        });
}


void SCObject::frameRetain()
{
    if(s_pFrameRetainList == nullptr)
    {
        s_pFrameRetainList = new std::list<SCObject::Ptr>();
    }
    
    s_pFrameRetainList->push_back(this->makeObjPtr(this));
}

void SCObject::freeFrameRetainPool()
{
    if(s_pFrameRetainList)
    {
        s_pFrameRetainList->clear();
    }
}

NAMESPACE_SPEEDCC_END
