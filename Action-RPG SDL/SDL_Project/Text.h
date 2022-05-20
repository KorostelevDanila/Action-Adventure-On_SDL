#pragma once
#include "Libraries.h"

void ttf_init();
void initFonts(TTF_Font* font);
SDL_Texture* getTextTexture(SDL_Renderer** Renderer, char text[], TTF_Font* font);
SDL_Texture* toTexture(SDL_Renderer** Renderer, SDL_Surface* surface, int destroySurface);
void textDraw(SDL_Renderer** Renderer, SDL_Rect& textRect, SDL_Texture* textTexture);