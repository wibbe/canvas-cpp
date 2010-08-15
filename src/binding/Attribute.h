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

#ifndef V8_SCRIPT_ATTRIBUTE_HPP
#define V8_SCRIPT_ATTRIBUTE_HPP

#include "v8.h"
#include "Translate.h"
#include "FunctionInfo.h"

namespace binding {

   class BaseAttribute
   {
      public:
         virtual v8::Handle<v8::Value> get(v8::AccessorInfo const& info)
         {
            return v8::Undefined();
         }
         
         virtual void set(v8::Handle<v8::Value> const& value, v8::AccessorInfo const& info)
         {
         }
   };

   template <typename ObjectT, typename AttribT>
   class AttributePtr : public BaseAttribute
   {
         typedef AttribT ObjectT::*Ptr;
         
      public:
         AttributePtr(Ptr ptr)
            : m_ptr(ptr)
         { }
      
         virtual v8::Handle<v8::Value> get(v8::AccessorInfo const& info)
         {
            ObjectT * object = Object<ObjectT>::unwrap(info.Holder());
            return Translate<AttribT>::from(object->*m_ptr);
         }
         
         virtual void set(v8::Handle<v8::Value> const& value, v8::AccessorInfo const& info)
         {
            ObjectT * object = Object<ObjectT>::unwrap(info.Holder());
            (object->*m_ptr) = Translate<AttribT>::to(value);
         }
         
      private:
         Ptr m_ptr;
   };
   
   template <typename ObjectT, typename GetT, typename SetT>
   class AttributeCallback : public BaseAttribute
   {
         typedef typename FunctionInfo<GetT>::Return  ReturnType;
         typedef typename TL::TypeAtNonStrict<typename FunctionInfo<SetT>::Params, EmptyType, 0>::Result SetType;
      
      public:
         AttributeCallback(GetT getMethod, SetT setMethod)
            : m_getMethod(getMethod),
              m_setMethod(setMethod)
         { }

         virtual v8::Handle<v8::Value> get(v8::AccessorInfo const& info)
         {
            ObjectT * object = Object<ObjectT>::unwrap(info.Holder());
            
            return Translate<ReturnType>::from(((*object).*m_getMethod)());
         }
      
         virtual void set(v8::Handle<v8::Value> const& value, v8::AccessorInfo const& info)
         {
            ObjectT * object = Object<ObjectT>::unwrap(info.Holder());
            ((*object).*m_setMethod)(Translate<SetType>::to(value));
         }
      
      private:
         GetT m_getMethod;
         SetT m_setMethod;
   };

}

#endif

