#pragma once

bool LoadMap(Map Map[][4], const char* filename);
bool LoadCave(Map Map[], const char* filename);
bool SwitchMap(Entity& Player, int& MapX, int& MapY);
void DisplayMap(Map& Map, MapTexture& Textures, SDL_Renderer** Renderer);
bool obstacleCheck(Map& Map, Entity& Hero);
bool LoadMap2(Map Map, const char* filename);

void EnemyDisplay(Map& Map, Entity Enemies[]);