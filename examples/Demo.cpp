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

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <fstream>
#include <Canvas.h>

using namespace canvas;

/// Simple function that tries to locate the Demo.js file
std::string locateDemoJavaScript()
{
   std::string  paths[3] = {
      "examples/Demo.js",
      "../examples/Demo.js",
      "../../examples/Demo.js"
   };
   
   for (int i = 0; i < 3; ++i)
   {
      std::ifstream file(paths[i].c_str());
      if (file.is_open())
         return paths[i];
   }
   
   return "";
}

int main(int argc, char * argv[])
{
   bool running = true;
   
   if (argc < 2)
   {
      std::cout << "Usage: demo (-i <image-path>) <javascript>" << std::endl;
      return 0;
   }
   
   if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
   {
      std::cerr << "Could not initialize SDL" << std::endl;
      return 1;
   }

   // Create the window
   SDL_Surface * screen = SDL_SetVideoMode(800, 500, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
   SDL_WM_SetCaption("Canvas++ Demo", 0);
   
   // Create the canvas
   Canvas * canvas = new Canvas(800, 500, Canvas::kRGBA, true);
   
   // Parse arguments
   for (int i = 1; i < argc; ++i)
   {
      std::string arg(argv[i]);
      if (arg == "-i" && (i + 1) < argc)
      {
         SDL_Surface * image = IMG_Load(argv[i + 1]);
         if (!image)
         {
            std::cerr << "Could not load image: " << argv[i + 1] << std::endl;
         }
         else
         {
            if (image->format->BitsPerPixel == 32)
            {
               std::cerr << "Loaded image (" << image->w << "x" << image->h << "): " << argv[i + 1] << std::endl;
               canvas->registerImage(argv[i + 1], image->w, image->h, Canvas::kRGBA, image->pixels);
            }
            else
            {
               std::cerr << "Image '" << argv[i + 1] << "' has the wrong format (" << (int)image->format->BitsPerPixel << ")" << std::endl;
            }
            
            SDL_FreeSurface(image);
         }
         
         i++;
      }
   }
   
   // Last argument must be the script file
   canvas->startWithFile(argv[argc - 1]);
   
   // Create a sdl surface that will act like a target for the canvas
   SDL_Surface * target = SDL_CreateRGBSurface(SDL_SWSURFACE, 800, 500, 32, 0x00FF0000, 
                                                                            0x0000FF00,
                                                                            0x000000FF,
                                                                            0xFF000000);

   // Enter the application loop
   while (running)
   {
      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
         switch (event.type)
         {
            case SDL_QUIT:
               running = false;
               break;
            case SDL_KEYDOWN:
               switch (event.key.keysym.sym)
               {
                  case SDLK_ESCAPE:
                     running = false;
                     break;
               }
               break;
         }
      }
      
      if (canvas->isDirty())
      {
         SDL_LockSurface(target);
         canvas->paint(target->pixels);
         SDL_UnlockSurface(target);
      }
      
      SDL_BlitSurface(target, 0, screen, 0);
      
      // Print log
      for (std::string log = canvas->lastLogEntry(); log != ""; log = canvas->lastLogEntry())
      //while ((std::string log = canvas->lastLogEntry()) != "")
         std::cout << log << std::endl;
      
      SDL_Flip(screen);
      SDL_Delay(10);
   }
   
   delete canvas;

   SDL_FreeSurface(screen);
   SDL_Quit();
   
   return 0;
}