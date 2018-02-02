#include <iostream>
#include <cmath>

#include <SDL2/SDL.h>


//Just a play thing 
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

// SDL stuff
void init_sdl();
void close_sdl();

SDL_Renderer* renderer = nullptr;
SDL_Window* displayWindow = nullptr;

// plazma stuff
constexpr int PLAZMA_SIZE = 256;
int plasma[PLAZMA_SIZE][PLAZMA_SIZE];
unsigned long buffer[PLAZMA_SIZE][PLAZMA_SIZE];
unsigned long palette[256];
int paletteShift = 0;

SDL_Surface* plazma_surface = nullptr;
SDL_Texture* plazma_texture = nullptr;

void init_plazma();
void update_plazma();
void render_plazma();

int main(int argc, char *argv[]) {

	init_sdl();
	init_plazma();

	bool running = true;

	SDL_Event event;

	while (running) {

		SDL_PollEvent(&event);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		update_plazma();
		render_plazma();

		SDL_RenderPresent(renderer);

		// sleep
		SDL_Delay(5);

		if (event.type == SDL_QUIT) {
			running = false;
		}

	}

	close_sdl();

	return 0;
}

void init_sdl() {

	if (SDL_Init( SDL_INIT_VIDEO) < 0) {
		std::cerr << "There was an error initializing SDL2: " << SDL_GetError() << std::endl;
		std::abort();
	}

	displayWindow = SDL_CreateWindow("Basic SDL2 2D application", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	if (displayWindow == nullptr) {
		std::cerr << "There was an error creating the window: " << SDL_GetError() << std::endl;
		std::abort();
	}

	renderer = SDL_CreateRenderer(displayWindow, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cerr << "There was an error creating the renderer: " << SDL_GetError() << std::endl;
		std::abort();
	}

}

void close_sdl() {

	if (plazma_surface != nullptr) {
		SDL_FreeSurface(plazma_surface);
	}

	if (plazma_texture != nullptr) {
		SDL_DestroyTexture(plazma_texture);
	}

	// Clean up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(displayWindow);
	SDL_Quit();

}

unsigned long color_to_int(int r, int g, int b, int a) {
	return ((a & 0xFF) << 24) | ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | ((b & 0xFF) << 0);
}

void init_plazma() {

	const int o = rand() % 255;

	const int _r = rand() % 255;
	const int _g = rand() % 255;
	const int _b = rand() % 255;

	unsigned char colorRGB[3];

	for (int x = 0; x < 256; x++) {

		colorRGB[0] = int(o + _r * sin(3.1415 * x / 128));
		colorRGB[1] = int(o + _g * sin(3.1415 * x / 32));
		colorRGB[2] = int(o + _b * sin(3.1415 * x / 32));

		palette[x] = color_to_int(colorRGB[0], colorRGB[1], colorRGB[2], SDL_ALPHA_OPAQUE);
	}

	//generate the plasma once
	for (int x = 0; x < PLAZMA_SIZE; x++) {
		for (int y = 0; y < PLAZMA_SIZE; y++) {

			const int color = int(128.0 + (128.0 * sin(x / 16.0)) + 128.0 + (128.0 * sin(y / 8.0)) + 128.0 + (128.0 * sin((x + y) / 16.0)) + 128.0 + (128.0 * sin(sqrt(double(x * x + y * y)) / 8.0))) / 4;

			plasma[x][y] = color;
		}
	}

	plazma_surface = SDL_CreateRGBSurface(0, PLAZMA_SIZE, PLAZMA_SIZE, 32, 0, 1, 0, 0);

}

inline
bool lock(SDL_Surface* surf) {

	if (SDL_MUSTLOCK(surf)) {
		if (SDL_LockSurface(surf) < 0) {
			std::cerr << "Can't lock plazma surface: " << SDL_GetError() << std::endl;
			std::abort();
		}
		return true;
	} else {
		return false;
	}

}

inline
void unlock(SDL_Surface* surf) {

	if (SDL_MUSTLOCK(surf)) {
		SDL_UnlockSurface(surf);
	}
}

void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {

	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
		case 1:
			*p = pixel;
			break;
		case 2:
			*(Uint16 *) p = pixel;
			break;
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;
		case 4:
			*(Uint32 *) p = pixel;
			break;
	}
}

SDL_Texture* to_texture(SDL_Renderer* ren, SDL_Surface* surface) {
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
	return texture;
}

void update_from_surface(SDL_Texture* texture, SDL_Surface* surf) {
	SDL_UpdateTexture(texture, nullptr, surf->pixels, surf->pitch);
}

void update_plazma() {

	//the parameter to shift the palette varies with time
	paletteShift = int(SDL_GetTicks() / 100.0);

	//draw every pixel again,	 with the shifted palette color
	for (int x = 0; x < PLAZMA_SIZE; x++) {
		for (int y = 0; y < PLAZMA_SIZE; y++) {
			buffer[x][y] = palette[(plasma[x][y] + paletteShift) % 256];
		}
	}

	lock(plazma_surface);

	for (int x = 0; x < PLAZMA_SIZE; x++) {
		for (int y = 0; y < PLAZMA_SIZE; y++) {
			put_pixel(plazma_surface, x, y, buffer[x][y]);
		}
	}

	unlock(plazma_surface);

	if (plazma_texture == nullptr) {
		plazma_texture = to_texture(renderer, plazma_surface);
	} else {
		update_from_surface(plazma_texture, plazma_surface);
	}

}

void render_plazma() {
	SDL_RenderCopy(renderer, plazma_texture, nullptr, nullptr);
}
