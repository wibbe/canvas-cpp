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

#ifndef V8_SCRIPT_FUNCTION_INFO_HPP
#define V8_SCRIPT_FUNCTION_INFO_HPP

#include "Types.h"
#include "TypeList.h"

namespace binding {

   template <typename Fun>
   struct FunctionInfo;


   template <typename O, typename R>
   struct FunctionInfo<R (O::*)()>
   {
      typedef O Object;
      typedef R Return;
      typedef NullType Params;
      
      static const bool Const = false;
   };

   template <typename O, typename R, typename P1>
   struct FunctionInfo<R (O::*)(P1)>
   {
      typedef O Object;
      typedef R Return;
      typedef TYPELIST_1(P1) Params;
      
      static const bool Const = false;   
   };
   
   template <typename O, typename R, typename P1, typename P2>
   struct FunctionInfo<R (O::*)(P1, P2)>
   {
      typedef O Object;
      typedef R Return;
      typedef TYPELIST_2(P1, P2) Params;
      
      static const bool Const = false;   
   };
   
   template <typename O, typename R, typename P1, typename P2, typename P3>
   struct FunctionInfo<R (O::*)(P1, P2, P3)>
   {
      typedef O Object;
      typedef R Return;
      typedef TYPELIST_3(P1, P2, P3) Params;
      
      static const bool Const = false;   
   };
   
   template <typename O, typename R, typename P1, typename P2, typename P3, typename P4>
   struct FunctionInfo<R (O::*)(P1, P2, P3, P4)>
   {
      typedef O Object;
      typedef R Return;
      typedef TYPELIST_4(P1, P2, P3, P4) Params;
      
      static const bool Const = false;   
   };
   
   template <typename O, typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
   struct FunctionInfo<R (O::*)(P1, P2, P3, P4, P5)>
   {
      typedef O Object;
      typedef R Return;
      typedef TYPELIST_5(P1, P2, P3, P4, P5) Params;
      
      static const bool Const = false;   
   };
   
   template <typename O, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
   struct FunctionInfo<R (O::*)(P1, P2, P3, P4, P5, P6)>
   {
      typedef O Object;
      typedef R Return;
      typedef TYPELIST_6(P1, P2, P3, P4, P5, P6) Params;
      
      static const bool Const = false;   
   };
   
   
   // - Const definitions

   template <typename O, typename R>
   struct FunctionInfo<R (O::*)() const>
   {
      typedef O Object;
      typedef R Return;
      typedef NullType Params;
      
      static const bool Const = true;
   };

   template <typename O, typename R, typename P1>
   struct FunctionInfo<R (O::*)(P1) const>
   {
      typedef O Object;
      typedef R Return;
      typedef TYPELIST_1(P1) Params;
      
      static const bool Const = true;   
   };
   
   template <typename O, typename R, typename P1, typename P2>
   struct FunctionInfo<R (O::*)(P1, P2) const>
   {
      typedef O Object;
      typedef R Return;
      typedef TYPELIST_2(P1, P2) Params;
      
      static const bool Const = true;
   };
   
   template <typename O, typename R, typename P1, typename P2, typename P3>
   struct FunctionInfo<R (O::*)(P1, P2, P3) const>
   {
      typedef O Object;
      typedef R Return;
      typedef TYPELIST_3(P1, P2, P3) Params;
      
      static const bool Const = true;   
   };
   
   template <typename O, typename R, typename P1, typename P2, typename P3, typename P4>
   struct FunctionInfo<R (O::*)(P1, P2, P3, P4) const>
   {
      typedef O Object;
      typedef R Return;
      typedef TYPELIST_4(P1, P2, P3, P4) Params;
      
      static const bool Const = true;   
   };
   
   template <typename O, typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
   struct FunctionInfo<R (O::*)(P1, P2, P3, P4, P5) const>
   {
      typedef O Object;
      typedef R Return;
      typedef TYPELIST_5(P1, P2, P3, P4, P5) Params;
      
      static const bool Const = true;   
   };
   
   template <typename O, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
   struct FunctionInfo<R (O::*)(P1, P2, P3, P4, P5, P6) const>
   {
      typedef O Object;
      typedef R Return;
      typedef TYPELIST_6(P1, P2, P3, P4, P5, P6) Params;
      
      static const bool Const = true;
   };

}

#endif

