#include "Libraries.h"
//#include "TextureRender.h"


void textureInitialize()
{
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		cout << "The problem occured during SDL-image initialization. SDL Error: " << SDL_GetError();
		exit(1);
	}
}

SDL_Texture* TextureLoad(const char* filePath, SDL_Renderer** Renderer)
{
	SDL_Texture* texture = NULL;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filePath);

	texture = IMG_LoadTexture(*Renderer, filePath);
	if (texture == NULL) {
		cout << "The problem occured during loading texture. SDL Error: " << SDL_GetError();
		exit(1);
	}

	return texture;
}

void TextureCopy(SDL_Renderer** Renderer, int x, int y, SDL_Texture** Texture)
{
	SDL_Rect SizeOfTheTexture;
	SizeOfTheTexture.x = 0;
	SizeOfTheTexture.y = 0;
	SizeOfTheTexture.w = 64;
	SizeOfTheTexture.h = 64;

	SDL_Rect Dest;
	Dest.x = x;
	Dest.y = y;
	Dest.w = 64;
	Dest.h = 64;

	SDL_RenderCopy(*Renderer, *Texture, &SizeOfTheTexture, &Dest);
}

void TextureDisplay(SDL_Renderer** Renderer)
{
	SDL_RenderPresent(*Renderer);
}
