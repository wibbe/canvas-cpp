
#ifndef CANVAS_COLOR_PARSER_HEADER
#define CANVAS_COLOR_PARSER_HEADER

#include "Color.h"
#include <string>
#include <map>

namespace canvas
{

   class ColorParser
   {
         typedef std::map<std::string, Color>   ColorMap;
   
      public:
         ColorParser();
         
         Color parse(std::string const& color);
         
         int hexStringToInt(std::string const& str);
         
      private:
         ColorMap m_cached;
   };

}

#endif

