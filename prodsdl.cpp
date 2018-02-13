#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "audio.h"
#include "CAKGraphics.h"

typedef Uint32 (*SDL_NewTimerCallback)(Uint32 interval, void* param);

#define EVENT_TAP_IN_RESET 0


SDL_TimerID idTapTimer = (SDL_TimerID)0;

Uint32 TapInTimerCallback(Uint32 interval, void* param)
{
	SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = EVENT_TAP_IN_RESET;
    userevent.data1 = NULL;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return 0;
}

bool Run(CAKGraphics* akgraphics)
{  
   bool quit = false;
   SDL_Event event;
   while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_WINDOWEVENT:
			switch(event.window.event){

						case SDL_WINDOWEVENT_SHOWN:
						case SDL_WINDOWEVENT_EXPOSED:
						case SDL_WINDOWEVENT_MOVED:
						case SDL_WINDOWEVENT_RESIZED:
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							 SDL_RenderPresent(akgraphics->renderer);
							 break;
						default:
							break;
			}
			break;
		case SDL_KEYUP:
			if( (char)(event.key.keysym.sym) == SDLK_z){
				akgraphics->graphics_drawbackground();
				akgraphics->graphics_text("Hello", {0,0,0x3F} );
				SDL_RenderPresent(akgraphics->renderer);
				playSound("/home/pi/Projects/sdl/sdlplay/good.wav", SDL_MIX_MAXVOLUME/2);
				if( idTapTimer != (SDL_TimerID)0 )
						SDL_RemoveTimer(idTapTimer);
				SDL_AddTimer(2000,TapInTimerCallback,NULL);  
			} 
			break;
			
		case SDL_USEREVENT: {
               if( event.user.code == EVENT_TAP_IN_RESET )
               {
				    SDL_RemoveTimer( idTapTimer );
				    idTapTimer = (SDL_TimerID)0; 
				   	akgraphics->graphics_drawbackground();
					akgraphics->graphics_text("Tap to Sign In", {0,0,0x3F} );
					SDL_RenderPresent(akgraphics->renderer);
					
		       }
               break;
               }         
         }
  
        
    }
    return true;
}


int main(int argc, char* args[]) 
{

	 CAKGraphics akgraphics;

	 if( akgraphics.graphics_init() == true )
	 {
		  
		initAudio();
		akgraphics.graphics_background("/home/pi/Projects/sdl/sdlplay/typhoon.bmp"); 
		akgraphics.graphics_text("Tap to Sign In", {0,0,0x3F} );

		SDL_RenderPresent(akgraphics.renderer);
		SDL_UpdateWindowSurface(akgraphics.window);
		
		playSound("/home/pi/Projects/sdl/sdlplay/door2.wav", SDL_MIX_MAXVOLUME / 2);
		
		Run(&akgraphics);
		
		endAudio();
		akgraphics.graphics_destroy();
	  }
	  return 0;
}
