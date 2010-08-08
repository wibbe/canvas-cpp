
#include "Painter.h"
#include "util/ScopedLock.h"

#include <iostream>

namespace canvas
{
   
   Painter::Painter(int width, int height, std::string const& filename)
      : m_mutex(),
        m_script(0),
        m_context(0),
        m_callbackIndex(0),
        m_windowBinding("Window"),
        m_contextBinding("Context")
   {
      v8::HandleScope scope;
      
      // Create V8 context
      m_scriptTemplate = v8::Persistent<v8::ObjectTemplate>::New(v8::ObjectTemplate::New());
      v8::Local<v8::Context> context = v8::Local<v8::Context>::New(v8::Context::New(0, m_scriptTemplate));
      
      // Create bindings
      m_windowBinding.function("setInterval", &Painter::setInterval)
                     .function("clearInterval", &Painter::clearInterval)
                     .function("getContext", &Painter::getContext)
                     .function("log", &Painter::log);
                     
                     
      // Create graphics context
      m_context = new Context(width, height);
      
      // Load script from file
      m_script = new Script(context);
      m_script->load(filename);
   }
   
   Painter::~Painter()
   {
      delete m_script;
      delete m_context;
   }
   
   void Painter::draw()
   {
      ScopedLock lock(m_mutex);
      
      // Call all registered callbacks
      v8::HandleScope scope;
      v8::Context::Scope contextScope(m_script->context());
      v8::TryCatch tryCatch;
   
      CallbackMap::iterator it = m_callbacks.begin();
      CallbackMap::iterator end = m_callbacks.end();
      
      for (; it != end; ++it)
      {
         Callback & callback = it->second;
         
         v8::Handle<v8::Value> result = callback.call();
         if (result.IsEmpty())
         {
            v8::String::Utf8Value error(tryCatch.Exception());
            std::cerr << "Script Error: " << *error << std::endl;
         }
      }
   }
   
   void Painter::copyImageData(unsigned char * data)
   {
      ScopedLock lock(m_mutex);
   }
   
   int Painter::setInterval(v8::Handle<v8::Function> const& function)
   {
      m_callbacks.insert(std::make_pair(++m_callbackIndex, Callback(function)));
      return m_callbackIndex;
   }
   
   void Painter::clearInterval(int index)
   {
      CallbackMap::iterator result = m_callbacks.find(index);
      if (result != m_callbacks.end())
         m_callbacks.erase(result);
   }
   
   v8::Handle<v8::Value> Painter::getContext(std::string const& type)
   {
      v8::HandleScope scope;
      if (type == "2d")
         return scope.Close(m_contextBinding.wrap(m_context));
      
      std::cerr << "Error: Requested wrong context type '" << type << "'" << std::endl;
      return scope.Close(v8::Undefined());
   }
   
   void Painter::log(std::string const& log)
   {
      std::cerr << "Log: " << log << std::endl;
   }
   
}