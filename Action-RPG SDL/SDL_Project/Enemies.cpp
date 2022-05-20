#include "Libraries.h"

void EnemyMove(Map& Map, Entity Enemy[], SDL_Texture* EnemyOverworld[])
{
	for (int i = 0; i < 4; i++) {
		bool collisionFlag = false;
		do {
			collisionFlag = obstacleCheck(Map, Enemy[i]);// && Enemy[i].x > 64 && Enemy[i].x < 1280-64 && Enemy[i].y > 64 && Enemy[i].y < 768-64);
			if (collisionFlag && Enemy[i].x > 64 && Enemy[i].x < 1280 - 64 && Enemy[i].y > 64 && Enemy[i].y < 768 - 64) {
				switch (Enemy[i].pos) {
				case 0: {
					Enemy[i].y += Enemy[i].dy;
				}; break;
				case 1: {
					Enemy[i].x -= Enemy[i].dx;
				}; break;
				case 2: {
					Enemy[i].y -= Enemy[i].dy;
				}; break;
				case 3: {
					Enemy[i].x += Enemy[i].dx;
				}; break;
				default: break;
				}
			}
			else if (Enemy[i].x != -64 && Enemy[i].y != - 64) {
				switch (Enemy[i].pos) {
				case 0: {
					Enemy[i].y -= Enemy[i].dy;
				}; break;
				case 1: {
					Enemy[i].x += Enemy[i].dx;
				}; break;
				case 2: {
					Enemy[i].y += Enemy[i].dy;
				}; break;
				case 3: {
					Enemy[i].x -= Enemy[i].dx;
				}; break;
				default: break;
				}
				Enemy[i].pos = rand() % 4;
			}
		} while (collisionFlag == false);
	}
}

void BulletMove(Entity* bullets, int& bulletCount, int PlayerX, int PlayerY, int& PlayerLives, int PlayerGetDamage)
{
	int tmpCount = bulletCount;
	for (int i = 0; i < tmpCount; i++) {
		bullets[i].x += bullets[i].dx;
		bullets[i].y += bullets[i].dy;

		if (bullets[i].x > 1280 || bullets[i].x < 0 || bullets[i].y < 0 || bullets[i].y > 768) {
			for (int j = i; j < bulletCount - 1; j++) {
				bullets[j] = bullets[j+1];
			}
			bulletCount--;
		}
		else if (bullets[i].x > PlayerX - 32 && bullets[i].x < PlayerX + 32 && bullets[i].y > PlayerY - 32 && bullets[i].y < PlayerY + 32) {
			bullets[i].x = bullets[i].y = -64;
			for (int j = i; j < bulletCount - 1; j++) {
				bullets[j] = bullets[j + 1];
			}
			bulletCount--;
			if (PlayerGetDamage == 1) PlayerLives -= bullets[i].Damage;
		}
	}
}



Entity EnemyShoot(Entity& Enemy, SDL_Texture* Bullet)
{
	Entity* bullet;

	bullet = (Entity*) malloc(sizeof(Entity));
	memset(bullet, 0, sizeof(Entity));

	bullet->x = Enemy.x;
	bullet->y = Enemy.y;
	//bullet->dx = Enemy.dx * 2;
	//bullet->dy = Enemy.dy * 2;
	bullet->Damage = 1;
	bullet->texture = Bullet;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

	switch (Enemy.pos) {
	case 0: bullet->dy = Enemy.dy * 2; break;
	case 1: bullet->dx = Enemy.dx * (-2); break;
	case 2: bullet->dy = Enemy.dy * (-2); break;
	case 3: bullet->dx = Enemy.dx * 2; break;
	default: break;
	}

	Enemy.Reload = 240;

	return *bullet;
}

bool EnemyBeat(Entity& Player, Entity& Enemy)
{
	if (Player.x > Enemy.x - 64 && Player.x < Enemy.x + 128 && Player.y > Enemy.y - 64 && Player.y < Enemy.y + 128) return true;
	else return false;
}
