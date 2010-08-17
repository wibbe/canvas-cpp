/**
 * Copyright (c) 2010 Daniel Wiberg
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

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
         CanvasThread(Painter * painter, std::string fileOrCode, bool isFile)
            : Thread(),
              m_painter(painter),
              m_fileOrCode(fileOrCode),
              m_isFile(isFile)
         { }
         
         void run()
         {
            m_painter->start(m_fileOrCode, m_isFile);
            
            while (m_running)
            {
               m_painter->draw();
            };
         }
      
      private:
         Painter * m_painter;
         std::string m_fileOrCode;
         bool m_isFile;
   };
   
   /// Holds all private data for the Canvas class.
   class CanvasData
   {
      public:
         CanvasData()
            : threaded(false),
              started(false),
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
         
         bool threaded;
         bool started;
         Painter * painter;
         Thread * thread;
   };
   
   
   Canvas::Canvas(int width, int height, Format format, bool threaded)
      : m_data(new CanvasData())
   {
      m_data->threaded = threaded;
      m_data->painter = new Painter(width, height, format);
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
      assert(m_data->started && "Must load a javascript before any painting is performed.");
      
      if (!m_data->threaded)
         m_data->painter->draw();

      if (imageData)
         m_data->painter->copyImageTo(imageData);
   }
   
   void Canvas::startWithFile(std::string const& filename)
   {
      assert(!m_data->started && "Only one script per canvas is allowed!");
      
      m_data->started = true;
      
      if (m_data->threaded)
         m_data->thread = new CanvasThread(m_data->painter, filename, true);
      else
         m_data->painter->start(filename, true);
   }
   
   void Canvas::startWithCode(std::string const& code)
   {
      assert(!m_data->started && "Only one script per canvas is allowed!");
      
      m_data->started = true;
      
      if (m_data->threaded)
         m_data->thread = new CanvasThread(m_data->painter, code, false);
      else
         m_data->painter->start(code, false);
   }
   
   void Canvas::registerImage(std::string const& name, int width, int height, Format format, void * data)
   {
      assert(m_data->painter);
      
      m_data->painter->registerImage(name, new ImageData(data, width, height, format));
   }
   
   std::string Canvas::lastLogEntry()
   {
      assert(m_data->painter);
      return m_data->painter->lastLogEntry();
   }
   
}

