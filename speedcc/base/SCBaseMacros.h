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


#ifndef __SPEEDCC__SCBASEMACROS_H__
#define __SPEEDCC__SCBASEMACROS_H__

#include <assert.h>


////------------------

#ifdef COCOS2D_DEBUG
#define SPEEDCC_DEBUG
#endif

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

// assert at debug and release
#define SCASSERTR(_condition_) \
	assert((_condition_))

// assert at debug
#ifdef SPEEDCC_DEBUG
#define SCASSERT(_condition_)  assert((_condition_))
#else
#define SCASSERT(_condition_)
#endif

// SPEEDCC_TEST_MODE

#define SC_IN_RANGE(_v_,_min_,_max_)\
    MAX((_min_),MIN((_max_),(_v_)))

#define SC_ARRAY_LENGTH(_array_)\
    (sizeof(_array_)/sizeof((_array_)[0]))

#define SC_NEW(_class_)\
    SCMemAllocator::newObject<_class_>()

#define SC_NEW_ARG(_class_,_arg_)\
    SCMemAllocator::newObject<_class_>((_arg_))

#define SC_DELETE(_pointer_)\
    do{\
        if((_pointer_)) {SCMemAllocator::deleteObject((_pointer_));}\
        (_pointer_) = nullptr;\
    }while(0)

#define SCMapInsert(_map_,_key_,_value_)\
    (_map_).insert(std::remove_reference<decltype(_map_)>::type::value_type((_key_),(_value_)))

#define SCLogR(_format_, ...)\
    SpeedCC::SCSystem::log((_format_), ##__VA_ARGS__)

#define SC_STRONG_TYPEDEF(_type_, new_type) \
    typedef SpeedCC::SCStrongTypedefT<_type_, struct sc_shadow_type##new_type> new_type

#ifdef SPEEDCC_DEBUG
#define SCLog  SCLogR
#else
#define SCLog(_format_, ...)
#endif

#define SCAutoLock(_lock_)\
    std::lock_guard<decltype(_lock_)> SPEEDCC_locker((_lock_))

#define SC_MAKE_WORD(_hight_,_low_)\
    (((_hight_)<<8)|(_low_))

#define SC_NUM_2_PVOID(_num_) \
    ((void*)(long)(_num_))

#define SC_PVOID_2_NUM(_p_) \
    ((int)(long)(void*)(_p_))

///------- execute flow control short name
#define SC_CONTINUE_IF(_condition_)\
    if((_condition_)) {continue;}

#define SC_RETURN_IF(_condition_,_result_)\
    if((_condition_)) {return (_result_);}

#define SC_RETURN_IF_LOG(_condition_,_result_,_log_,...)\
    if((_condition_)) {SCLog((_log_),##__VA_ARGS__); return (_result_);}

#define SC_RETURN_V_IF(_condition_)\
    if((_condition_)) {return;}

#define SC_BREAK_IF(_condition_)\
    if((_condition_)) break;


///----- bit test
// match any one of bit
#define SC_BIT_HAS_OR(_set_,_bit_)\
    (((_set_)&(_bit_)) ? true : false)

// match all bits
#define SC_BIT_HAS_AND(_set_,_bit_)\
    ((((_set_)&(_bit_))==(_bit_)) ? true : false)

// add bits
#define SC_BIT_ADD(_set_,_bit_)\
    ((_set_)|(_bit_))

// remove bits
#define SC_BIT_REMOVE(_set_,_bit_)\
    ((_set_)&(~(_bit_)))

///------- class relate
#define SC_AVOID_CLASS_COPY(_class_) \
    _class_(const _class_&)= delete; \
    _class_& operator=(const _class_&)= delete;

#define SC_DEFINE_CLASS_PTR(_class_) \
    typedef SpeedCC::SCObjPtrT<_class_>              Ptr; \
    typedef SpeedCC::SCObjPtrT<_class_,false>        WeakPtr;

#define SC_HAS_CLASS(_ptr_,_class_) \
    ((_ptr_).cast<_class_>()!=nullptr)


#define SC_DEFINE_CREATE_FUNC_0(_class_)\
    static typename _class_::Ptr create(){\
        typename _class_::Ptr ptrRet;\
        ptrRet.createInstanceWithCon([](void* pData){\
                                        new(pData)_class_();\
                                    });\
        return ptrRet;\
    }

#define SC_DEFINE_CREATE_FUNC_1(_class_,_type1_)\
    static typename _class_::Ptr create(_type1_ arg1){\
        typename _class_::Ptr ptrRet;\
        ptrRet.createInstanceWithCon([&arg1](void* pData){\
                                        new(pData)_class_(arg1);\
                                    });\
        return ptrRet;\
    }

#define SC_DEFINE_CREATE_FUNC_2(_class_,_type1_,_type2_)\
    static typename _class_::Ptr create(_type1_ arg1,_type2_ arg2){\
        typename _class_::Ptr ptrRet;\
        ptrRet.createInstanceWithCon([&arg1,&arg2](void* pData){\
                                        new(pData)_class_(arg1,arg2);\
                                    });\
        return ptrRet;\
    }

#define SC_DEFINE_CREATE_FUNC_3(_class_,_type1_,_type2_,_type3_)\
    static typename _class_::Ptr create(_type1_ arg1,_type2_ arg2,_type3_ arg3){\
        typename _class_::Ptr ptrRet;\
        ptrRet.createInstanceWithCon([&arg1,&arg2,&arg3](void* pData){\
                                        new(pData)_class_(arg1,arg2,arg3);\
                                    });\
        return ptrRet;\
    }

#define SC_DEFINE_CREATE_FUNC_4(_class_,_type1_,_type2_,_type3_,_type4_)\
    static typename _class_::Ptr create(_type1_ arg1,_type2_ arg2,_type3_ arg3,_type4_ arg4){\
        typename _class_::Ptr ptrRet;\
        ptrRet.createInstanceWithCon([&arg1,&arg2,&arg3,&arg4](void* pData){\
                                        new(pData)_class_(arg1,arg2,arg3,arg4);\
                                    });\
        return ptrRet;\
    }


#define SC_MAKE_FUNC(_func_,_p_) \
SpeedCC::SCBindFuncUtilsT<SpeedCC::SCTraitMemberFuncT<decltype((&std::remove_pointer<decltype((_p_))>::type::_func_))>::ArgCount>::makeFunc(&std::remove_pointer<decltype((_p_))>::type::_func_,(_p_))

//#define SC_TRAITS_PTR_CLASS(_ptr_) \
//    decltype(_ptr_)::type

///--------- SPEEDCCD version
#define SPEEDCC_VERSION_MAJOR                       ((SPEEDCC_VERSION & 0x00ff0000)>>(4*4))
#define SPEEDCC_VERSION_MINOR                       ((SPEEDCC_VERSION & 0x0000ff00)>>(4*2))
#define SPEEDCC_VERSION_FIX                         ((SPEEDCC_VERSION & 0x000000ff))


#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#else
#ifndef INT64
#define INT64       long long
#endif
#endif

#define NAMESPACE_SPEEDCC_BEGIN namespace SpeedCC {
#define NAMESPACE_SPEEDCC_END		}

#endif //__SPEEDCC__SCBASEMACROS_H__
