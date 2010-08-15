
#include <SDL.h>
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
   
   if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
   {
      std::cerr << "Could not initialize SDL" << std::endl;
      return 1;
   }

   // Create the window
   SDL_Surface * screen = SDL_SetVideoMode(800, 500, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
   SDL_WM_SetCaption("Canvas++ Demo", 0);
   
   // Create the canvas
   Canvas * canvas = new Canvas(800, 500, true);
   canvas->loadFile(locateDemoJavaScript());
   
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