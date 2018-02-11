
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 768

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

	bool graphics_drawbackground();
	bool graphics_background(const char* imagefile);

	bool graphics_init();

};



