
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

