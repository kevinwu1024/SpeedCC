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


#ifndef __SPEEDCC__SCTEMPLATEDEF_H__
#define __SPEEDCC__SCTEMPLATEDEF_H__

#include "SCBaseMacros.h"
#include <type_traits>
#include <tuple>

NAMESPACE_SPEEDCC_BEGIN

// atom special class
struct SCClassNull;
    
struct SCClassEmpty{};
    
template<typename T>
struct SCShadowClassT{typedef T type;};
    
template<>
struct SCShadowClassT<SCClassNull> {typedef SCClassEmpty type;};
    
// judgement class
template<typename T>
struct SCIsNullClassT { enum {value=std::is_same<T,SCClassNull>::value};};
    
template<typename T>
struct SCIsEmptyClassT { enum {value=std::is_same<T,SCClassEmpty>::value};};
    
    
///---------- SCGetIndexByClassT
template <typename T, typename Tuple>
struct SCGetIndexByClassT { enum {value=0}; };
    
template <typename T, typename ...Ts>
struct SCGetIndexByClassT<T, std::tuple<T, Ts...>> { enum {value=0}; };
    
template <typename T1, typename T2, typename ...Ts>
struct SCGetIndexByClassT<T1, std::tuple<T2, Ts...>>
{
    enum {value = (1 + SCGetIndexByClassT<T1, std::tuple<Ts...>>::value)};
};
    
///----------- SCTraitMemberFunc
template <typename>
struct SCTraitMemberFuncT;
    
template <typename T1, typename T2, typename ...Ts>
struct SCTraitMemberFuncT<T1 (T2::*)(Ts...)>
{
    typedef T1 return_type;
    typedef T2 class_type;
    typedef T2& class_reference;
        
    enum {ArgCount = sizeof...(Ts)};
};
    
template <typename T1, typename T2, typename ...Ts>
struct SCTraitMemberFuncT<T1 (T2::*)(Ts...) const>
{
    typedef T1 return_type;
    typedef T2 class_type;
    typedef T2 const& class_reference;
        
    enum {ArgCount = sizeof...(Ts)};
};
    
///--------------  detect class internal type define
template<typename T>
struct SCDefineVoidT
{
    typedef void type;
};
    
template<typename T1, typename T2 = void>
struct SCHasInternalTypeT
{
    enum { value = 0 };
};
    
template<typename T>
struct SCHasInternalTypeT<T, typename SCDefineVoidT<typename T::type>::type>
{
    enum { value = 1 };
};

    
NAMESPACE_SPEEDCC_END


#endif // __SPEEDCC__SCTEMPLATEDEF_H__
