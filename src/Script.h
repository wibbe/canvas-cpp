
#ifndef CANVAS_SCRIPT_HEADER
#define CANVAS_SCRIPT_HEADER

#include <v8.h>
#include <string>
#include <vector>

namespace canvas
{
   class Script
   {
      public:
      
         Script(v8::Handle<v8::Context> context);
         ~Script();
         
         bool load(std::string const& filename);
         bool load(std::vector<std::string> const& files);
         
         bool runString(std::string const& string, std::string const& filename = "");
         
         /// Returns a global script object that match the supplied name.
         v8::Local<v8::Value> getObject(std::string const& name);
         
         v8::Handle<v8::Context> context() const { return m_context; }
         
      private:
      
         v8::Persistent<v8::Context>   m_context;
   };
}

#endif

