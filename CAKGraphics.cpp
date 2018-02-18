#include <pthread.h>
#include "prodcom.h"
#include <CkJsonObject.h>
#include "CAKGraphics.h"


typedef Uint32 (*SDL_NewTimerCallback)(Uint32 interval, void* param);

bool CAKGraphics::ParseRfidData(char* rfidcontent, RFIDData* rfiddata)
{
	CkJsonObject json;

 
    bool success = json.Load(rfidcontent);
    if (success != true) {
            return false;
    }
    rfiddata->rfidcode = json.IntOf("rfid");
    rfiddata->rfidstatus = json.IntOf("rfidStatus");
    rfiddata->rfidpersonid = json.IntOf("personference");
    strcpy(rfiddata->rfidpersonstr,json.stringOf("personTitle"));
    rfiddata->rfidbirthday = json.BoolOf("birthday");
    
    return true;    


}

SDL_TimerID CAKGraphics::idTapTimer = (SDL_TimerID)0;


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
  endAudio();
  graphics_destroytext();
  graphics_destroybackground();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
} 


bool CAKGraphics::graphics_drawtext(TTF_Font* font, const char* message, SDL_Color color)
{
	int w, h;
	TTF_SizeText(font, message, &w, &h);

	SDL_Surface* textsurface = TTF_RenderUTF8_Blended(font, message, color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* textmessage = SDL_CreateTextureFromSurface(renderer, textsurface); //now you can convert it into a texture
	
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = (SCREEN_WIDTH/2)-(w/2);  //controls the rect's x coordinate 
	Message_rect.y = (SCREEN_HEIGHT/2)-(h/2); // controls the rect's y coordinte
	Message_rect.w = w; // controls the width of the rect
	Message_rect.h = h; // controls the height of the rect

	SDL_RenderCopy(renderer, textmessage, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
	return true;
}

bool CAKGraphics::graphics_text(const char* message, SDL_Color color)
{

   	textfont = TTF_OpenFont("./fonts/DejaVuSans.ttf", 42); //this opens a font style and sets a size
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
  
  if (TTF_Init() < 0  || SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER) < 0 ) {
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
  
  initAudio();

  return true;
  
  }
  
  void CAKGraphics::graphics_updatewindow()
  {
	  	SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(window);
  }
  
    void CAKGraphics::graphics_update()
  {
	  	SDL_RenderPresent(renderer);

  }
  


Uint32 CAKGraphics::TapInTimerCallback(Uint32 interval, void* param)
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

  
 bool CAKGraphics::graphics_run(void* context)
{  
   cp_t* temp = (cp_t*)context;
   volatile bool quit = false;
   SDL_Event event;
   
   playSound("./sound/door2.wav", SDL_MIX_MAXVOLUME / 2);
   
   while (!quit)
   {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
        
        case SDL_QUIT:
            temp->quitflag = true;
            quit = true;
            return false;
            
        case SDL_WINDOWEVENT:
			switch(event.window.event){

						case SDL_WINDOWEVENT_SHOWN:
						case SDL_WINDOWEVENT_EXPOSED:
						case SDL_WINDOWEVENT_MOVED:
						case SDL_WINDOWEVENT_RESIZED:
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							 SDL_RenderPresent(renderer);
							 break;
						default:
							break;
			}
			break;
		case SDL_KEYUP:
			if( (char)(event.key.keysym.sym) == SDLK_z){
				//akgraphics->graphics_drawbackground();
				SDL_SetRenderDrawColor(renderer, 255, 255,255, 255);
				SDL_RenderClear(renderer);
				graphics_text("Signed in", {0,0,0} );
				SDL_RenderPresent(renderer);
				playSound("./sound/good.wav", SDL_MIX_MAXVOLUME/2);
				if( idTapTimer != (SDL_TimerID)0 )
						SDL_RemoveTimer(idTapTimer);
				SDL_AddTimer(2000,CAKGraphics::TapInTimerCallback,NULL);  
			} 
			if( (char)(event.key.keysym.sym) == SDLK_x){
				//akgraphics->graphics_drawbackground();
				SDL_SetRenderDrawColor(renderer, 255, 255,255, 255);
				SDL_RenderClear(renderer);
				graphics_text("Unknown", {0,0,0} );
				SDL_RenderPresent(renderer);
				playSound("./sound/fail.wav", SDL_MIX_MAXVOLUME/2);
				if( idTapTimer != (SDL_TimerID)0 )
						SDL_RemoveTimer(idTapTimer);
				SDL_AddTimer(2000,CAKGraphics::TapInTimerCallback,NULL);  
			} 
			break;
			
		case SDL_USEREVENT: {
			   if( event.user.code == EVENT_TAP_FROM_WEBRESPONSE )
			   {
						RFIDData rfiddata;
						char rfidsound[256];
				   		if( (int)event.user.data2 > 0 )
						{
							    ParseRfidData((char*)event.user.data1, &rfiddata);
								free( event.user.data1 );
						}
						
						SDL_SetRenderDrawColor(renderer, 255, 255,255, 255);
						SDL_RenderClear(renderer);
						if( rfiddata.rfidstatus == 0 )
						{
							graphics_text( rfiddata.rfidpersonstr, {255,0,0} );
							strcpy(rfidsound , "./sound/good.wav");
						}
						if( rfiddata.rfidstatus == -1 )
						{
							graphics_text( "Unknown", {0,0,255} );
							strcpy(rfidsound , "./sound/fail.wav");						
						}	
						SDL_RenderPresent(renderer);
						playSound(rfidsound, SDL_MIX_MAXVOLUME/2);
						if( idTapTimer != (SDL_TimerID)0 )
							SDL_RemoveTimer(idTapTimer);
						SDL_AddTimer(2000,CAKGraphics::TapInTimerCallback,NULL);  

							 
			   }
			
               if( event.user.code == EVENT_TAP_IN_RESET )
               {
				    SDL_RemoveTimer( idTapTimer );
				    idTapTimer = (SDL_TimerID)0; 
				   	graphics_drawbackground();

					graphics_text("Tap to Sign In", {0,0,0x3F} );
					SDL_RenderPresent(renderer);
					
		       }
               break;
               }         
         }
  
        
    }
    return false;
}

