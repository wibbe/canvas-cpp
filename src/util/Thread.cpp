
#include "util/Thread.h"

namespace canvas
{

   static void * pthreadRun(void * arg)
   {
      Thread * thread = static_cast<Thread*>(arg);
      thread->run();
      return 0;
   }
   
   Thread::Thread()
      : m_running(true)
   {
      pthread_create(&m_thread, 0, pthreadRun, this);
   }
   
   Thread::~Thread()
   {
      void * exitStatus;
      pthread_join(m_thread, &exitStatus);
   }
   
}