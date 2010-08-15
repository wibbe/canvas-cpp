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

#include "Object.h"

namespace binding {

   v8::Handle<v8::Value> scriptCallback(v8::Arguments const& args)
   {
      v8::HandleScope scope;
      BaseFunctor * func = static_cast<BaseFunctor *>(v8::External::Unwrap(args.Data()));
      return scope.Close(func->call(args));
   }
   
   v8::Handle<v8::Value> scriptConstructor(v8::Arguments const& args)
   {
      return v8::Undefined();
   }
   
   void attributeSetCallback(v8::Local<v8::String> name, v8::Local<v8::Value> value, v8::AccessorInfo const& info)
   {
      v8::HandleScope scope;
      BaseAttribute * attrib = static_cast<BaseAttribute*>(v8::External::Unwrap(info.Data()));
      attrib->set(value, info);
   }
   
   v8::Handle<v8::Value> attributeGetCallback(v8::Local<v8::String> name, v8::AccessorInfo const& info)
   {
      v8::HandleScope scope;
      BaseAttribute * attrib = static_cast<BaseAttribute*>(v8::External::Unwrap(info.Data()));
      return scope.Close(attrib->get(info));
   }

}

