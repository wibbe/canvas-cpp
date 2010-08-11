
#ifndef V8_SCRIPT_ATTRIBUTE_HPP
#define V8_SCRIPT_ATTRIBUTE_HPP

#include "v8.h"
#include "Translate.h"

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

}

#endif

