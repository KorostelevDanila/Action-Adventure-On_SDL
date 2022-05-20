#pragma once
#include "Libraries.h"

struct Entity {
	int x;
	int y;
	int w = 64;
	int h = 64;
	int dx = 0;
	int dy = 0;
	int pos; //0 - down, 1 - left, 2 - right, 3 - left

	bool fireAbility = false;
	bool isInDungeon = false;
	bool isInLegacyDungeon = false;
	bool fightAbility = false;
	bool pickedBombs = false;
	bool isDead = false;
	int getDamage = 1;

	int Lives = 0;
	int Damage;
	int Arrows = 0;
	int Coins = 0;
	int Bombs = 0;
	int Reload;

	SDL_Texture* texture;
};

struct MapTexture {
	SDL_Texture* Floor;
	SDL_Texture* Wall;
	SDL_Texture* Rock;
	SDL_Texture* CaveEntrance;
	SDL_Texture* Button;
	SDL_Texture* Void;
};

struct Map {
	int map[12][20] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	SDL_Rect CaveRect;
	SDL_Rect LegacyDungeonRect;
	SDL_Rect collisionRects[12][20];
	SDL_Rect rockRects[12][20] = { 0, 0, 0, 0 };
	SDL_Rect buttonRect;

	//SDL_Rect src, dest;
};


