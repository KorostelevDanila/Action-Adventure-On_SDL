#pragma once

void textureInitialize();
SDL_Texture* TextureLoad(const char* filePath, SDL_Renderer** Renderer);
void TextureCopy(SDL_Renderer** Renderer, int x, int y, SDL_Texture** Texture);
void TextureDisplay(SDL_Renderer** Renderer);

void clearUpTexture(SDL_Texture);