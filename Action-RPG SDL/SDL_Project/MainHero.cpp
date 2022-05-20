#include "MainHero.h"

void HeroShoot(Entity& Hero, Entity& Arrow, SDL_Texture* ArrowTexture[])
{
	Arrow.x = Hero.x;
	Arrow.y = Hero.y;
	Arrow.Damage = 1;
	switch (Hero.pos) {
	case 0: {
		Arrow.dy = Hero.dy;
		Arrow.pos = 0;
	}; break;
	case 1: {
		Arrow.dx = -Hero.dx;
		Arrow.pos = 1;
	}; break;
	case 2: {
		Arrow.dy = -Hero.dy;
		Arrow.pos = 2;
	}; break;
	case 3: {
		Arrow.dx = Hero.dx;
		Arrow.pos = 3;
	}; break;
	default: break;
	}
}

bool ArrowMove(Entity& Arrow, Entity Enemies[])
{
	Arrow.x += Arrow.dx;
	Arrow.y += Arrow.dy;

	if (Arrow.x < 0 || Arrow.x > 1280 || Arrow.y < 0 || Arrow.y > 768) {
		Arrow.x = -64;
		Arrow.y = -64;
		Arrow.dx = 0;
		Arrow.dy = 0;
		return false;
	}

	for (int i = 0; i < 4; i++) {
		if (Arrow.x > Enemies[i].x - 32 && Arrow.x < Enemies[i].x + Enemies[i].w && Arrow.y > Enemies[i].y - 32 && Arrow.y < Enemies[i].y + 32) {
			Enemies[i].Lives -= Arrow.Damage;
			Arrow.x = -64;
			Arrow.y = -64;
			Arrow.dx = 0;
			Arrow.dy = 0;
			return false;
		}
	}

	return true;
}

bool BombSet(Entity& Hero, Entity& Bomb, Map& Map)
{
		switch (Hero.pos) {
		case 0: {
			Bomb.x = Hero.x;
			Bomb.y = Hero.y + 64;
		}; break;
		case 1: {
			Bomb.x = Hero.x - 64;
			Bomb.y = Hero.y;
		}; break;
		case 2: {
			Bomb.x = Hero.x;
			Bomb.y = Hero.y - 64;
		}; break;
		case 3: {
			Bomb.x = Hero.x + 64;
			Bomb.y = Hero.y;
		}; break;
		default: break;
		}
	if (obstacleCheck(Map, Bomb)) return true;
	else {
		Bomb.x = Bomb.y = -64;
		return false;
	}
}

void BombDetonate(SDL_Rect& Bomb, Map* Map, Entity Enemies[], int damage)
{
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 20; j++) {
			if (Map->rockRects[i][j].x <= Bomb.x + Bomb.w + 16 && Map->rockRects[i][j].x >= Bomb.x - Map->rockRects[i][j].w - 16 && Map->rockRects[i][j].y >= Bomb.y - Map->rockRects[i][j].h - 16 && Map->rockRects[i][j].y <= Bomb.y + Bomb.h + 16) {
				Map->map[i][j] = 0;
				Map->collisionRects[i][j].x = Map->collisionRects[i][j].y = 0;
				Map->rockRects[i][j].w = Map->rockRects[i][j].h = 0;
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		if (Enemies[i].x <= Bomb.x + 64 + 16 && Enemies[i].x >= Bomb.x - 64 - 16 && Enemies[i].y >= Bomb.y - 64 - 16 && Enemies[i].y <= Bomb.y + Bomb.h + 16) {
			Enemies[i].Lives -= damage;
		}
	}
}
