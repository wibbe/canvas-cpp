
#ifndef CANVAS_PAINTER_HEADER
#define CANVAS_PAINTER_HEADER

#include <string>
#include <list>
#include <map>
#include <v8.h>
#include "Script.h"
#include "Context.h"
#include "Callback.h"
#include "util/Mutex.h"
#include "binding/Object.h"

namespace canvas
{
   class Painter
   {
         typedef std::map<int, Callback> CallbackMap;
         
      public:
         Painter(int width, int height, std::string const& fileOrCode, bool isFile = true);
         ~Painter();
         
         void draw();
         
         void copyImageData(unsigned char * data);
         
         int setInterval(v8::Handle<v8::Function> const& function);
         void clearInterval(int index);
         
         v8::Handle<v8::Value> getContext(std::string const& type);
         
         /// Store a string in the log history.
         void log(std::string const& log);
         
         /// Returns the oldest entry in the history, 
         /// while also poping it from the list.
         std::string lastLogEntry();
         
      private:
         Mutex m_painterMutex;
         Mutex m_logMutex;
         Script * m_script;
         Context * m_context;
         
         /// Stores the log history
         std::list<std::string> m_history;
         
         CallbackMap m_callbacks;
         int m_callbackIndex;
         
         binding::Object<Painter> * m_windowBinding;
         binding::Object<Context> * m_contextBinding;
         
         v8::Persistent<v8::ObjectTemplate> m_scriptTemplate;
   };
}

#endif

