// SDL2 Hello, World!
// This should display a white screen for 2 seconds
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 768

int main(int argc, char* args[]) 

{



  bool quit = false;
  SDL_Event event;


if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
}

  SDL_Window* window = NULL;
  //SDL_Surface* screenSurface = NULL;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }

  

  window = SDL_CreateWindow(
			    "2427 (Biggin Hill) Sqn CIS",
			    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			    SCREEN_WIDTH, SCREEN_HEIGHT,
			    SDL_WINDOW_SHOWN
			    );
  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }
  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Surface * image = SDL_LoadBMP("/home/pi/Projects/sdl/sdlplay/image.bmp"); 
  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
  SDL_Rect dstrect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);

   TTF_Font* Sans = TTF_OpenFont("DejaVuSans.ttf", 52); //this opens a font style and sets a size

if(Sans == NULL)
printf("Failed to find Font\n");

	SDL_Color White = {255, 128, 0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	int w;
	int h;
	TTF_SizeText(Sans, "TAP F3822 TO SIGN IN", &w, &h);

	SDL_Surface* surfaceMessage = TTF_RenderUTF8_Blended(Sans, "TAP F3822 TO SIGN IN", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = (SCREEN_WIDTH/2);  //controls the rect's x coordinate 
	Message_rect.y = (SCREEN_HEIGHT/2); // controls the rect's y coordinte
	Message_rect.w = w; // controls the width of the rect
	Message_rect.h = h; // controls the height of the rect
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

  SDL_RenderPresent(renderer);


  //screenSurface = SDL_GetWindowSurface(window);
  //SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xBA, 0xFA, 0xFF));
  

  SDL_UpdateWindowSurface(window);
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
   SDL_DestroyTexture(Message);
   SDL_FreeSurface(surfaceMessage);
  
   SDL_DestroyTexture(texture);
   SDL_FreeSurface(image);
  
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  
  SDL_Quit();
  return 0;
}
