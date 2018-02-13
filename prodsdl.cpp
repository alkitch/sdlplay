#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "CAKGraphics.h"


int main(int argc, char* args[]) 
{

	 CAKGraphics akgraphics;

	 if( akgraphics.graphics_init() == true )
	 {
		
		akgraphics.graphics_background("/home/pi/Projects/sdl/sdlplay/typhoon.bmp"); 
		akgraphics.graphics_text("Tap to Sign In", {0,0,0x3F} );

		akgraphics.graphics_updatewindow();
				
		akgraphics.graphics_run();
				
		akgraphics.graphics_destroy();
	  }
	  return 0;
}
