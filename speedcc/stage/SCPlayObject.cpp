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

#include "SCPlayObject.h"
#include "../system/SCSystem.h"

NAMESPACE_SPEEDCC_BEGIN

SCPlayObject::SCPlayObject()
:_nID(0)
,_bActive(true)
{
}
    
SCPlayObject::SCPlayObject(const int nID)
:_nID(nID)
,_bActive(true)
{}
    
SCPlayObject::~SCPlayObject()
{
}
    
void SCPlayObject::setActive(const bool bActive)
{
    SC_RETURN_V_IF(bActive == _bActive);
    
    SCLog("play object [%d] changes to [%s]",_nID, bActive ? "Active" : "Inactive");
    _bActive = bActive;
    this->onActiveChanged(_bActive);
}
    
NAMESPACE_SPEEDCC_END
