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

#ifndef CANVAS_CONTEXT_HEADER
#define CANVAS_CONTEXT_HEADER

#include <core/SkBitmap.h>
#include <core/SkDevice.h>
#include <core/SkPaint.h>
#include <core/SkPath.h>
#include <core/SkPaint.h>

#include <v8.h>

#include <list>
#include <cassert>

#include "State.h"
#include "Canvas.h"
#include "ColorParser.h"
#include "ImageData.h"

namespace canvas
{
   class ContextData;
   
   class Context
   {
      public:
         Context(int width, int height, Canvas::Format format);
         ~Context();
         
         void copyImageTo(void * target);
         
         // Styles
         float lineWidth() const;
         void setLineWidth(float width);
         
         std::string lineCap() const;
         void setLineCap(std::string const& cap);
         
         std::string strokeStyle() const;
         void setStrokeStyle(std::string const& style);
         std::string fillStyle() const;
         void setFillStyle(std::string const& style);
         
         float globalAlpha() const;
         void setGlobalAlpha(float alpha);
         
         // Transformations
         void scale(float x, float y);
         void rotate(float angle);
         void translate(float x, float y);
         
         // Image function
         void drawImage(v8::Handle<v8::Value> image, float x, float y, float width, float height);
         
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
         
         void clear();
         
      private:
         inline State & currentState() { return m_stateStack.back(); }
         inline State const& currentState() const { return m_stateStack.back(); }
        
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
         Canvas::Format m_format;
         
         std::list<State> m_stateStack;
   };
   
}

#endif

