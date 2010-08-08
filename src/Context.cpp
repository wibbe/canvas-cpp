
#include "Context.h"

namespace canvas
{
   class ContextData
   {
      public:
         ContextData()
         { }
         
         ~ContextData()
         { }
         
   };
   
   Context::Context(int width, int height)
      : m_data(new ContextData())
   {
   }
   
   Context::~Context()
   {
   }
   
}