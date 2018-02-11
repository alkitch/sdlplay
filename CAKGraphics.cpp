#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#include "CAKGraphics.h"



CAKGraphics::CAKGraphics()
{
}

CAKGraphics::~CAKGraphics(){}


void CAKGraphics::graphics_destroytext()
{
   SDL_DestroyTexture(textmessage);
   SDL_FreeSurface(textsurface);

}
 
void CAKGraphics::graphics_destroybackground()
{
   SDL_DestroyTexture(background);
   SDL_FreeSurface(backgroundsurface);
}

void CAKGraphics::graphics_destroy()
{  

  graphics_destroytext();
  graphics_destroybackground();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
} 


bool CAKGraphics::graphics_drawtext(TTF_Font* font, const char* message, SDL_Color color)
{
	//SDL_Color White = {255, 128, 0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	
	int w, h;
	TTF_SizeText(font, message, &w, &h);

	SDL_Surface* textsurface = TTF_RenderUTF8_Blended(font, message, color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* textmessage = SDL_CreateTextureFromSurface(renderer, textsurface); //now you can convert it into a texture
	
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = (SCREEN_WIDTH/2);  //controls the rect's x coordinate 
	Message_rect.y = (SCREEN_HEIGHT/2); // controls the rect's y coordinte
	Message_rect.w = w; // controls the width of the rect
	Message_rect.h = h; // controls the height of the rect

	SDL_RenderCopy(renderer, textmessage, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
	return true;
}

bool CAKGraphics::graphics_text(const char* message, SDL_Color color)
{

   	textfont = TTF_OpenFont("DejaVuSans.ttf", 52); //this opens a font style and sets a size
	if(textfont == NULL)
		return false;

	return graphics_drawtext(textfont, message, color);

}

bool CAKGraphics::graphics_drawbackground()
{
  SDL_Rect dstrect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_RenderCopy(renderer, background, NULL, &dstrect);
}

bool CAKGraphics::graphics_background(const char* imagefile)
{
  backgroundsurface = SDL_LoadBMP(imagefile); 
  background = SDL_CreateTextureFromSurface(renderer, backgroundsurface);
  graphics_drawbackground();
}



bool CAKGraphics::graphics_init()
{
 
  if (TTF_Init() < 0  || SDL_Init(SDL_INIT_VIDEO) < 0 || SDL_Init(SDL_INIT_AUDIO) < 0) {
		return false;
  }

  window = SDL_CreateWindow(
			    "2427 (Biggin Hill) Sqn CIS",
			    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			    SCREEN_WIDTH, SCREEN_HEIGHT,
			    SDL_WINDOW_BORDERLESS
			    );
  if(window == NULL) return false;

  renderer = SDL_CreateRenderer(window, -1, 0);

	return true;
  
  }
