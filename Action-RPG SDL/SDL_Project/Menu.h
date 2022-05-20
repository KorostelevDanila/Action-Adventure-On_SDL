#pragma once
#include "Libraries.h"

int MainMenu(SDL_Renderer** Renderer, int& MusicIsOn, int& SoundIsOn);
void OptionsMenu(SDL_Renderer** Renderer, int& MusicIsOn, int& SoundIsOn, Mix_Chunk* click, Mix_Music* MainMenuOST);
void GameOver(SDL_Renderer** Renderer);
void Victory(SDL_Renderer** Renderer);
void LoadNewGame(Entity* Player, int& MapX, int& MapY);
bool LoadGame(Entity* Player, int& MapX, int& MapY, const char* savepath);
bool PauseMenu(SDL_Renderer** Renderer, int& MusicIsOn, int& SoundIsOn, Entity* Player, int& MapX, int& MapY);
void SaveGame(Entity* Player, int MapX, int MapY);