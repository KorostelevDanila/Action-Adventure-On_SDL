#include "Text.h"

void ttf_init()
{
	if (TTF_Init() < 0) {
		printf_s("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
		exit(1);
	}
}

void initFonts(TTF_Font* font)
{
	font = TTF_OpenFont("Game Files//pixelcyr_normal.ttf", 100);
}

SDL_Texture* getTextTexture(SDL_Renderer** Renderer, char text[], TTF_Font* font)
{
	SDL_Surface* surface;
	SDL_Color color = { 0, 0, 0 };
	if (!(surface = TTF_RenderUTF8_Blended(font, text, color))) {
		printf_s("sosi huy\n");
	}

	return toTexture(Renderer, surface, 1);
}

SDL_Texture* toTexture(SDL_Renderer** Renderer, SDL_Surface* surface, int destroySurface)
{
	SDL_Texture* texture;

	texture = SDL_CreateTextureFromSurface(*Renderer, surface);

	if (destroySurface == 1) {
		SDL_FreeSurface(surface);
	}

	return texture;
}

void textDraw(SDL_Renderer** Renderer, SDL_Rect& textRect, SDL_Texture* textTexture)
{
	SDL_RenderCopy(*Renderer, textTexture, NULL, &textRect);
}
