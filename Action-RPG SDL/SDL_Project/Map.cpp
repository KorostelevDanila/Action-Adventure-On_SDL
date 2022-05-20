#include "Libraries.h"

bool LoadMap(Map Map[][4], const char* filename)
{
	ifstream file;
	file.open(filename);

	if (!file) {
		cout << "Problem occured during map loading." << endl;
		return false;
	}

	for (int iMap = 0; iMap < 3; iMap++) {
		for (int jMap = 0; jMap < 3; jMap++) {
			for (int i = 0; i < 12; i++) {
				for (int j = 0; j < 20; j++) {
					file >> Map[jMap][iMap].map[i][j];
				}
			}
		}
	}

	file.close();

	return true;
}

bool LoadMap2(Map Map, const char* filename)
{
	ifstream file;
	file.open(filename);

	if (!file) {
		cout << "Problem occured during map loading." << endl;
		return false;
	}

	for (int jMap = 0; jMap < 3; jMap++) {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 20; j++) {
				file >> Map.map[i][j];
			}
		}
	}

	file.close();

	return true;
}

bool LoadCave(Map Map[], const char* filename)
{
	ifstream file;
	file.open(filename);

	if (!file) {
		cout << "Problem occured during map loading" << endl;
		return false;
	}

	for (int iMap = 0; iMap < 3; iMap++) {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 20; j++) {
				file >> Map[iMap].map[i][j];
			}
		}
	}

	file.close();

	return true;
}

bool SwitchMap(Entity& Player, int& MapX, int& MapY)
{
	if (Player.y < 0) {
		MapX--;
		Player.y = 768 - 64 - 16;
		return true;
	}
	if (Player.y > 768) {
		MapX++;
		Player.y = 64 + 16;
		return true;
	}
	if (Player.x < 0) {
		MapY--;
		Player.x = 1280 - 64 - 16;
		return true;
	}
	if (Player.x > 1280) {
		MapY++;
		Player.x = 64 + 16;
		return true;
	}
	return false;
}

void DisplayMap(Map& Map, MapTexture& Textures, /*Entity Enemies[]*/ SDL_Renderer** Renderer)
{
	int textureType = 0, enemyCounter = 0;

	//0 - Трава
	//1 - Стена
	//2 - Препятствие
	//3 - Вход в пещеру
	//4 - Враг
	//5 - Вода
	//6 - Вход в данж
	//7 - Кнопка (Для данжа)

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 20; j++) {
			textureType = Map.map[i][j];
			switch (textureType) {
			case 0: TextureCopy(Renderer, (j * 64), (i * 64), &Textures.Floor); break;
			case 1: {
				TextureCopy(Renderer, (j * 64), (i * 64), &Textures.Wall);
				Map.collisionRects[i][j].x = j * 64;
				Map.collisionRects[i][j].y = i * 64;
				Map.collisionRects[i][j].w = Map.collisionRects[i][j].h = 64;
			}; break;
			case 2: {
				TextureCopy(Renderer, (j * 64), (i * 64), &Textures.Floor);
				TextureCopy(Renderer, (j * 64), (i * 64), &Textures.Rock);
				Map.collisionRects[i][j].x = j * 64;
				Map.collisionRects[i][j].y = i * 64;
				Map.collisionRects[i][j].w = Map.collisionRects[i][j].h = 64;
				Map.rockRects[i][j].x = j * 64;
				Map.rockRects[i][j].y = i * 64;
				Map.rockRects[i][j].w = Map.rockRects[i][j].h = 64;
			}; break;
			case 3: {
				TextureCopy(Renderer, (j * 64), (i * 64), &Textures.CaveEntrance);
				Map.CaveRect.x = j * 64;
				Map.CaveRect.y = i * 64;
				Map.CaveRect.w = Map.CaveRect.h = 64;
			}; break;
			case 4: {
					TextureCopy(Renderer, (j * 64), (i * 64), &Textures.Floor);
			}; break;
			case 5: {
				TextureCopy(Renderer, (j * 64), (i * 64), &Textures.Void);
				Map.collisionRects[i][j].x = j * 64;
				Map.collisionRects[i][j].y = i * 64;
				Map.collisionRects[i][j].w = Map.collisionRects[i][j].h = 64;
			}; break;
			case 6: {
				TextureCopy(Renderer, (j * 64), (i * 64), &Textures.CaveEntrance);
				Map.LegacyDungeonRect.x = j * 64;
				Map.LegacyDungeonRect.y = i * 64;
				Map.LegacyDungeonRect.w = Map.LegacyDungeonRect.h = 64;
			}; break;
			case 7: {
				TextureCopy(Renderer, j * 64, i * 64, &Textures.Button);
				Map.buttonRect.x = j * 64;
				Map.buttonRect.y = i * 64;
				Map.buttonRect.w = Map.buttonRect.h = 64;
			}; break;
			default: break;
			}
		}
	}
}

bool obstacleCheck(Map& Map, Entity& Hero)
{
	int k = 0;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 20; j++) {
			if (Hero.y > Map.collisionRects[i][j].y - 64 && Hero.y <  Map.collisionRects[i][j].y + Map.collisionRects[i][j].h && Hero.x >  Map.collisionRects[i][j].x - 64 && Hero.x < Map.collisionRects[i][j].x + Map.collisionRects[i][j].w) k++;
			if (k != 0) return false;
		}
	}
	return true;
}

void EnemyDisplay(Map& Map, Entity Enemies[])
{
	int enemyCounter = 0, type = 0;

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 20; j++) {
			type = Map.map[i][j];
			if (type == 4) {
				Enemies[enemyCounter].x = j * 64;
				Enemies[enemyCounter].y = i * 64;
				Enemies[enemyCounter].pos = rand() % 4;
				Enemies[enemyCounter].Lives = 3;
				Enemies[enemyCounter].isDead = false;
				enemyCounter++;
			}
		}
	}
	if (enemyCounter < 4) {
		for (int i = enemyCounter; i < 4; i++) {
			Enemies[i].x = Enemies[i].y = -64;
			Enemies[i].Lives = 3;
		}
	}
}


