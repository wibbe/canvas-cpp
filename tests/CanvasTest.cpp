
#include <tut/tut.hpp>
#include "Canvas.h"

using namespace canvas;

namespace tut
{
   struct CanvasData
   {
      CanvasData()
         : canvas(new Canvas(100, 100, false))
      { }
      
      ~CanvasData()
      {
         delete canvas;
      }
      
      Canvas  * canvas;
   };
   
   test_group<CanvasData> canvasTest("Canvas");
   typedef test_group<CanvasData>::object object;
   
   template <>
   template <>
   void object::test<1>()
   {
      set_test_name("Canvas allocation");
   }
   
   template <>
   template <>
   void object::test<2>()
   {
      set_test_name("Javascript Test 1");
      
      canvas->loadCode("(function() { })();");
   }
   
   template <>
   template <>
   void object::test<3>()
   {
      set_test_name("Javascript Test 2: window.log()");
      
      //canvas->loadCode("");
   }
}