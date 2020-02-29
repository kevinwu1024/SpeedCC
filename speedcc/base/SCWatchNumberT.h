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

#ifndef __SPEEDCC__SCWATCHNUMBERT_H__
#define __SPEEDCC__SCWATCHNUMBERT_H__

#include "SCBaseMacros.h"
#include "SCObject.h"
#include "SCString.h"

NAMESPACE_SPEEDCC_BEGIN

#define SC_DEFINE_NUMBER_OPERATOR(_opr_) \
    template<typename T2>\
    T2 operator _opr_ (const T2 num) {\
        return this->_number _opr_ num;\
    }
    
#define SC_DEFINE_NUMBER_CONSTRUCTOR(_type_) \
    SCWatchNumberT(const _type_ num):\
    _number(0),\
    _nIDCounter(0),\
    _funGetString(nullptr){\
        this->_number = (T)(num);\
    }
    
    
#define SC_DEFINE_NUMBER_GLOBAL1(_opr_,_ret_type_) \
    template<typename T> \
    _ret_type_ operator _opr_ (const SCWatchNumberT<T>& num1,const SCWatchNumberT<T>& num2) {\
        return num1.getValue() _opr_ num2.getValue();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const int num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getValue();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const unsigned int num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getValue();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const char num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getValue();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const unsigned char num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getValue();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const short num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getValue();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const unsigned short num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getValue();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const long num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getValue();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const unsigned long num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getValue();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const float num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getValue();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const double num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getValue()();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const INT64 num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getValue();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const bool num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getValue();\
    }
 
#define SC_DEFINE_NUMBER_GLOBAL2(_opr1_,_opr2_) \
    template<typename T2>\
    T2 operator _opr1_ (T2& num1,const SCWatchNumberT<T2>& num) {\
        T2 ret = num1 _opr2_ num.getValue();\
        num1 = ret;\
        return ret;\
    }
    
#define SC_DEFINE_NUMBER_OPERATOR2(_opr1_,_opr2_) \
    template<typename T2>\
    SCWatchNumberT& operator _opr1_ (const T2 num) {\
        const T oldNum = _number;\
        const T2 ret = _number _opr2_ num;\
        if((_number == ret)){\
            return *this;\
        }\
        _number = ret;\
        this->firePostUpdateFun(_number,oldNum);\
        return *this;\
    }
    
template<typename T,typename = typename std::enable_if<std::is_arithmetic<T>::value,T>::type>
class SCWatchNumberT : public SCObject
{
public:
    typedef T  type;
        
    SCWatchNumberT(const SCWatchNumberT& num):
    _number(num._number),
    _nIDCounter(0),
    _funGetString(nullptr)
    {
    }

    SC_DEFINE_CLASS_PTR(SCWatchNumberT)
        
    SC_DEFINE_CREATE_FUNC_0(SCWatchNumberT)
    SC_DEFINE_CREATE_FUNC_1(SCWatchNumberT,const T)
        
    SC_DEFINE_NUMBER_CONSTRUCTOR(int)
    SC_DEFINE_NUMBER_CONSTRUCTOR(unsigned int)
    SC_DEFINE_NUMBER_CONSTRUCTOR(char)
    SC_DEFINE_NUMBER_CONSTRUCTOR(unsigned char)
    SC_DEFINE_NUMBER_CONSTRUCTOR(short)
    SC_DEFINE_NUMBER_CONSTRUCTOR(unsigned short)
    SC_DEFINE_NUMBER_CONSTRUCTOR(long)
    SC_DEFINE_NUMBER_CONSTRUCTOR(unsigned long)
    SC_DEFINE_NUMBER_CONSTRUCTOR(INT64)
    SC_DEFINE_NUMBER_CONSTRUCTOR(float)
    SC_DEFINE_NUMBER_CONSTRUCTOR(double)
        
    inline operator int() const {return (int)_number;}
    inline operator unsigned int() const {return (unsigned int)_number;}
    inline operator long() const {return (long)_number;}
    inline operator unsigned long() const {return (unsigned long)_number;}
    inline operator char() const {return (char)_number;}
    inline operator unsigned char() const {return (unsigned char)_number;}
    inline operator INT64() const {return (INT64)_number;}
    inline operator float() const {return (float)_number;}
    inline operator double() const {return (double)_number;}
        
    inline bool operator<(const T num) { return _number<num; }
    inline bool operator<=(const T num) { return _number<=num; }
    inline bool operator>(const T num) { return _number>num; }
    inline bool operator>=(const T num) { return _number>=num; }
    inline bool operator==(const T num) { return _number==num; }
    inline bool operator!=(const T num) { return _number!=num; }
        
    inline bool operator<(const SCWatchNumberT num) { return _number<num._number; }
    inline bool operator<=(const SCWatchNumberT num) { return _number<=num._number; }
    inline bool operator>(const SCWatchNumberT num) { return _number>num._number; }
    inline bool operator>=(const SCWatchNumberT num) { return _number>=num._number; }
    inline bool operator==(const SCWatchNumberT num) { return _number==num._number; }
    inline bool operator!=(const SCWatchNumberT num) { return _number!=num._number; }
        
    SC_DEFINE_NUMBER_OPERATOR(+)
    SC_DEFINE_NUMBER_OPERATOR(-)
    SC_DEFINE_NUMBER_OPERATOR(*)
    SC_DEFINE_NUMBER_OPERATOR(/)
    SC_DEFINE_NUMBER_OPERATOR(%)
    SC_DEFINE_NUMBER_OPERATOR(^)
    SC_DEFINE_NUMBER_OPERATOR(&)
        
    SC_DEFINE_NUMBER_OPERATOR2(+=,+)
    SC_DEFINE_NUMBER_OPERATOR2(-=,-)
    SC_DEFINE_NUMBER_OPERATOR2(*=,*)
    SC_DEFINE_NUMBER_OPERATOR2(/=,/)
    SC_DEFINE_NUMBER_OPERATOR2(%=,%)
    SC_DEFINE_NUMBER_OPERATOR2(^=,^)
    SC_DEFINE_NUMBER_OPERATOR2(&=,&)
        
    SC_DEFINE_NUMBER_OPERATOR2(<<=,<<)
    SC_DEFINE_NUMBER_OPERATOR2(>>=,>>)
        
        
    template<typename T2,
    typename = typename std::enable_if<std::is_arithmetic<T2>::value && !std::is_same<T2,T>::value,T>::type>
    SCWatchNumberT& operator=(const SCWatchNumberT<T2>& num)
    {
        const T oldNum = _number;
        const bool bDiff = (oldNum!=(T)num._number);
            
        if(!bDiff) {return *this;}
            
        _number = (T)num._number;
        this->firePostUpdateFun(_number,oldNum);
            
        return *this;
    }
        
        
    SCWatchNumberT& operator=(const SCWatchNumberT& num)
    {
        const T oldNum = _number;
        const bool bDiff = (oldNum!=(T)num._number);
            
        if(!bDiff) {return *this;}
            
        _number = num._number;
        this->firePostUpdateFun(_number,oldNum);
            
        return *this;
    }
        
    template<typename T2,
    typename = typename std::enable_if<std::is_arithmetic<T2>::value,T>::type>
    SCWatchNumberT& operator=(const T2 num)
    {
        const T oldNum = _number;
        bool bDiff = (oldNum!=num);
            
        if(!bDiff) {return *this;}
            
        _number = num;
        this->firePostUpdateFun(num,oldNum);
            
        return *this;
    }
        
    // prefix ++ (++a)
    template<typename Q = T>
    typename std::enable_if< std::is_integral<Q>::value,SCWatchNumberT& >::type operator++()
    {
        const Q oldNum = _number;
        const Q num = _number + 1;
        _number += 1;
        this->firePostUpdateFun(num,oldNum);
        return *this;
    }
        
    // postfix ++ (a++)
    template<typename Q = T>
    typename std::enable_if< std::is_integral<Q>::value,SCWatchNumberT >::type
    operator++(Q)
    {
        SCWatchNumberT result(*this);
        ++(*this);
        return result;
    }
        
    // prefix -- (--a)
    template<typename Q = T>
    typename std::enable_if< std::is_integral<Q>::value,SCWatchNumberT& >::type
    operator--()
    {
        const Q oldNum = _number;
        const Q num = _number - 1;
        _number -= 1;
        this->firePostUpdateFun(num,oldNum);
        return *this;
    }
        
    // postfix -- (a--)
    template<typename Q = T>
    typename std::enable_if< std::is_integral<Q>::value,SCWatchNumberT >::type
    operator--(Q)
    {
        SCWatchNumberT result(*this);
        --(*this);
        return result;
    }
        

    int addUpdateFunc(const std::function<void(Ptr pNum,const T newNumber,const T oldNumber)>& fun)
    {
        ++_nIDCounter;
        _postUpdateFunMap[_nIDCounter] = fun;
        return _nIDCounter;
    }
        
    void removeUpdateFunc(const int nID)
    {
        if(_postUpdateFunMap.find(nID)!=_postUpdateFunMap.end())
        {
            _postUpdateFunMap.erase(nID);
        }
    }
        
    void setGetStringFun(const std::function<SCString(const T num)>& fun)
    {
        _funGetString = fun;
    }
        
    SCString getString()
    {
        if(_funGetString)
        {
            return _funGetString(_number);
        }
            
        return SCString(_number);
    }

    inline T getValue() const {return _number;}
        
protected:
    SCWatchNumberT():
    _number(0),
    _nIDCounter(0),
    _funGetString(nullptr)
    {}
        
    void firePostUpdateFun(const T newNumber,const T oldNumber)
    {
        if(newNumber==oldNumber)
        {
            return;
        }
            
        for(const auto& it : _postUpdateFunMap)
        {
            it.second(this->makeObjPtr<SCWatchNumberT::Ptr>(),newNumber,oldNumber);
        }
    }
        
private:
    T                   _number;
    int                 _nIDCounter;
    std::map<int,std::function<void(Ptr ptrNum,
                                    const T newNumber,
                                    const T oldNumber)> >    _postUpdateFunMap;
    std::function<SCString(const T num)>      _funGetString;
};
    
    
template<>
class SCWatchNumberT<bool> : public SCObject
{
public:
    SC_DEFINE_CLASS_PTR(SCWatchNumberT<bool>)
    typedef bool  type;
        
    SC_DEFINE_CREATE_FUNC_0(SCWatchNumberT<bool>)
    SC_DEFINE_CREATE_FUNC_1(SCWatchNumberT<bool>,const bool)
        
    inline operator bool() const {return _number;}
    inline bool operator==(const bool num) { return _number==num; }
    inline bool operator!=(const bool num) { return _number!=num; }
        
    template<typename T2,
    typename = typename std::enable_if<std::is_arithmetic<T2>::value && !std::is_same<T2,bool>::value,bool>::type>
    SCWatchNumberT& operator=(const SCWatchNumberT<T2>& num)
    {
        const bool oldNum = _number;
        const bool bDiff = (oldNum!=(num._number==0 ? false : true));
            
        if(!bDiff) {return *this;}
            
        _number = (num._number==0 ? false : true);
        this->firePostUpdateFun(_number,!_number);
            
        return *this;
    }
        
    SCWatchNumberT& operator=(const bool num)
    {
        const bool oldNum = _number;
        bool bDiff = (oldNum!=num);
            
        if(!bDiff) {return *this;}
            
        _number = num;
        this->firePostUpdateFun(num,!num);
            
        return *this;
    }
        
    int addUpdateFunc(const std::function<void(Ptr ptrNum,const bool bNew,const bool bOld)>& fun)
    {
        ++_nIDCounter;
        _postUpdateFunMap[_nIDCounter] = fun;
        return _nIDCounter;
    }
        
    void removeUpdateFunc(const int nID)
    {
        if(_postUpdateFunMap.find(nID)!=_postUpdateFunMap.end())
        {
            _postUpdateFunMap.erase(nID);
        }
    }
        
    SCString getString() const
    {
        return _number ? "true" : "false";
    }
        
    inline bool getValue() const {return _number;}
        
protected:
    SCWatchNumberT():
    _number(false),
    _nIDCounter(0)
    {
    }
        
    SCWatchNumberT(const bool num):
    _number(num),
    _nIDCounter(0)
    {
    }
        
    void firePostUpdateFun(const bool bNew,const bool bOld)
    {
        for(const auto& it : _postUpdateFunMap)
        {
            it.second(this->makeObjPtr<SCWatchNumberT<bool>::Ptr>(), bNew,bOld);
        }
    }
        
protected:
    SCWatchNumberT(const SCWatchNumberT& num):
    _number(num._number),
    _nIDCounter(0)
    {
    }
        
private:
    bool                   _number;
    int                 _nIDCounter;
    std::map<int,std::function<void(Ptr ptrNum,
                                    const bool bNew,const bool bOld)> >    _postUpdateFunMap;
};
    
SC_DEFINE_NUMBER_GLOBAL1(+,SCWatchNumberT<T>)
SC_DEFINE_NUMBER_GLOBAL1(-,SCWatchNumberT<T>)
SC_DEFINE_NUMBER_GLOBAL1(*,SCWatchNumberT<T>)
SC_DEFINE_NUMBER_GLOBAL1(/,SCWatchNumberT<T>)
SC_DEFINE_NUMBER_GLOBAL1(%,SCWatchNumberT<T>)
SC_DEFINE_NUMBER_GLOBAL1(^,SCWatchNumberT<T>)
SC_DEFINE_NUMBER_GLOBAL1(&,SCWatchNumberT<T>)
    
SC_DEFINE_NUMBER_GLOBAL1(>,bool)
SC_DEFINE_NUMBER_GLOBAL1(>=,bool)
SC_DEFINE_NUMBER_GLOBAL1(<,bool)
SC_DEFINE_NUMBER_GLOBAL1(<=,bool)
SC_DEFINE_NUMBER_GLOBAL1(==,bool)
SC_DEFINE_NUMBER_GLOBAL1(!=,bool)

SC_DEFINE_NUMBER_GLOBAL2(+=,+)
SC_DEFINE_NUMBER_GLOBAL2(-=,-)
SC_DEFINE_NUMBER_GLOBAL2(*=,*)
SC_DEFINE_NUMBER_GLOBAL2(/=,/)
SC_DEFINE_NUMBER_GLOBAL2(%=,%)
SC_DEFINE_NUMBER_GLOBAL2(^=,^)
SC_DEFINE_NUMBER_GLOBAL2(&=,&)
    
SC_DEFINE_NUMBER_GLOBAL2(<<=,<<)
SC_DEFINE_NUMBER_GLOBAL2(>>=,>>)
    

typedef SCWatchNumberT<short>                        SCWatchShort;
typedef SCWatchNumberT<unsigned short>               SCWatchUShort;
typedef SCWatchNumberT<char>                         SCWatchChar;
typedef SCWatchNumberT<unsigned char>                SCWatchByte;
typedef SCWatchNumberT<int>                          SCWatchInt;
typedef SCWatchNumberT<unsigned int>                 SCWatchUInt;
typedef SCWatchNumberT<long>                         SCWatchLong;
typedef SCWatchNumberT<unsigned long>                SCWatchULong;
typedef SCWatchNumberT<INT64>                        SCWatchInt64;
typedef SCWatchNumberT<float>                        SCWatchFloat;
typedef SCWatchNumberT<double>                       SCWatchDouble;
typedef SCWatchNumberT<bool>                         SCWatchBool;
    
class SCWatchString;
    
typedef std::tuple<SCWatchShort,
                    SCWatchUShort,
                    SCWatchChar,
                    SCWatchByte,
                    SCWatchInt,
                    SCWatchUInt,
                    SCWatchLong,
                    SCWatchULong,
                    SCWatchInt64,
                    SCWatchFloat,
                    SCWatchDouble,
                    SCWatchBool>        SCWatchNumberList_t;
    
typedef std::tuple<SCWatchShort,
                    SCWatchUShort,
                    SCWatchChar,
                    SCWatchByte,
                    SCWatchInt,
                    SCWatchUInt,
                    SCWatchLong,
                    SCWatchULong,
                    SCWatchInt64,
                    SCWatchFloat,
                    SCWatchDouble>        SCWatchNumberableList_t;
    
typedef std::tuple<SCWatchShort,
                    SCWatchUShort,
                    SCWatchChar,
                    SCWatchByte,
                    SCWatchInt,
                    SCWatchUInt,
                    SCWatchLong,
                    SCWatchULong,
                    SCWatchInt64>           SCWatchNumberIntegerList_t;
    
typedef std::tuple<SCWatchShort,
                        SCWatchUShort,
                        SCWatchChar,
                        SCWatchByte,
                        SCWatchInt,
                        SCWatchUInt,
                        SCWatchLong,
                        SCWatchULong,
                        SCWatchInt64,
                        SCWatchFloat,
                        SCWatchDouble,
                        SCWatchBool,
                        SCWatchString>     SCWatchClassList_t;
    
template<typename T>
struct SCIsWatchNumberT {enum {value=(SCGetIndexByClassT<T,SCWatchNumberList_t>::value== std::tuple_size<SCWatchNumberList_t>::value) ? 0 : 1};};
    
template<typename T>
struct SCIsWatchNumberableT  {enum {value=(SCGetIndexByClassT<T,SCWatchNumberableList_t>::value== std::tuple_size<SCWatchNumberableList_t>::value) ? 0 : 1};};
    
template<typename T>
struct SCIsWatchNumberIntegerT  {enum {value=(SCGetIndexByClassT<T,SCWatchNumberIntegerList_t>::value== std::tuple_size<SCWatchNumberIntegerList_t>::value) ? 0 : 1};};
    
template<typename T>
struct SCIsWatchClassT {enum {value=(SCGetIndexByClassT<T,SCWatchClassList_t>::value==std::tuple_size<SCWatchClassList_t>::value) ? 0 : 1};};
    
NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCWATCHNUMBERT_H__
