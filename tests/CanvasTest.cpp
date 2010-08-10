
#include <tut/tut.hpp>
#include "Canvas.h"

using namespace canvas;

namespace tut
{
   struct CanvasData
   {
      Canvas  * canvas;
   };
   
   test_group<CanvasData> canvasTest("Canvas");
   typedef test_group<CanvasData>::object object;
   
   template <>
   template <>
   void object::test<1>()
   {
      set_test_name("Canvas allocation");
      
      canvas = new Canvas(100, 100, false);
      delete canvas;
   }
}