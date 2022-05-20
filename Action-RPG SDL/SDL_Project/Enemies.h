#pragma once

void EnemyMove(Map& Map, Entity Enemy[], SDL_Texture* EnemyOverworld[]);
void BulletMove(Entity* bullets, int& bulletCount, int PlayerX, int PlayerY, int& PlayerLives, int PlayerGetDamage);
Entity EnemyShoot(Entity& Enemy, SDL_Texture* Bullet);
bool EnemyBeat(Entity& Player, Entity& Enemy);
