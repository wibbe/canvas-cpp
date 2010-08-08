
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
      std::cerr << "Constructor called" << std::endl;
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

