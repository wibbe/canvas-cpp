
#include "ColorParser.h"

#include <iostream>
#include <boost/xpressive/xpressive_static.hpp>
#include <boost/lexical_cast.hpp>

namespace canvas
{

   ColorParser::ColorParser()
   {
      // Insert some standard colors
      m_cached.insert(std::make_pair("black", Color(0, 0, 0)));
      m_cached.insert(std::make_pair("white", Color(255, 255, 255)));
      m_cached.insert(std::make_pair("red", Color(255, 0, 0)));
      m_cached.insert(std::make_pair("lime", Color(0, 255, 0)));
      m_cached.insert(std::make_pair("blue", Color(0, 0, 255)));
      m_cached.insert(std::make_pair("green", Color(0, 255, 0)));
      m_cached.insert(std::make_pair("grey", Color(128, 128, 128)));
      m_cached.insert(std::make_pair("lightgrey", Color(211, 211, 211)));
      m_cached.insert(std::make_pair("lightblue", Color(173,216,230)));
      m_cached.insert(std::make_pair("lightgreen", Color(144,238,144)));
      m_cached.insert(std::make_pair("orange", Color(255,165,0)));
      m_cached.insert(std::make_pair("orangered", Color(255,69,0)));
      m_cached.insert(std::make_pair("skyblue", Color(135,206,235)));
      m_cached.insert(std::make_pair("yellow", Color(255,255,0)));
      m_cached.insert(std::make_pair("pink", Color(255,192,203)));
      m_cached.insert(std::make_pair("indigo", Color(75,0,130)));
   }
         
   Color ColorParser::parse(std::string const& color)
   {
      Color resultColor;
      
      ColorMap::iterator search = m_cached.find(color);
      if (search != m_cached.end())
      {
         resultColor = search->second;
      }
      else
      {
         // Parse the color string
         using namespace boost::xpressive;
         
         // Matches: rgb(<int>, <int>, <int>)
         sregex rgbFunc = "rgb(" >> *space >> (s1= +_d) >> *space >> ',' >> *space >> (s2= +_d) >> *space >> ',' >> *space >> (s3= +_d) >> *space >> ')';
         
         // Matches: rgba(<int>, <int>, <int>, <float>)
         sregex rgbaFunc = "rgba(" >> *space >> (s1= +_d) >> *space >> ',' >> *space >>
                                                (s2= +_d) >> *space >> ',' >> *space >>
                                                (s3= +_d) >> *space >> ',' >> *space >>
                                                (s4= +_d >> '.' >> +_d) >> *space >> ')';
         
         sregex hex = (_d | (set= 'a','b','c','d','e','f', 'A', 'B', 'C', 'D', 'E', 'F'));
         // Matches #rgb
         sregex rgbHex = '#' >> (s1= hex) >> 
                                (s2= hex) >> 
                                (s3= hex);
         // Matches: #rrggbb
         sregex rrggbbHex = '#' >> (s1= hex >> hex) >> 
                                   (s2= hex >> hex) >>
                                   (s3= hex >> hex);
         
         smatch result;
         if (regex_match(color, result, rgbFunc))
         {
            resultColor = Color(boost::lexical_cast<int>(result.str(1)) / 255.0f,
                                boost::lexical_cast<int>(result.str(2)) / 255.0f,
                                boost::lexical_cast<int>(result.str(3)) / 255.0f,
                                1.0f);
            
            m_cached.insert(std::make_pair(color, resultColor));
         }
         else if (regex_match(color, result, rgbaFunc))
         {
            resultColor = Color(boost::lexical_cast<int>(result.str(1)) / 255.0f,
                                boost::lexical_cast<int>(result.str(2)) / 255.0f,
                                boost::lexical_cast<int>(result.str(3)) / 255.0f,
                                boost::lexical_cast<float>(result.str(4)));
            
            m_cached.insert(std::make_pair(color, resultColor));
         }
         else if (regex_match(color, result, rrggbbHex))
         {
            resultColor = Color(hexStringToInt(result.str(1)) / 255.0f,
                                hexStringToInt(result.str(2)) / 255.0f,
                                hexStringToInt(result.str(3)) / 255.0f,
                                1.0f);
            
            m_cached.insert(std::make_pair(color, resultColor));
         }
         else if (regex_match(color, result, rgbHex))
         {
            std::string r = result.str(1);
            std::string g = result.str(2);
            std::string b = result.str(3);
            
            r = r.size() == 1 ? r + r : r;
            g = g.size() == 1 ? g + g : g;
            b = b.size() == 1 ? b + b : b;
         
            resultColor = Color(hexStringToInt(r) / 255.0f,
                                hexStringToInt(g) / 255.0f,
                                hexStringToInt(b) / 255.0f,
                                1.0f);
            
            m_cached.insert(std::make_pair(color, resultColor));
         }
         else
            std::cerr << "Invalid color: " << color << std::endl;
      }
      
      return resultColor;
   }
   
   int ColorParser::hexStringToInt(std::string const& str)
   {
      int result = 0;
      
      std::string::const_iterator it = str.begin();
      std::string::const_iterator end = str.end();
      for (; it != end; ++it)
      {
         result = result << 4;
         char c = *it;
         
         if (c >= '0' && c <= '9')
            result += c - '0';
         else if (c >= 'a' && c <= 'f')
            result += 10 + (c - 'a');
         else if (c >= 'A' && c <= 'F')
            result += 10 + (c - 'A');
      }
      return result;
   }
         
}