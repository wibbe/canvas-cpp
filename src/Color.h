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

#ifndef CANVAS_COLOR_HEADER
#define CANVAS_COLOR_HEADER

#include <cmath>

namespace canvas
{

   class Color
   {
      public:
         Color()
            :  r(0.0f),
               g(0.0f),
               b(0.0f),
               a(1.0f)
         { }
         
         Color(float r, float g, float b, float a = 1.0f)
            :  r(r),
               g(g),
               b(b),
               a(a)
         { }
         
         Color(int r, int g, int b, int a = 255)
            :  r(r / 255.0f),
               g(g / 255.0f),
               b(b / 255.0f),
               a(a / 255.0f)
         { }
         
         Color(Color const& c)
            :  r(c.r),
               g(c.g),
               b(c.b),
               a(c.a)
         { }
         
         bool operator == (Color const& other)
         {
            return std::abs(r - other.r) < 1e-5f &&
                   std::abs(g - other.g) < 1e-5f &&
                   std::abs(b - other.b) < 1e-5f &&
                   std::abs(a - other.a) < 1e-5f;
         }
         
         
         float r, g, b, a;
   };

}

#endif

