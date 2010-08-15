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
/**
 * The Translate struct is used to transform ordinary datatypes to and from
 * thier javascript counterparts.
 */
 
#ifndef V8_SCRIPT_TRANSLATE_HPP
#define V8_SCRIPT_TRANSLATE_HPP

#include "v8.h"
#include <string>
#include <cassert>

#include "Types.h"

namespace binding {

   // Forward declarations
   template <typename Type> class Object;
   
   template <typename T> struct Translate;
   
   template <>
   struct Translate<EmptyType>
   {
      static EmptyType to(v8::Handle<v8::Value> const& value)
      {
         return EmptyType();
      }
   };
   
   template <>
   struct Translate<bool>
   {
      static bool to(v8::Handle<v8::Value> const& value)
      {
         return value->BooleanValue();
      }
      
      static v8::Handle<v8::Value> from(bool value)
      {
         return v8::Boolean::New(value);
      }
   };

   template <>
   struct Translate<char>
   {
      static char to(v8::Handle<v8::Value> const& value)
      {
         return value->Int32Value();  
      }
      
      static v8::Handle<v8::Value> from(char value)
      {
         return v8::Int32::New(value);
      }
   };
   
   template <>
   struct Translate<unsigned char>
   {
      static unsigned char to(v8::Handle<v8::Value> const& value)
      {
         return value->Uint32Value(); 
      }
      
      static v8::Handle<v8::Value> from(unsigned char value)
      {
         return v8::Uint32::New(value);
      }
   };

   template <>
   struct Translate<short>
   {
      static short to(v8::Handle<v8::Value> const& value)
      {
         return value->Int32Value();   
      }
      
      static v8::Handle<v8::Value> from(short value)
      {
         return v8::Int32::New(value);
      }
   };
   
   template <>
   struct Translate<unsigned short>
   {
      static unsigned short to(v8::Handle<v8::Value> const& value)
      {
         return value->Uint32Value();   
      }
      
      static v8::Handle<v8::Value> from(unsigned short value)
      {
         return v8::Uint32::New(value);
      }
   };

   template <>
   struct Translate<int>
   {
      static int to(v8::Handle<v8::Value> const& value)
      {
         return value->Int32Value();   
      }
      
      static v8::Handle<v8::Value> from(int value)
      {
         return v8::Int32::New(value);
      }
   };
   
   template <>
   struct Translate<unsigned int>
   {
      static unsigned int to(v8::Handle<v8::Value> const& value)
      {
         return value->Uint32Value();   
      }
      
      static v8::Handle<v8::Value> from(unsigned int value)
      {
         return v8::Uint32::New(value);
      }
   };
   
   template <>
   struct Translate<long>
   {
      static long to(v8::Handle<v8::Value> const& value)
      {
         return value->Int32Value();   
      }
      
      static v8::Handle<v8::Value> from(long value)
      {
         return v8::Int32::New(value);
      }
   };
   
   template <>
   struct Translate<unsigned long>
   {
      static unsigned long to(v8::Handle<v8::Value> const& value)
      {
         return value->Uint32Value();   
      }
      
      static v8::Handle<v8::Value> from(unsigned long value)
      {
         return v8::Uint32::New(value);
      }
   };
   
   template <>
   struct Translate<float>
   {
      static float to(v8::Handle<v8::Value> const& value)
      {
         return value->NumberValue();
      }
      
      static v8::Handle<v8::Value> from(float value)
      {
         return v8::Number::New(value);
      }
   };
   
   template <>
   struct Translate<double>
   {
      static double to(v8::Handle<v8::Value> const& value)
      {
         return value->NumberValue();
      }
      
      static v8::Handle<v8::Value> from(double value)
      {
         return v8::Number::New(value);
      }
   };
   
   template <>
   struct Translate<std::string>
   {
      static std::string to(v8::Handle<v8::Value> const& value)
      {
         return *v8::String::Utf8Value(value);
      }
      
      static v8::Handle<v8::Value> from(std::string const& value)
      {
         return v8::String::New(value.c_str());
      }
   };
   
   template <>
   struct Translate<std::string const&>
   {
      static std::string to(v8::Handle<v8::Value> const& value)
      {
         return *v8::String::Utf8Value(value);
      }
      
      static v8::Handle<v8::Value> from(std::string const& value)
      {
         return v8::String::New(value.c_str());
      }
   };
   
   template <>
   struct Translate<v8::Handle<v8::Function> >
   {
      static v8::Handle<v8::Function> to(v8::Handle<v8::Value> const& value)
      {
         assert(value->IsFunction());
         return v8::Handle<v8::Function>::Cast(value);
      }
      
      static v8::Handle<v8::Value> from(v8::Handle<v8::Function> const& value)
      {
         return value;
      }
   };
   
   template <>
   struct Translate<v8::Handle<v8::Function> const&>
   {
      static v8::Handle<v8::Function> to(v8::Handle<v8::Value> const& value)
      {
         assert(value->IsFunction());
         return v8::Handle<v8::Function>::Cast(value);
      }
      
      static v8::Handle<v8::Value> from(v8::Handle<v8::Function> const& value)
      {
         return value;
      }
   };
   
   template <>
   struct Translate<v8::Handle<v8::Value> >
   {
      static v8::Handle<v8::Value> to(v8::Handle<v8::Value> const& value)
      {
         return value;
      }
      
      static v8::Handle<v8::Value> from(v8::Handle<v8::Value> const& value)
      {
         return value;
      }
   };
/*   
   template <typename T>
   struct Translate
   {
      static T * to(v8::Handle<v8::Value> const& value)
      {
         return Object<T>::unwrap(value);
      }
      
      static v8::Handle<v8::Value> from(T * value)
      {
         return Object<T>::wrap(value);
      } 
   };
*/
}

#endif

