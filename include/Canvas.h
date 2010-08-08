
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
         
         /// Returns true if the canvas should be rendered.
         bool isDirty() const;
         
         /// Render the canvas to the supplied image data.
         void render(unsigned char * imageData);
         
      private:
         std::auto_ptr<CanvasData> m_data;
   };
}

#endif