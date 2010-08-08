
#include "Context.h"

namespace canvas
{
   
   Context::Context(int width, int height)
      : m_bitmap(0),
        m_device(0),
        m_canvas(0),
        m_parser(),
        m_width(width),
        m_height(height)
   {
      m_bitmap = new SkBitmap();
      m_bitmap->setConfig(SkBitmap::kARGB_8888_Config, width, height);
      m_bitmap->allocPixels();
      m_bitmap->eraseARGB(0, 0, 0, 0);
      
      m_device = new SkDevice(*m_bitmap);
      m_canvas = new SkCanvas(m_device);
   }
   
   Context::~Context()
   {
   }
   
   void Context::beginPath()
   {
   }
   
   void Context::closePath()
   {
      
   }

   void Context::fill()
   {
      
   }
   
   void Context::stroke()
   {
      
   }
   
   void Context::clip()
   {
      
   }

   void Context::moveTo(float x, float y)
   {
      
   }
   
   void Context::lineTo(float x, float y)
   {
      
   }
   
   void Context::rect(float x, float y, float width, float height)
   {

   }
   
}