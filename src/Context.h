
#ifndef CANVAS_CONTEXT_HEADER
#define CANVAS_CONTEXT_HEADER

#include <core/SkBitmap.h>
#include <core/SkDevice.h>
#include <core/SkPaint.h>
#include <core/SkPath.h>
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
         
         void copyImageTo(unsigned char * target);
         
         // Transformations
         void scale(float x, float y);
         void rotate(float angle);
         void translate(float x, float y);
         
         // Path functions
         void beginPath();
         void closePath();
         
         void fill();
         void stroke();
         void clip();
         
         void moveTo(float x, float y);
         void lineTo(float x, float y);
         
         void fillRect(float x, float y, float width, float height);
         void strokeRect(float x, float y, float width, float height);
        
      private:
         
         SkBitmap * m_bitmap;
         SkDevice * m_device;
         SkCanvas * m_canvas;
         SkPath m_path;
         
         SkPaint m_fillPaint;
         SkPaint m_strokePaint;
         
         ColorParser m_parser;
         
         int m_width;
         int m_height;
   };
   
}

#endif

