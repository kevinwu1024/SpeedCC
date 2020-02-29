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

#include "gtest/gtest.h"
#include "SpeedCC.h"

using namespace SpeedCC;

int s_ACounter = 0;
bool s_AFoo = false;
int s_BCounter = 0;
bool s_BFoo = false;

class ObjPtrA : public SCObject
{
public:
    typedef SCObjPtrT<ObjPtrA>  Ptr;
    ObjPtrA(){ s_ACounter++;std::cout << "A class constructor: " << this << std::endl; };
    virtual void foo() {s_AFoo = true;};
    virtual ~ObjPtrA(){ s_ACounter--;std::cout << "A class destructor: " << this << std::endl;};
};

class ObjPtrB : public ObjPtrA
{
public:
    typedef SCObjPtrT<ObjPtrB>  Ptr;
    ObjPtrB(){ s_BCounter++;std::cout << "B class constructor: " << this << std::endl; };
    virtual void foo() {s_BFoo = true;};
    virtual ~ObjPtrB(){ s_BCounter--;std::cout << "B class destructor: " << this << std::endl;};
};

void resetVar()
{
    s_ACounter = 0;
    s_AFoo = false;
    s_BCounter = 0;
    s_BFoo = false;
}

TEST(TestSCObjPtr, StrongLifecycle)
{
    
    // without instance
    resetVar();
    {
        SCObjPtrT<ObjPtrA> APtr;
        EXPECT_EQ(APtr.getRefCount(),0);
        EXPECT_EQ(s_ACounter,0);
        EXPECT_EQ(APtr==NULL,true);
    }
    
    EXPECT_EQ(s_ACounter,0);
    
    // with instance
    resetVar();
    {
        SCObjPtrT<ObjPtrA> APtr;
        EXPECT_EQ(s_ACounter,0);
        APtr.createInstance();
        EXPECT_EQ(s_ACounter,1);
        EXPECT_EQ(APtr.getRefCount(),1);
        EXPECT_EQ(APtr!=NULL,true);
    }
    EXPECT_EQ(s_ACounter,0);
    
    // with re-create instance
    resetVar();
    {
        SCObjPtrT<ObjPtrA> APtr;
//        ObjPtrA* p = APtr.getRawPointer();
        std::shared_ptr<int> kk;
        EXPECT_EQ(s_ACounter,0);
        APtr.createInstance();
        EXPECT_EQ(s_ACounter,1);
        EXPECT_EQ(APtr.getRefCount(),1);
        APtr.createInstance();
        EXPECT_EQ(s_ACounter,1);
        EXPECT_EQ(APtr.getRefCount(),1);
        EXPECT_EQ(APtr!=NULL,true);
    }
    EXPECT_EQ(s_ACounter,0);
    
    // with multiple instances
    resetVar();
    {
        SCObjPtrT<ObjPtrA> APtr;
        EXPECT_EQ(s_ACounter,0);
        APtr.createInstance();
        EXPECT_EQ(s_ACounter,1);
        EXPECT_EQ(APtr!=NULL,true);
        
        SCObjPtrT<ObjPtrA> APtr2;
        APtr2.createInstance();
        EXPECT_EQ(s_ACounter,2);
        EXPECT_EQ(APtr2!=NULL,true);
    }
    EXPECT_EQ(s_ACounter,0);
    
    // with assignment
    resetVar();
    {
        SCObjPtrT<ObjPtrA> APtr;
        EXPECT_EQ(s_ACounter,0);
        APtr.createInstance();
        EXPECT_EQ(s_ACounter,1);
        EXPECT_EQ(APtr.getRefCount(),1);
        
        SCObjPtrT<ObjPtrA> APtr2 = APtr;
        EXPECT_EQ(s_ACounter,1);
        EXPECT_EQ(APtr2.getRefCount(),2);
        EXPECT_EQ(APtr.getRefCount(),2);
        EXPECT_EQ(APtr2!=NULL,true);
    }
    EXPECT_EQ(s_ACounter,0);
    
}

TEST(TestSCObjPtr, WeakLifecycle)
{
    // weak pointer
    s_ACounter = 0;
    {
        SCObjPtrT<ObjPtrA,false> APtr;
        EXPECT_EQ(s_ACounter,0);
        EXPECT_EQ(APtr==NULL,true);
    }
    EXPECT_EQ(s_ACounter,0);
    
    // with assignment
    resetVar();
    {
        SCObjPtrT<ObjPtrA> APtr;
        EXPECT_EQ(s_ACounter,0);
        SCObjPtrT<ObjPtrA,false> APtr1 = APtr;
        EXPECT_EQ(s_ACounter,0);
        EXPECT_EQ(APtr1==NULL,true);
        EXPECT_EQ(APtr.getRefCount(),0);
        EXPECT_EQ(APtr1.getRefCount(),0);
        APtr.createInstance();
        
        SCObjPtrT<ObjPtrA,false> APtr2 = APtr;
        EXPECT_EQ(s_ACounter,1);
        EXPECT_EQ(APtr2!=NULL,true);
        EXPECT_EQ(APtr.getRefCount(),1);
        EXPECT_EQ(APtr2.getRefCount(),1);
        EXPECT_EQ(APtr==APtr2,true);
        
        SCObjPtrT<ObjPtrA,false> APtr3 = APtr2;
        EXPECT_EQ(s_ACounter,1);
        EXPECT_EQ(APtr2!=NULL,true);
        EXPECT_EQ(APtr3!=NULL,true);
        EXPECT_EQ(APtr.getRefCount(),1);
        EXPECT_EQ(APtr2.getRefCount(),2);
        EXPECT_EQ(APtr3.getRefCount(),2);
        EXPECT_EQ(APtr2==APtr3,true);
        EXPECT_EQ(APtr==APtr3,true);
    }
    EXPECT_EQ(s_ACounter,0);
}

TEST(TestSCObjPtr, Assigment)
{
    SCObjPtrT<ObjPtrA,true> APtr;
    SCObjPtrT<ObjPtrA,false> APtr1;
    
    EXPECT_EQ(APtr==NULL,true);
    EXPECT_EQ(APtr1==NULL,true);
    
    APtr1 = APtr;
    EXPECT_EQ(APtr==APtr1,true);
    EXPECT_EQ(APtr==NULL,true);
    EXPECT_EQ(APtr1==NULL,true);
    EXPECT_EQ(APtr1.getRefCount(),0);
    
    resetVar();
    {
        ObjPtrA* p = new ObjPtrA();
        APtr1 = p;
        EXPECT_EQ((APtr1==p),true);
        EXPECT_EQ(APtr1!=NULL,true);
        EXPECT_EQ(APtr1.getRefCount(),1);
    }
    EXPECT_EQ(s_ACounter,1);
    
    EXPECT_EQ(APtr1!=NULL,true);
    EXPECT_EQ(APtr1.getRefCount(),1);
    APtr1 = NULL;
    EXPECT_EQ(APtr1.getRefCount(),0);
    
    resetVar();
    {
        SCObjPtrT<ObjPtrB> BPtr;
        BPtr.createInstance();
        EXPECT_EQ(s_ACounter,1);
        EXPECT_EQ(s_BCounter,1);
        
        SCObjPtrT<ObjPtrA> APtr = BPtr;
        EXPECT_EQ(s_ACounter,1);
        EXPECT_EQ(s_BCounter,1);
        EXPECT_EQ(APtr.getRefCount(),2);
        EXPECT_EQ(BPtr.getRefCount(),2);
    }
    EXPECT_EQ(s_ACounter,0);
    EXPECT_EQ(s_BCounter,0);
}

TEST(TestSCObjPtr, Instance)
{
    resetVar();
    {
        SCObjPtrT<ObjPtrA> APtr;
        APtr.createInstance();
        
        SCObjPtrT<ObjPtrB> BPtr;
        BPtr.createInstance();
        
        EXPECT_EQ(s_ACounter,2);
        EXPECT_EQ(s_BCounter,1);
        EXPECT_EQ(APtr.getRefCount(),1);
        EXPECT_EQ(BPtr.getRefCount(),1);
    }
    EXPECT_EQ(s_ACounter,0);
    EXPECT_EQ(s_BCounter,0);
    
    resetVar();
    {
        SCObjPtrT<ObjPtrB> BPtr;
        BPtr.createInstance();
        SCObjPtrT<ObjPtrA> APtr = BPtr;
        BPtr->foo();
        EXPECT_EQ(s_BFoo,true);
        EXPECT_EQ(s_AFoo,false);
        
        s_BFoo = false;
        s_AFoo = false;
        APtr->foo();
        EXPECT_EQ(s_BFoo,true);
        EXPECT_EQ(s_AFoo,false);
    }
    EXPECT_EQ(s_ACounter,0);
    EXPECT_EQ(s_BCounter,0);
    
    resetVar();
    {
        SCObjPtrT<ObjPtrA> APtr;
        APtr.createInstance();
        APtr->foo();
        EXPECT_EQ(s_BFoo,false);
        EXPECT_EQ(s_AFoo,true);
    }
    EXPECT_EQ(s_ACounter,0);
}

TEST(TestSCObjPtr, StrongCast)
{
    resetVar();
    {
        SCObjPtrT<ObjPtrA> APtr;
        APtr.createInstance();
        
        ObjPtrB::Ptr BPtr = APtr.cast<ObjPtrB::Ptr>();
        EXPECT_EQ(s_ACounter,1);
        EXPECT_EQ(s_BCounter,0);
        EXPECT_EQ(BPtr==NULL,true);
    }
    EXPECT_EQ(s_ACounter,0);
    
    resetVar();
    {
        SCObjPtrT<ObjPtrA> APtr;
        SCObjPtrT<ObjPtrB> BPtr = APtr.cast<ObjPtrB::Ptr>();
        EXPECT_EQ(s_ACounter,0);
        EXPECT_EQ(s_BCounter,0);
        EXPECT_EQ(BPtr==NULL,true);
    }
    EXPECT_EQ(s_ACounter,0);
    
    resetVar();
    {
        SCObjPtrT<ObjPtrB> BPtr;
        BPtr.createInstance();
        SCObjPtrT<ObjPtrA> APtr = BPtr;
        SCObjPtrT<ObjPtrB> CPtr = APtr.cast<ObjPtrB::Ptr>();
        
        EXPECT_EQ(s_ACounter,1);
        EXPECT_EQ(s_BCounter,1);
        EXPECT_EQ(CPtr!=NULL,true);
        EXPECT_EQ(BPtr==CPtr,true);
        
        CPtr->foo();
        EXPECT_EQ(s_BFoo,true);
        EXPECT_EQ(s_AFoo,false);
    }
    EXPECT_EQ(s_ACounter,0);
}


TEST(TestSCObjPtr, WeakCast)
{
    resetVar();
    {
        SCObjPtrT<ObjPtrA> APtr0;
        APtr0.createInstance();
        
        SCObjPtrT<ObjPtrA,false> APtr = APtr0;
        SCObjPtrT<ObjPtrB,false> BPtr = APtr.cast<ObjPtrB>();
        EXPECT_EQ(s_ACounter,1);
        EXPECT_EQ(s_BCounter,0);
        EXPECT_EQ(BPtr==NULL,true);
    }
    EXPECT_EQ(s_ACounter,0);
    
    resetVar();
    {
        SCObjPtrT<ObjPtrA> APtr;
        SCObjPtrT<ObjPtrB> BPtr = APtr.cast<ObjPtrB::Ptr>();
        EXPECT_EQ(s_ACounter,0);
        EXPECT_EQ(s_BCounter,0);
        EXPECT_EQ(BPtr==NULL,true);
    }
    EXPECT_EQ(s_ACounter,0);
    
    resetVar();
    {
        SCObjPtrT<ObjPtrB> BPtr;
        BPtr.createInstance();
        SCObjPtrT<ObjPtrA,false> APtr = BPtr;
        
        EXPECT_EQ(s_ACounter,1);
        EXPECT_EQ(s_BCounter,1);
        EXPECT_EQ(APtr!=NULL,true);
        
        APtr->foo();
        EXPECT_EQ(s_BFoo,true);
        EXPECT_EQ(s_AFoo,false);
    }
    EXPECT_EQ(s_ACounter,0);
    
    resetVar();
    {
        SCObjPtrT<ObjPtrB> BPtr;
        BPtr.createInstance();
        SCObjPtrT<ObjPtrA,false> APtr = BPtr;
        SCObjPtrT<ObjPtrB,false> CPtr = APtr.cast<ObjPtrB>();
        
        EXPECT_EQ(s_ACounter,1);
        EXPECT_EQ(s_BCounter,1);
        EXPECT_EQ(CPtr!=NULL,true);
        EXPECT_EQ(BPtr==CPtr,true);
        
        CPtr->foo();
        EXPECT_EQ(s_BFoo,true);
        EXPECT_EQ(s_AFoo,false);
    }
    EXPECT_EQ(s_ACounter,0);
}



