
#ifndef CANVAS_THREAD_HEADER
#define CANVAS_THREAD_HEADER

#include <pthread.h>

namespace canvas
{
   class Thread
   {
      public:
         Thread();
         virtual ~Thread();
         
         virtual void run() = 0;
         
         void stop() { m_running = false; }
        
      protected:
         bool m_running;
         
      private:
         pthread_t   m_thread;
   };
}

#endif