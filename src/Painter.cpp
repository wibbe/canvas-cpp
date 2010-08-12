
#include "Painter.h"
#include "util/ScopedLock.h"

#include <iostream>

namespace canvas
{
   
   Painter::Painter(int width, int height, std::string const&  fileOrCode, bool isFile)
      : m_painterMutex(),
        m_logMutex(),
        m_script(0),
        m_context(0),
        m_callbackIndex(0),
        m_windowBinding(0),
        m_contextBinding(0)
   {
      v8::HandleScope scope;
      
      // Create V8 context
      m_scriptTemplate = v8::Persistent<v8::ObjectTemplate>::New(v8::ObjectTemplate::New());
      v8::Local<v8::Context> jsContext = v8::Local<v8::Context>::New(v8::Context::New(0, m_scriptTemplate));

      
      // Create bindings
      m_windowBinding = new binding::Object<Painter>("Window");
      m_windowBinding->function("setInterval", &Painter::setInterval)
                     .function("clearInterval", &Painter::clearInterval)
                     .function("getContext", &Painter::getContext)
                     .function("log", &Painter::log);
      
      m_contextBinding = new binding::Object<Context>("Context");
      m_contextBinding->function("scale", &Context::scale)
                      .function("rotate", &Context::rotate)
                      .function("translate", &Context::translate)
                      .function("beginPath", &Context::beginPath)
                      .function("closePath", &Context::closePath)
                      .function("moveTo", &Context::moveTo)
                      .function("lineTo", &Context::lineTo)
                      .function("fillRect", &Context::fillRect)
                      .function("strokeRect", &Context::strokeRect);
      
      v8::Context::Scope contextScope(jsContext);
      
      // Inject the window object
      jsContext->Global()->Set(v8::String::New("window"), m_windowBinding->wrap(this));
                     
      // Create graphics context
      m_context = new Context(width, height);
      
      // Create javascript object
      m_script = new Script(jsContext);
      if (isFile)
         m_script->load(fileOrCode);
      else
         m_script->runString(fileOrCode);
   }
   
   Painter::~Painter()
   {
      delete m_script;
      delete m_context;
   }
   
   void Painter::draw()
   {
      ScopedLock lock(m_painterMutex);
      
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
   
   void Painter::copyImageTo(unsigned char * target)
   {
      ScopedLock lock(m_painterMutex);
      if (target)
         m_context->copyImageTo(target);
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
         return scope.Close(m_contextBinding->wrap(m_context));
      
      std::cerr << "Error: Requested wrong context type '" << type << "'" << std::endl;
      return v8::Undefined();
   }
   
   void Painter::log(std::string const& log)
   {
      ScopedLock lock(m_logMutex);
      
      m_history.push_back(log);
      
      // We only store a 1000 log entries
      if (m_history.size() > 1000)
         m_history.pop_front();
         
      std::cerr << log << std::endl;
   }
   
   std::string Painter::lastLogEntry()
   {
      ScopedLock lock(m_logMutex);
      
      if (m_history.empty())
         return "";
      
      std::string log = m_history.front();
      m_history.pop_front();
      return log;
   }
   
}

