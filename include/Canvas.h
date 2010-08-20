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
         enum Format
         {
            kARGB,   //!< Default format, 32-bits per pixel in (alpha, red, blue, green) configuration.
            kRGBA    //!< If this format is used, an internal byte swap will be performed on every paint() call.
         };
         
         Canvas(int width, int height, Format format = kARGB, bool threaded = true);
         ~Canvas();
         
         /// Loads a script from file and executes it.
         void startWithFile(std::string const& filename);
         
         /// Loads and executes the supplied javascript code.
         void startWithCode(std::string const& code);
         
         /// Register image data with the canvas, it can later be accessed from javascript.
         void registerImage(std::string const& name, int width, int height, Format format, void * data);
         
         /// Returns true if the canvas should be rendered.
         bool isDirty() const;
         
         /// Paint the canvas to the supplied image data.
         /// Note that the image format is 32-bits per pixel
         /// organized in ARGB.
         void paint(void * imageData);
         
         /// Pops and returns the last javascript log entry.
         /// Returns the empty string if no log entires exists.
         std::string lastLogEntry();
         
      private:
         std::auto_ptr<CanvasData> m_data;
   };
}

#endif

