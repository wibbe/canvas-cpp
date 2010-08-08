
#include "Canvas.h"
#include "Context.h"
#include "Painter.h"
#include "util/Thread.h"

#include <cassert>

namespace canvas
{
   class CanvasThread : public Thread
   {
      public:
         CanvasThread(Painter * painter)
            : Thread(),
              m_painter(painter)
         { }
         
         void run()
         {
            while (m_running)
            {
               m_painter->draw();
            };
         }
      
      private:
         Painter * m_painter;
   };
   
   class CanvasData
   {
      public:
         CanvasData()
            : width(0),
              height(0),
              threaded(false),
              painter(0),
              thread(0)
         { }
         
         ~CanvasData()
         {
            if (thread)
            {
               thread->stop();
               delete thread;
            }
            
            delete painter;
         }
         
         int width;
         int height;
         bool threaded;
         Painter * painter;
         Thread * thread;
   };
   
   Canvas::Canvas(int width, int height, bool threaded)
      : m_data(new CanvasData())
   {
      m_data->width = width;
      m_data->height = height;
      m_data->threaded = threaded;
   }
   
   Canvas::~Canvas()
   {
   }
   
   bool Canvas::isDirty() const
   {
      return false;
   }
   
   void Canvas::render(unsigned char * imageData)
   {
      if (!m_data->threaded)
         m_data->painter->draw();

      m_data->painter->copyImageData(imageData);
   }
   
   void Canvas::loadScript(std::string const& filename)
   {
      assert(!m_data->painter && "Only allow one script per canvas is allowed!");
      
      m_data->painter = new Painter(m_data->width, m_data->height, filename);
      
      if (m_data->threaded)
         m_data->thread = new CanvasThread(m_data->painter);
   }
   
}