
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
            m_painter->start();
            
            while (m_running)
            {
               m_painter->draw();
            };
         }
      
      private:
         Painter * m_painter;
   };
   
   /// Holds all private data for the Canvas class.
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

   Canvas::Canvas(Canvas const& other)
   {
   }
   
   Canvas & Canvas::operator = (Canvas const& other)
   {
   }
   
   Canvas::~Canvas()
   {
   }
   
   bool Canvas::isDirty() const
   {
      return true;
   }
   
   void Canvas::paint(void * imageData)
   {
      assert(imageData && "No image data supplied to paint method.");
      assert(m_data->painter && "Must load a javascript before any painting is performed.");
      
      if (!m_data->threaded)
         m_data->painter->draw();

      m_data->painter->copyImageTo(imageData);
   }
   
   void Canvas::loadFile(std::string const& filename)
   {
      assert(!m_data->painter && "Only one script per canvas is allowed!");
      
      m_data->painter = new Painter(m_data->width, m_data->height, filename);
      
      if (m_data->threaded)
         m_data->thread = new CanvasThread(m_data->painter);
      else
         m_data->painter->start();
   }
   
   void Canvas::loadCode(std::string const& code)
   {
      assert(!m_data->painter && "Only one script per canvas is allowed!");
      
      m_data->painter = new Painter(m_data->width, m_data->height, code, false);
      
      if (m_data->threaded)
         m_data->thread = new CanvasThread(m_data->painter);
      else
         m_data->painter->start();
   }
   
   std::string Canvas::lastLogEntry()
   {
      assert(m_data->painter);
      return m_data->painter->lastLogEntry();
   }
   
}

