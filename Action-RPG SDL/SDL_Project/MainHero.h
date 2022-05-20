#pragma once
#include "Libraries.h"

void HeroShoot(Entity& Hero, Entity& Arrow, SDL_Texture* ArrowTexture[]);
bool ArrowMove(Entity& Arrow, Entity Enemies[]);
bool BombSet(Entity& Hero, Entity& Bomb, Map& Map);
void BombDetonate(SDL_Rect& Bomb, Map* Map, Entity Enemies[], int damage);