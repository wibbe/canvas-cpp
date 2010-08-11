
#ifndef CANVAS_MUTEX_HEADER
#define CANVAS_MUTEX_HEADER

#include <pthread.h>

namespace canvas
{
   class Mutex
   {
      public:
         Mutex();
         ~Mutex();
         
         void lock();
         void unlock();
         
      private:
         pthread_mutex_t m_mutex;
   };
}

#endif

