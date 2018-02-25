#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "audio.h"


#define SCREEN_WIDTH 480 
//1280
#define SCREEN_HEIGHT 320

#define EVENT_TAP_IN_RESET 0
#define EVENT_TAP_FROM_WEBRESPONSE 1

typedef struct _tagRfidData
{
		int rfidcode;
		int rfidstatus;
		int rfidpersonid;
		char rfidpersonstr[256];
		bool rfidbirthday;
}RFIDData;


class CAKConfig
{
public:
	  char fontpath[256];
	  int  fontsize;

	  char serviceurl[256];       //":"http://alansw550/aweb2427/home/rfid"
	  char servicelocation[256];  //"servicelocation":"frontdoor"
      char initsound[256];        //"initsound":"./sound/door2.wav"
      char initimage[256];		  //"initimage": .
      char rfidinsound[256];      //"rfidinsound":"./sound/good.wav"
      char rfidnosound[256];      //"rfidnosound":"./sound/fail.wav"
public:

	  CAKConfig(){
			initimage[0] = (char)'\0';
	  }
	  void ReadConfig(const char* configfile);
	
};


class CAKGraphics
{
public:

	SDL_Window* window;
	SDL_Renderer *renderer;


	SDL_Surface *backgroundsurface;
	SDL_Texture *background;

	SDL_Surface* textsurface;
	SDL_Texture* textmessage;

	TTF_Font* textfont;
	

public:
	CAKGraphics();
	~CAKGraphics();



	void graphics_destroytext();
	void graphics_destroybackground();
	void graphics_destroy();
	
	bool graphics_drawtext(TTF_Font* font, const char* message, SDL_Color color);
	bool graphics_text(const char* message, SDL_Color color);


	void graphics_initdisplay();
	
	bool graphics_drawbackground();
	bool graphics_clearbackground( ushort r, ushort g, ushort b ); 
	bool graphics_background(const char* imagefile);
	
    void graphics_updatewindow();
    void graphics_update();

	bool graphics_init();
	bool graphics_run(void* context);

	CAKConfig config;
	
private:
	static SDL_TimerID idTapTimer;
	static Uint32 TapInTimerCallback(Uint32 interval, void* param);
	static bool ParseRfidData(char* rfidcontent, RFIDData* rfiddata);
	
	
 

};



