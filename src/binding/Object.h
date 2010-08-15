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

#ifndef V8_SCRIPT_OBJECT_HPP
#define V8_SCRIPT_OBJECT_HPP

#include "v8.h"
#include <string>
#include <cassert>
#include <iostream>

#include "Function.h"
#include "Attribute.h"
#include "FunctionInfo.h"

namespace binding {

   extern v8::Handle<v8::Value> scriptCallback(v8::Arguments const& args);
   extern v8::Handle<v8::Value> scriptConstructor(v8::Arguments const& args);
   
   extern void attributeSetCallback(v8::Local<v8::String> name, v8::Local<v8::Value> value, v8::AccessorInfo const& info);
   extern v8::Handle<v8::Value> attributeGetCallback(v8::Local<v8::String> name, v8::AccessorInfo const& info);


   template <typename T>
   class Object
   {
      public:
         
         /// Copy constructor
         Object(Object const& other)
         {
            m_functionTemplate = v8::Persistent<v8::FunctionTemplate>::New(other.m_functionTemplate);
         }
      
         Object(std::string const& name)
         {
            v8::Handle<v8::FunctionTemplate> functionTemplate = v8::FunctionTemplate::New(&scriptConstructor);
            functionTemplate->SetClassName(v8::String::New(name.c_str()));
            functionTemplate->InstanceTemplate()->SetInternalFieldCount(1);
            
            m_functionTemplate = v8::Persistent<v8::FunctionTemplate>::New(functionTemplate);
         }
         
         v8::Handle<v8::FunctionTemplate> getFunction()
         {
            return m_functionTemplate;
         }
         
         template <typename Fun>
         Object<T> & function(std::string const& name, Fun func)
         {
            addCallback(name, new binding::Functor<T, typename FunctionInfo<Fun>::Return, typename FunctionInfo<Fun>::Params>(func));
            return *this;
         }
         
         /// Make it posible to bind 'ordinary' v8 callback functions.
         Object<T> & function(std::string const& name, v8::InvocationCallback callback)
         {
            v8::Handle<v8::ObjectTemplate> protoTempl = m_functionTemplate->PrototypeTemplate();
            protoTempl->Set(v8::String::New(name.c_str()), v8::FunctionTemplate::New(callback));

            return *this;
         }

         template <typename AttribT>
         Object<T> & attribute(std::string const& name, AttribT T::*ptr)
         {
            v8::Handle<v8::ObjectTemplate> instaTempl = m_functionTemplate->InstanceTemplate();
            
            BaseAttribute * attrib = new AttributePtr<T, AttribT>(ptr);
            
            instaTempl->SetAccessor(v8::String::New(name.c_str()), 
                                    attributeGetCallback, 
                                    attributeSetCallback, 
                                    v8::External::Wrap(attrib));
            return *this;
         }
         
         template <typename GetT, typename SetT>
         Object<T> & attribute(std::string const& name, GetT get, SetT set)
         {
            v8::Handle<v8::ObjectTemplate> instaTempl = m_functionTemplate->InstanceTemplate();
            
            BaseAttribute * attrib = new AttributeCallback<T, GetT, SetT>(get, set);
            
            instaTempl->SetAccessor(v8::String::New(name.c_str()), 
                                    attributeGetCallback, 
                                    attributeSetCallback, 
                                    v8::External::Wrap(attrib));
            return *this;
         }
         
         template <typename AttribT>
         Object<T> & getter(std::string const& name, AttribT T::*ptr)
         {
            v8::Handle<v8::ObjectTemplate> instaTempl = m_functionTemplate->InstanceTemplate();
            
            BaseAttribute * attrib = new AttributePtr<T, AttribT>(ptr);
            
            instaTempl->SetAccessor(v8::String::New(name.c_str()), 
                                    attributeGetCallback, 
                                    0, 
                                    v8::External::Wrap(attrib));
            return *this;
         }
         
         /**
          * Transform an object from C++ to Javascript.
          */
         v8::Handle<v8::Object> wrap(T * object)
         {
            v8::HandleScope scope;
            
            //if (!object)
            //   scope.Close(v8::Undefined());
               
            v8::Local<v8::Object> result = m_functionTemplate->GetFunction()->NewInstance();
            result->SetInternalField(0, v8::External::New(object));
            
            return scope.Close(result);
         }
         
         /**
          * Transform a Javascript object to C++.
          */
         static inline T * unwrap(v8::Local<v8::Object> obj)
         {
            v8::HandleScope scope;
            v8::Local<v8::External> field = v8::Local<v8::External>::Cast(obj->GetInternalField(0));
            void* ptr = field->Value();
            return static_cast<T *>(ptr);
         }
         
      private:
         void addCallback(std::string const& name, binding::BaseFunctor * functor)
         {
            v8::Handle<v8::ObjectTemplate> protoTempl = m_functionTemplate->PrototypeTemplate();
            protoTempl->Set(v8::String::New(name.c_str()), v8::FunctionTemplate::New(&scriptCallback, v8::External::Wrap(functor)));
         }
         
      private:
         v8::Persistent<v8::FunctionTemplate>   m_functionTemplate;
   };

}

#endif

