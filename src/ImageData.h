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

#ifndef IMAGE_DATA_HEADER
#define IMAGE_DATA_HEADER

#include <core/SkBitmap.h>
#include "Canvas.h"

namespace canvas
{
   
   class ImageData
   {
      public:
         ImageData(void * data, int width, int height, Canvas::Format format);
         ImageData(ImageData const& other);
         
         ~ImageData();
         
         int width() const;
         int height() const;
         void setWidth(int);
         void setHeight(int);
         
         SkBitmap const& bitmap() const { return *m_bitmap; }
         
      private:
         SkBitmap * m_bitmap;
         Canvas::Format m_format;
   };
   
}

#endif
