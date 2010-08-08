
#ifndef CANVAS_CONTEXT_HEADER
#define CANVAS_CONTEXT_HEADER

#include <memory>

namespace canvas
{
   class ContextData;
   
   class Context
   {
      public:
         Context(int width, int height);
         ~Context();
        
      private:
         std::auto_ptr<ContextData> m_data;
   };
   
}

#endif