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

#ifndef __SPEEDCC__SCPLAYOBJECT_H__
#define __SPEEDCC__SCPLAYOBJECT_H__

#include "../base/SCObject.h"
#include "../base/SCValue.h"
#include "../base/SCDictionary.h"

#include <typeindex>

NAMESPACE_SPEEDCC_BEGIN

///------------ SCPlayObject
class SCPlayObject : public SCObject
{
public:
	SC_AVOID_CLASS_COPY(SCPlayObject)
	SC_DEFINE_CLASS_PTR(SCPlayObject)

	SC_DEFINE_CREATE_FUNC_0(SCPlayObject)
	SC_DEFINE_CREATE_FUNC_1(SCPlayObject,int)

    virtual ~SCPlayObject();
        
    inline int getID() const {return _nID;}
    inline void setID(const int nID) { _nID = nID;}
        
    inline bool getActive() const {return _bActive;}
    void setActive(const bool _bActive);
        
protected:
    SCPlayObject();
    SCPlayObject(const int nID);
        
    virtual void onActiveChanged(const bool bNewActive){}
        
private:
    int         _nID;
    bool        _bActive;
};
    
///---------- SCBehavior
class SCBehavior : public SCPlayObject
{
protected:
    SCBehavior()
    {}
        
public:
    SC_AVOID_CLASS_COPY(SCBehavior)
    SC_DEFINE_CLASS_PTR(SCBehavior)
        
    virtual ~SCBehavior() {}
    virtual void execute(const SCDictionary& par=SCDictionary()) = 0;
};

NAMESPACE_SPEEDCC_END

#endif /* __SPEEDCC__SCPLAYOBJECT_H__ */
