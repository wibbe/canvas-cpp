/**
 * Copyright (c) 2010 Daniel Wiberg
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef V8_SCRIPT_TYPE_LIST_HPP
#define V8_SCRIPT_TYPE_LIST_HPP

#include "Types.h"

/**
* Convinient macros for defining typelists.
*/
#define TYPELIST_1(T1) \
 TypeList<T1, NullType>
#define TYPELIST_2(T1, T2) \
 TypeList<T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1, T2, T3) \
 TypeList<T1, TYPELIST_2(T2, T3) >
#define TYPELIST_4(T1, T2, T3, T4) \
 TypeList<T1, TYPELIST_3(T2, T3, T4) >
#define TYPELIST_5(T1, T2, T3, T4, T5) \
 TypeList<T1, TYPELIST_4(T2, T3, T4, T5) >
#define TYPELIST_6(T1, T2, T3, T4, T5, T6) \
 TypeList<T1, TYPELIST_5(T2, T3, T4, T5, T6) >
#define TYPELIST_7(T1, T2, T3, T4, T5, T6, T7) \
 TypeList<T1, TYPELIST_6(T2, T3, T4, T5, T6, T7) >
#define TYPELIST_8(T1, T2, T3, T4, T5, T6, T7, T8) \
 TypeList<T1, TYPELIST_7(T2, T3, T4, T5, T6, T7, T8) >
#define TYPELIST_9(T1, T2, T3, T4, T5, T6, T7, T8, T9) \
 TypeList<T1, TYPELIST_8(T2, T3, T4, T5, T6, T7, T8, T9) >
#define TYPELIST_10(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) \
 TypeList<T1, TYPELIST_9(T2, T3, T4, T5, T6, T7, T8, T9, T10) >

/**
* Servs as a collection of types, implemented as a list.
*/
template <class T, class U>
struct TypeList
{
   typedef T Head;
   typedef U Tail;
};    

namespace TL {
  
   /**
    * Calculates the lenth of a typelist.
    */
   template <class TList> struct Length;
   
   template <> struct Length<NullType>
   {
      enum { Value = 0 };
   };
   
   template <class T, class U>
   struct Length< TypeList<T, U> >
   {
      enum { Value = 1 + Length<U>::Value };
   };
   
   /**
    * Access a type by index in a typelist.
    */
   template <class TList, unsigned int index> struct TypeAt;
   
   template <class Head, class Tail>
   struct TypeAt<TypeList<Head, Tail>, 0>
   {
      typedef Head Result;
   };
   
   template <class Head, class Tail, unsigned int i>
   struct TypeAt<TypeList<Head, Tail>, i>
   {
      typedef typename TypeAt<Tail, i - 1>::Result Result;
   };
   
   /**
    * Access a type by index. If index is outside of list,
    * a default value is returned.
    */
   template <class TList, class Default, unsigned int index> struct TypeAtNonStrict;
   
   template <class Head, class Tail, class Default>
   struct TypeAtNonStrict<TypeList<Head, Tail>, Default, 0>
   {
      typedef Head Result;
   };
   
   template <class Default, unsigned int index>
   struct TypeAtNonStrict<NullType, Default, index>
   {
      typedef Default Result;
   };
   
   template <class Head, class Tail, class Default, unsigned int index>
   struct TypeAtNonStrict<TypeList<Head, Tail>, Default, index>
   {
      typedef typename TypeAtNonStrict<Tail, Default, index - 1>::Result Result;
   };
   

}

#endif

