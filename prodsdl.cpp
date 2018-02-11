#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "audio.h"


#include "CAKGraphics.h"




int main(int argc, char* args[]) 

{

	
  CAKGraphics akgraphics;
  bool quit = false;
  SDL_Event event;


 if( akgraphics.graphics_init() == true )
  {
	  
	initAudio();
	akgraphics.graphics_background("/home/pi/Projects/sdl/sdlplay/image.bmp"); 
	akgraphics.graphics_text("TAP F3822 TO SIGN IN", {128,228,45} );


  SDL_RenderPresent(akgraphics.renderer);
  
  SDL_UpdateWindowSurface(akgraphics.window);
  playSound("/home/pi/Projects/sdl/sdlplay/good.wav", SDL_MIX_MAXVOLUME / 2);
  
  akgraphics.graphics_drawbackground();
  akgraphics.graphics_text("Tap in here", {45,228,123} );
    
  SDL_RenderPresent(akgraphics.renderer);
  
   //playSound("/home/pi/Projects/sdl/sdlplay/door2.wav", SDL_MIX_MAXVOLUME / 2);
 // SDL_UpdateWindowSurface(akgraphics.window);
   
    
      while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
  
        }
    }
  

   endAudio();
   akgraphics.graphics_destroy();
  
  
  }
  return 0;
}
