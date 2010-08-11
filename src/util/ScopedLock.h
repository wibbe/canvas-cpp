
#ifndef CANVAS_SCOPED_LOCK_HEADER
#define CANVAS_SCOPED_LOCK_HEADER

#include "util/Mutex.h"

namespace canvas
{
   class ScopedLock
   {
      public:
         ScopedLock(Mutex & mutex);
         ~ScopedLock();
         
      private:
         Mutex & m_mutex;
   };
}

#endif

