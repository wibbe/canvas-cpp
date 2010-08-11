
#include <tut/tut.hpp>
#include "../src/ColorParser.h"

using namespace canvas;

namespace tut
{
   struct ColorParserData
   {
      ColorParser parser;
   };
   
   test_group<ColorParserData> tf("ColorParser");
   typedef test_group<ColorParserData>::object object;
   
   template <>
   template <>
   void object::test<1>()
   {
      set_test_name("Check Hex string -> Int");
      
      ensure(parser.hexStringToInt("0") == 0);
      ensure(parser.hexStringToInt("1") == 1);
      ensure(parser.hexStringToInt("2") == 2);
      ensure(parser.hexStringToInt("3") == 3);
      ensure(parser.hexStringToInt("4") == 4);
      ensure(parser.hexStringToInt("5") == 5);
      ensure(parser.hexStringToInt("6") == 6);
      ensure(parser.hexStringToInt("7") == 7);
      ensure(parser.hexStringToInt("8") == 8);
      ensure(parser.hexStringToInt("9") == 9);
      ensure(parser.hexStringToInt("a") == 10);
      ensure(parser.hexStringToInt("b") == 11);
      ensure(parser.hexStringToInt("c") == 12);
      ensure(parser.hexStringToInt("d") == 13);
      ensure(parser.hexStringToInt("e") == 14);
      ensure(parser.hexStringToInt("f") == 15);
      ensure(parser.hexStringToInt("A") == 10);
      ensure(parser.hexStringToInt("B") == 11);
      ensure(parser.hexStringToInt("C") == 12);
      ensure(parser.hexStringToInt("D") == 13);
      ensure(parser.hexStringToInt("E") == 14);
      ensure(parser.hexStringToInt("F") == 15);
   }
   
   template<>
   template<>
   void object::test<2>()
   {
      set_test_name("Check Color equal operator");
      ensure(Color(1.0f, 1.0f, 0.0f, 0.4f) == Color(1.0f, 1.0f, 0.0f, 0.4f));
   }
   
   template <>
   template <>
   void object::test<3>()
   {
      set_test_name("Check built-in colors");
      ensure(parser.parse("red") == Color(255, 0, 0));
      ensure(parser.parse("blue") == Color(0, 0, 255));
      ensure(parser.parse("green") == Color(0, 255, 0));
      ensure(parser.parse("yellow") == Color(255,255,0));
   }
}

