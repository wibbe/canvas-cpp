
#ifndef CANVAS_CALLBACK_HEADER
#define CANVAS_CALLBACK_HEADER

#include <v8.h>

namespace canvas
{
   class Callback
   {
      public:
      
         Callback(v8::Handle<v8::Function> func)
         {
            m_function = v8::Persistent<v8::Function>::New(func);
         }
         
         v8::Handle<v8::Value> call()
         {
            return m_function->Call(m_function, 0, NULL);
         }
         
      private:
      
         v8::Persistent<v8::Function>  m_function;
   };
}

#endif

