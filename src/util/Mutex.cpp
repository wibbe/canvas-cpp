
#include "util/Mutex.h"

namespace canvas
{
   
   Mutex::Mutex()
   {
      pthread_mutex_init(&m_mutex, 0);
   }
   
   Mutex::~Mutex()
   {
      pthread_mutex_destroy(&m_mutex);
   }
   
   void Mutex::lock()
   {
      pthread_mutex_lock(&m_mutex);
   }
   
   void Mutex::unlock()
   {
      pthread_mutex_unlock(&m_mutex);
   }
}

