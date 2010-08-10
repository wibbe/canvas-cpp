
#ifndef CANVAS_HEADER
#define CANVAS_HEADER

#include <string>
#include <memory>

namespace canvas
{
   // Forward declaration
   class CanvasData;
   
   class Canvas
   {
      private:
         Canvas(Canvas const& other);
         Canvas & operator = (Canvas const& other);
         
      public:
         Canvas(int width, int height, bool threaded = true);
         ~Canvas();
         
         /// Loads a script from file and executes it.
         void loadScript(std::string const& filename);
         
         /// Loads and executes javascript code.
         void loadCode(std::string const& code);
         
         /// Returns true if the canvas should be rendered.
         bool isDirty() const;
         
         /// Paint the canvas to the supplied image data.
         void paint(unsigned char * imageData);
         
         /// Pops and returns the last javascript log entry.
         /// Returns the empty string if no log entires exists.
         std::string lastLogEntry();
         
      private:
         std::auto_ptr<CanvasData> m_data;
   };
}

#endif