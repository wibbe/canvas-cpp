
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
      
      m_fillPaint.setAntiAlias(true);
      m_fillPaint.setStyle(SkPaint::kFill_Style);
      m_strokePaint.setAntiAlias(true);
      m_strokePaint.setStyle(SkPaint::kStroke_Style);
   }
   
   Context::~Context()
   {
   }
   
   void Context::copyImageTo(void * target)
   {
      void * source = m_bitmap->getPixels();
      memcpy(target, source, m_bitmap->getSize());
   }
   
   void Context::scale(float x, float y)
   {
      m_canvas->scale(x, y);
   }
   
   void Context::rotate(float angle)
   {
      m_canvas->rotate(angle);
   }
   
   void Context::translate(float x, float y)
   {
      m_canvas->translate(x, y);
   }
   
   void Context::beginPath()
   {
      m_path.reset();
   }
   
   void Context::closePath()
   {
      
   }

   void Context::fill()
   {
      m_canvas->drawPath(m_path, m_fillPaint);
   }
   
   void Context::stroke()
   {
      m_canvas->drawPath(m_path, m_strokePaint);
   }
   
   void Context::clip()
   {
      
   }

   void Context::moveTo(float x, float y)
   {
      m_path.moveTo(x, y);
   }
   
   void Context::lineTo(float x, float y)
   {
      m_path.lineTo(x, y);
   }
   
   void Context::fillRect(float x, float y, float width, float height)
   {
      m_canvas->drawRect(SkRect::MakeXYWH(x, y, width, height), m_fillPaint);
   }
   
   void Context::strokeRect(float x, float y, float width, float height)
   {
      m_canvas->drawRect(SkRect::MakeXYWH(x, y, width, height), m_strokePaint);
   }
}

