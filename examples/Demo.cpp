
#include <SDL.h>
#include <iostream>
#include <Canvas.h>

using namespace canvas;

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

   // Enter the application loop
   while (running)
   {
      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
         if (event.type == SDL_QUIT)
         {
            running = false;
         }
         else if (event.type == SDL_KEYDOWN)
         {
            switch (event.key.keysym.sym)
            {
               case SDLK_ESCAPE:
                  running = false;
                  break;
            }
         }
      }
      
      SDL_Flip(screen);
      SDL_Delay(10);
   }
   
   delete canvas;

   SDL_FreeSurface(screen);
   SDL_Quit();
   
   return 0;
}