
#ifndef CANVAS_CONTEXT_HEADER
#define CANVAS_CONTEXT_HEADER

#include <core/SkBitmap.h>
#include <core/SkDevice.h>
#include <core/SkPaint.h>

#include "ColorParser.h"

namespace canvas
{
   class ContextData;
   
   class Context
   {
      public:
         Context(int width, int height);
         ~Context();
         
         // Path functions
         void beginPath();
         void closePath();
         
         void fill();
         void stroke();
         void clip();
         
         void moveTo(float x, float y);
         void lineTo(float x, float y);
         
         void rect(float x, float y, float width, float height);
        
      private:
         
         SkBitmap * m_bitmap;
         SkDevice * m_device;
         SkCanvas * m_canvas;
         
         ColorParser m_parser;
         
         int m_width;
         int m_height;
   };
   
}

#endif