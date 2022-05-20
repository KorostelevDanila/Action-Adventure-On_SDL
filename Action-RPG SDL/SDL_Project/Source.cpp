#include "Libraries.h"
//Основной файл с игровым циклом

int main(int args, char* argc[]) {
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	srand(time(NULL));
	SDL_Window* Main_Window = NULL;
	SDL_Renderer* Main_Renderer = NULL;

	WindowAndRendererCreating(&Main_Window, &Main_Renderer);
	RenderPrep(&Main_Renderer);
	RenderPres(&Main_Renderer);

	ttf_init();
	TTF_Font* mainFont = NULL;
	mainFont = TTF_OpenFont("Game Files//pixelcyr_normal.ttf", 50);

	textureInitialize();

	Entity Player; // Сущность игрока и его стандартное положение на экране

	SDL_Texture* Interface = TextureLoad("Game Files//Interface.png", &Main_Renderer);
	SDL_Rect InterfaceRect = { 0, 0, 64, 128 };

	Entity Arrow;
	bool ArrowOnScreen = false;
	SDL_Texture* ArrowTexture[4];
	ArrowTexture[0] = TextureLoad("Game Files//ArrowDown.png", &Main_Renderer);
	ArrowTexture[1] = TextureLoad("Game Files//ArrowLeft.png", &Main_Renderer);
	ArrowTexture[2] = TextureLoad("Game Files//ArrowUp.png", &Main_Renderer);
	ArrowTexture[3] = TextureLoad("Game Files//ArrowRight.png", &Main_Renderer);

	SDL_Texture* PlayerLivesTexture;
	char PlayerLivesText[10];
	_itoa_s(Player.Lives, PlayerLivesText, 8);
	SDL_Rect PlayerLivesRect = { 32, 0, 32, 32 };
	PlayerLivesTexture = getTextTexture(&Main_Renderer, PlayerLivesText, mainFont);

	SDL_Texture* PlayerBombsTexture;
	char PlayerBombsText[10];
	_itoa_s(Player.Bombs, PlayerBombsText, 8);
	SDL_Rect PlayerBombsRect = { 32, 32, 32, 32 };
	PlayerBombsTexture = getTextTexture(&Main_Renderer, PlayerBombsText, mainFont);

	SDL_Texture* PlayerArrowsTexture;
	char PlayerArrowsText[10];
	_itoa_s(Player.Arrows, PlayerArrowsText, 8);
	SDL_Rect PlayerArrowsRect = { 32, 64, 32, 32 };
	PlayerArrowsTexture = getTextTexture(&Main_Renderer, PlayerArrowsText, mainFont);

	SDL_Texture* PlayerCoinsTexture;
	char PlayerCoinsText[10];
	_itoa_s(Player.Coins, PlayerCoinsText, 8);
	SDL_Rect PlayerCoinsRect = { 32, 96, 32, 32 };
	PlayerCoinsTexture = getTextTexture(&Main_Renderer, PlayerCoinsText, mainFont);

	SDL_Texture* MainHero[4];
	MainHero[0] = TextureLoad("Game Files//MainHeroFront.png", &Main_Renderer); //Текстуры для главного героя
	MainHero[2] = TextureLoad("Game Files//MainHeroBack.png", &Main_Renderer);
	MainHero[1] = TextureLoad("Game Files//MainHeroLeft.png", &Main_Renderer);
	MainHero[3] = TextureLoad("Game Files//MainHeroRight.png", &Main_Renderer);
	SDL_Texture* MainHeroShield[4];
	MainHeroShield[0] = TextureLoad("Game Files//MainHeroShieldFront.png", &Main_Renderer);
	MainHeroShield[1] = TextureLoad("Game Files//MainHeroShieldLeft.png", &Main_Renderer);
	MainHeroShield[2] = TextureLoad("Game Files//MainHeroShieldBack.png", &Main_Renderer);
	MainHeroShield[3] = TextureLoad("Game Files//MainHeroShieldRight.png", &Main_Renderer);

	SDL_Texture* SwordDungeon = TextureLoad("Game Files//Sword.png", &Main_Renderer);
	SDL_Rect SwordDungeonRect;
	SDL_Texture* BowDungeon = TextureLoad("Game Files//Bow.png", &Main_Renderer);
	SDL_Rect BowDungeonRect;

	Entity Bomb;
	Bomb.x = Bomb.y = -64;
	bool BombOnScreen = false;
	SDL_Texture* BombTexture = TextureLoad("Game Files//Bomb.png", &Main_Renderer);
	SDL_Rect BombHitBox;
	SDL_Rect BombPick;

	Player.texture = MainHero[0];
	Player.pos = 2;

	Entity Enemy[4];
	SDL_Texture* EnemyOverworld[4];
	EnemyOverworld[0] = TextureLoad("Game Files//EnemyOverworldDown.png", &Main_Renderer); //Текстуры для врагов
	EnemyOverworld[2] = TextureLoad("Game Files//EnemyOverworldUp.png", &Main_Renderer);
	EnemyOverworld[1] = TextureLoad("Game Files//EnemyOverworldLeft.png", &Main_Renderer);
	EnemyOverworld[3] = TextureLoad("Game Files//EnemyOverworldRight.png", &Main_Renderer);
	SDL_Texture* Bullet = TextureLoad("Game Files//Bullet.png", &Main_Renderer);

	Map OverworldMap[3][4]; // Создание карты, загрузка текстур для карты
	MapTexture OverworldMapTextures;
	OverworldMapTextures.Floor = TextureLoad("Game Files//GrassTextureNoShadows.png", &Main_Renderer);
	OverworldMapTextures.Wall = TextureLoad("Game Files//WallOverworld.png", &Main_Renderer);
	OverworldMapTextures.Rock = TextureLoad("Game Files//Rock.png", &Main_Renderer);
	OverworldMapTextures.CaveEntrance = TextureLoad("Game Files//CaveEnter.png", &Main_Renderer);
	//OverworldMapTextures.Void = TextureLoad("Game Files//OverworldVoid.png", &Main_Renderer);

	Map Caves[3];
	if (!LoadCave(Caves, "Game Files//Map//CaveMaps.txt")) {
		return -1;
	}
	MapTexture CaveTextures;
	CaveTextures.Floor = TextureLoad("Game Files//CaveFloor.png", &Main_Renderer);
	CaveTextures.Wall = TextureLoad("Game Files//CaveWall.png", &Main_Renderer);

	Map LegacyDungeonMap[3][4];
	LoadMap(LegacyDungeonMap, "Game Files//Map//LegacyDungeonMap.txt");
	MapTexture LegacyDungeonTexture;
	LegacyDungeonTexture.Floor = TextureLoad("Game Files//LegacyDungeonFloor.png", &Main_Renderer);
	LegacyDungeonTexture.Wall = TextureLoad("Game Files//LegacyDungeonWall.png", &Main_Renderer);
	LegacyDungeonTexture.Rock = TextureLoad("Game Files//Rock.png", &Main_Renderer);
	LegacyDungeonTexture.Button = TextureLoad("Game Files//Button.png", &Main_Renderer);
	LegacyDungeonTexture.Void = TextureLoad("Game Files//LegacyDungeonVoid.png", &Main_Renderer);

	SDL_Texture* Hints[3];
	Hints[0] = TextureLoad("Game Files//Hint0.png", &Main_Renderer);
	SDL_Rect Hint0 = { 13 * 64, 2 * 64, 400, 400 };
	Hints[1] = TextureLoad("Game Files//Hint1.png", &Main_Renderer);
	SDL_Rect Hint1 = { 3 * 64, 2 * 64, 400, 400 };
	Hints[2] = TextureLoad("Game Files//Hint2.png", &Main_Renderer);
	SDL_Rect Hint2 = { 10 * 64, 64, 400, 400 };

	Map* MainMap;
	MapTexture* MainMapTexture;

	if (!LoadMap(OverworldMap, "Game Files//Map//OverworldMap.txt")) { //Загрузка карты
		return -1;
	}

	bool ProgRunning = true;
	bool inGame = false;
	bool inMenu = true;
	SDL_Event event;

	int MapX = 2, MapY = 1;
	MainMap = &OverworldMap[MapX][MapY];
	MainMapTexture = &OverworldMapTextures;
	EnemyDisplay(*MainMap, Enemy);

	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

	Mix_Music* OverworldOST = NULL;
	Mix_Music* MarketOST = NULL;
	Mix_Music* LegacyDungeonOST = NULL;
	Mix_Music* VictoryOST = NULL;
	Mix_Music* DefeatOST = NULL;
	Mix_Chunk* ExplosionSound = sound("Game Files//Music//ExplosionSound.wav");
	Mix_Chunk* ArrowSound = sound("Game Files//Music//ArrowSound.wav");
	Mix_Chunk* HitSound = sound("Game Files//Music//HitSound.wav");
	Mix_Chunk* DeathSound = sound("Game Files//Music//DeathSound.wav");
	int MusicIsOn = -1, SoundIsOn = 1;

	Entity* bullets = NULL;
	int bulletCount = 0;
	bullets = (Entity*)malloc(32 * sizeof(Entity));
	HitSound = sound("Game Files//Music//Neco-Arc-sound-effect.wav");

	while (ProgRunning) {
		//if () {
		do {
			switch (MainMenu(&Main_Renderer, MusicIsOn, SoundIsOn)) {
			case 0: {
				ProgRunning = false;
				inMenu = false;
			}; break;
			case 1: {
				LoadNewGame(&Player, MapX, MapY);
				MainMap = &OverworldMap[MapX][MapY];
				MainMapTexture = &OverworldMapTextures;
				EnemyDisplay(*MainMap, Enemy);

				for (int i = 0; i < 4; i++) {
					Enemy[i].Lives = 3;
					Enemy[i].pos = rand() % 4;
					Enemy[i].dx = Enemy[i].dy = 2;
					switch (Enemy[i].pos) {
					case 0: Enemy[i].texture = EnemyOverworld[0]; break;
					case 1: Enemy[i].texture = EnemyOverworld[1]; break;
					case 2: Enemy[i].texture = EnemyOverworld[2]; break;
					case 3: Enemy[i].texture = EnemyOverworld[3]; break;
					default: break;
					}
				}
				if (MusicIsOn == -1) musicPlay(OverworldOST, MusicIsOn, "Game Files//Music//OverworldOST.mp3");
				inGame = true;
				inMenu = false;
			}; break;
			case 2: {
				if (!LoadGame(&Player, MapX, MapY, "Game Files//Saves/Save File.txt"))
					LoadNewGame(&Player, MapX, MapY);


				MainMap = &OverworldMap[MapX][MapY];
				MainMapTexture = &OverworldMapTextures;
				EnemyDisplay(*MainMap, Enemy);

				for (int i = 0; i < 4; i++) {
					Enemy[i].Lives = 3;
					Enemy[i].pos = rand() % 4;
					Enemy[i].dx = Enemy[i].dy = 2;
					switch (Enemy[i].pos) {
					case 0: Enemy[i].texture = EnemyOverworld[0]; break;
					case 1: Enemy[i].texture = EnemyOverworld[1]; break;
					case 2: Enemy[i].texture = EnemyOverworld[2]; break;
					case 3: Enemy[i].texture = EnemyOverworld[3]; break;
					default: break;
					}
				}
				if (MusicIsOn == -1) musicPlay(OverworldOST, MusicIsOn, "Game Files//Music//OverworldOST.mp3");
				inGame = true;
				inMenu = false;
			}; break;
			default: break;
			}
		} while (inMenu);

		while (inGame) {

			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) //ивент хэндлер, связанный с кнопкой закрытия программы
					ProgRunning = inGame = false;
				if (event.key.keysym.sym == SDLK_w && event.type == SDL_KEYDOWN) {
					Player.texture = MainHero[2];
					Player.pos = 2;
					Player.y -= Player.dy;
					if (obstacleCheck(*MainMap, Player) == false)
						Player.y += Player.dy;
				}
				if (event.key.keysym.sym == SDLK_s && event.type == SDL_KEYDOWN) {
					Player.texture = MainHero[0];
					Player.y += Player.dy;
					Player.pos = 0;
					if (obstacleCheck(*MainMap, Player) == false)
						Player.y -= Player.dy;
				}
				if (event.key.keysym.sym == SDLK_a && event.type == SDL_KEYDOWN) {
					Player.texture = MainHero[1];
					Player.x -= Player.dx;
					Player.pos = 1;
					if (obstacleCheck(*MainMap, Player) == false)
						Player.x += Player.dx;
				}
				if (event.key.keysym.sym == SDLK_d && event.type == SDL_KEYDOWN) {
					Player.texture = MainHero[3];
					Player.x += Player.dx;
					Player.pos = 3;
					if (obstacleCheck(*MainMap, Player) == false)
						Player.x -= Player.dx;
				}
				if (event.key.keysym.sym == SDLK_f && event.type == SDL_KEYDOWN && Player.fightAbility == true) {
					for (int i = 0; i < 4; i++) {
						if (EnemyBeat(Player, Enemy[i]) == true) {
							playsound(SoundIsOn, HitSound);
							Mix_PlayChannel(-1, HitSound, 0);
							Enemy[i].Lives -= Player.Damage;
						}
					}
				}
				if (event.key.keysym.sym == SDLK_r && event.type == SDL_KEYDOWN && Player.Arrows > 0 && Player.fireAbility == true && Player.Arrows > 0) {
					if (ArrowOnScreen == false) {
						playsound(SoundIsOn, ArrowSound);
						HeroShoot(Player, Arrow, ArrowTexture);
						Player.Arrows--;
						ArrowOnScreen = true;
					}
				}
				if (event.key.keysym.sym == SDLK_b && event.type == SDL_KEYDOWN && Player.Bombs > 0) {
					if (BombOnScreen == false) {
						if (BombSet(Player, Bomb, *MainMap)) {
							Player.Bombs--;
							BombOnScreen = true;
							Bomb.Reload = 120;
							Bomb.Damage = 3;
							BombHitBox.x = Bomb.x - 64;
							BombHitBox.y = Bomb.y - 64;
							BombHitBox.w = BombHitBox.h = 3 * 64;
						}
					}
				}
				if (event.key.keysym.sym == SDLK_LSHIFT && event.type == SDL_KEYDOWN) {
					Player.getDamage = 0;
					Player.texture = MainHeroShield[Player.pos];
				}
				else {
					Player.getDamage = 1;
					Player.texture = MainHero[Player.pos];
				}
				if (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN) {
					inGame = PauseMenu(&Main_Renderer, MusicIsOn, SoundIsOn, &Player, MapX, MapY);
					if (MusicIsOn == -1) if (Player.isInLegacyDungeon == false) musicPlay(OverworldOST, MusicIsOn, "Game Files//Music//OverworldOST.mp3");
					else musicPlay(OverworldOST, MusicIsOn, "Game Files//Music//LegacyDungeonOST.mp3");
				}
				if (event.key.keysym.sym == SDLK_1 && event.type == SDL_KEYDOWN && Player.isInDungeon == true && MapX == 0) {
					if (Player.Coins >= 10 && Player.fireAbility == true) {
						Player.Coins -= 10;
						Player.Arrows += 5;
					}
				}
				if (event.key.keysym.sym == SDLK_2 && event.type == SDL_KEYDOWN && Player.isInDungeon == true && MapX == 0) {
					if (Player.Coins >= 20) {
						Player.Coins -= 20;
						Player.Bombs += 5;
					}
				}
			}

			if (inGame == false) break;

			if (BombOnScreen) {
				Bomb.Reload--;
				if (Bomb.Reload <= 0) {
					playsound(SoundIsOn, ExplosionSound);
					BombDetonate(BombHitBox, MainMap, Enemy, Bomb.Damage);
					BombHitBox = { 0, 0, 0, 0 };
					Bomb.x = Bomb.y = -64;
					BombOnScreen = false;
				}
			}

			//Проверка для перехода на следующий экран
			if (SwitchMap(Player, MapX, MapY) == true && Player.isInDungeon == false) {
				if (Player.isInLegacyDungeon == true) {
					MainMap = &LegacyDungeonMap[MapX][MapY];
				}
				else MainMap = &OverworldMap[MapX][MapY];
				EnemyDisplay(*MainMap, Enemy);
				for (int i = 0; i < bulletCount; i++) {
					bullets[i].x = bullets[i].y = -64;
				}
				free(bullets);
				int bulletCount = 0;
				bullets = (Entity*)malloc(32 * sizeof(Entity));
			}

			RenderPrep(&Main_Renderer);
			DisplayMap(*MainMap, *MainMapTexture, &Main_Renderer);
			TextureCopy(&Main_Renderer, Player.x, Player.y, &Player.texture);
			EnemyMove(*MainMap, Enemy, EnemyOverworld);

			

			for (int i = 0; i < 4; i++) {
				if (Enemy[i].Lives <= 0) {
					if (Enemy[i].isDead == false) {
						playsound(SoundIsOn, DeathSound);
						Player.Coins += 5;
						Enemy[i].isDead = true;
					}
					Enemy[i].x = Enemy[i].y = -64;
				}
				Enemy[i].texture = EnemyOverworld[Enemy[i].pos];
				TextureCopy(&Main_Renderer, Enemy[i].x, Enemy[i].y, &Enemy[i].texture);
			}


			for (int i = 0; i < 4; i++) {
				if (Enemy[i].x > 0 && Enemy[i].y > 0) {
					if (--Enemy[i].Reload <= 0) {
						bulletCount++;
						bullets[bulletCount - 1] = EnemyShoot(Enemy[i], Bullet);
					}
				}
			}

			if (ArrowOnScreen == true) {
				ArrowOnScreen = ArrowMove(Arrow, Enemy);
				Arrow.texture = ArrowTexture[Arrow.pos];
				TextureCopy(&Main_Renderer, Arrow.x, Arrow.y, &Arrow.texture);
			}

			BulletMove(bullets, bulletCount, Player.x, Player.y, Player.Lives, Player.getDamage);
			for (int i = 0; i < bulletCount; i++) {
				TextureCopy(&Main_Renderer, bullets[i].x, bullets[i].y, &bullets[i].texture);
			}

			if (Player.x >= MainMap->CaveRect.x && Player.x < MainMap->CaveRect.x + 64 && Player.y > MainMap->CaveRect.y - 16 && Player.y < MainMap->CaveRect.y + 64) {
				if (MusicIsOn == -1 && MapX == 0) musicPlay(MarketOST, MusicIsOn, "Game Files//Music//MarketOST.mp3");
				MainMap = &Caves[MapX];
				MainMapTexture = &CaveTextures;
				switch (MapX) {
				case 0: {
					Player.x = 6 * 64;
					Player.y = 9 * 64;
					if (Player.pickedBombs == false) {
						BombPick.x = 4 * 64;
						BombPick.y = 5 * 64;
						BombPick.w = BombPick.h = 64;
					}
				}; break;
				case 1: {
					Player.x = 17 * 64;
					Player.y = 5 * 64;
					if (Player.fireAbility == false) {
						BowDungeonRect.x = 12 * 64;
						BowDungeonRect.y = 5 * 64;
						BowDungeonRect.w = BowDungeonRect.h = 64;
					}
				}; break;
				case 2: {
					Player.x = 3 * 64;
					Player.y = 9 * 64;
					if (Player.fightAbility == false) {
						SwordDungeonRect.x = 3 * 64;
						SwordDungeonRect.y = 3 * 64;
						SwordDungeonRect.w = SwordDungeonRect.h = 64;
					}
				}; break;
				default: break;
				}
				for (int i = 0; i < 4; i++) {
					Enemy[i].x = Enemy[i].y = -64;
				}
				free(bullets);
				int bulletCount = 0;
				bullets = (Entity*)malloc(32 * sizeof(Entity));
				Player.isInDungeon = true;
			}

			if (Player.x >= MainMap->LegacyDungeonRect.x && Player.x < MainMap->LegacyDungeonRect.x + 64 && Player.y > MainMap->LegacyDungeonRect.y - 16 && Player.y < MainMap->LegacyDungeonRect.y + 64) {
				MapX = 2;
				MapY = 1;
				MainMap = &LegacyDungeonMap[MapX][MapY];
				MainMapTexture = &LegacyDungeonTexture;
				if (MusicIsOn == -1) musicPlay(LegacyDungeonOST, MusicIsOn, "Game Files//Music//LegacyDungeonOST.mp3");
				for (int i = 0; i < 4; i++) {
					Enemy[i].x = Enemy[i].y = -64;
				}
				EnemyDisplay(*MainMap, Enemy);
				for (int i = 0; i < bulletCount; i++) {
					bullets[i].x = bullets[i].y = -64;
				}
				free(bullets);
				int bulletCount = 0;
				bullets = (Entity*)malloc(32 * sizeof(Entity));
				Player.isInLegacyDungeon = true;
			}

			if (Player.isInDungeon) {
				switch (MapX) {
				case 0: {
					SDL_RenderCopy(Main_Renderer, Hints[0], NULL, &Hint0);
					if (Player.pickedBombs == false) {
						TextureCopy(&Main_Renderer, BombPick.x, BombPick.y, &BombTexture);
					}
					if (Player.x >= BombPick.x && Player.x <= BombPick.x + BombPick.w && Player.y >= BombPick.y && Player.y <= BombPick.y + BombPick.h) {
						Player.pickedBombs = true;
						Player.Bombs = 5;
					}
				}; break;
				case 1: {
					SDL_RenderCopy(Main_Renderer, Hints[1], NULL, &Hint1);
					if (Player.fireAbility == false) {
						TextureCopy(&Main_Renderer, BowDungeonRect.x, BowDungeonRect.y, &BowDungeon);
					}
					if (Player.x >= BowDungeonRect.x && Player.x <= BowDungeonRect.x + BowDungeonRect.w && Player.y >= BowDungeonRect.y && Player.y <= BowDungeonRect.y + BowDungeonRect.h) {
						Player.fireAbility = true;
						Player.Arrows = 10;
					}
				}; break;
				case 2: {
					SDL_RenderCopy(Main_Renderer, Hints[2], NULL, &Hint2);
					if (Player.fightAbility == false) {
						TextureCopy(&Main_Renderer, SwordDungeonRect.x, SwordDungeonRect.y, &SwordDungeon);
					}
					if (Player.x >= SwordDungeonRect.x && Player.x <= SwordDungeonRect.x + SwordDungeonRect.w && Player.y >= SwordDungeonRect.y && Player.y <= SwordDungeonRect.y + SwordDungeonRect.h)
						Player.fightAbility = true;
				}; break;
				}
			}

			if (Player.isInDungeon == true && (Player.x < 64 || Player.x > 1280 - 64 || Player.y < 64 || Player.y > 768 - 64)) {
				switch (Player.pos) {
				case 0: Player.y = 64; break;
				case 1: Player.x = 1280 - 64; break;
				case 2: Player.y = 768 - 64; break;
				case 3: Player.x = 64; break;
				default: break;
				}
				if (MapX == 0) if (MusicIsOn == -1) musicPlay(OverworldOST, MusicIsOn, "Game Files//Music//OverworldOST.mp3");
				MainMap = &OverworldMap[MapX][MapY];
				MainMapTexture = &OverworldMapTextures;
				EnemyDisplay(*MainMap, Enemy);
				Player.isInDungeon = false;
			}

			if (Player.isInLegacyDungeon == true) {
				if (MainMap == &LegacyDungeonMap[0][0]) {
					if (Arrow.x >= MainMap->buttonRect.x && Arrow.x <= MainMap->buttonRect.x + MainMap->buttonRect.w && Arrow.y >= MainMap->buttonRect.y && Arrow.y <= MainMap->buttonRect.y + MainMap->buttonRect.h) {
						Arrow.x = -64;
						Arrow.y = -64;
						Arrow.dx = 0;
						Arrow.dy = 0;
						ArrowOnScreen = false;
						for (int i = 4; i <= 7; i++) {
							LegacyDungeonMap[2][1].map[i][19] = 0;
							LegacyDungeonMap[2][1].collisionRects[i][19].x = LegacyDungeonMap[2][1].collisionRects[i][19].y = 0;
						}
					}
				}
				if (MainMap == &LegacyDungeonMap[0][2]) {
					if (Player.x >= MainMap->buttonRect.x && Player.x <= MainMap->buttonRect.x + MainMap->buttonRect.w && Player.y >= MainMap->buttonRect.y && Player.y <= MainMap->buttonRect.y + MainMap->buttonRect.h) {
						for (int i = 6; i <= 13; i++) {
							LegacyDungeonMap[2][1].map[0][i] = 0;
							LegacyDungeonMap[2][1].collisionRects[0][i].x = LegacyDungeonMap[2][1].collisionRects[0][i].y = 0;
						}
					}
				}
				if (MainMap == &LegacyDungeonMap[0][1]) {
					if (MusicIsOn == -1) musicPlay(VictoryOST, MusicIsOn, "Game Files//Music//VictoryOST.mp3");
					Victory(&Main_Renderer);
					inGame = false;
					inMenu = true;
					break;
				}
			}

			if (Player.Lives <= 0) {
				if (MusicIsOn == -1) musicPlay(DefeatOST, MusicIsOn, "Game Files//Music//DefeatOST.mp3");
				GameOver(&Main_Renderer);
				inGame = false;
				inMenu = true;
				break;
			}

			TextureCopy(&Main_Renderer, Bomb.x, Bomb.y, &BombTexture);

			SDL_RenderCopy(Main_Renderer, Interface, NULL, &InterfaceRect);

			_itoa_s(Player.Lives, PlayerLivesText, 10);
			SDL_DestroyTexture(PlayerLivesTexture);
			PlayerLivesTexture = getTextTexture(&Main_Renderer, PlayerLivesText, mainFont);
			textDraw(&Main_Renderer, PlayerLivesRect, PlayerLivesTexture);

			_itoa_s(Player.Bombs, PlayerBombsText, 10);
			SDL_DestroyTexture(PlayerBombsTexture);
			PlayerBombsTexture = getTextTexture(&Main_Renderer, PlayerBombsText, mainFont);
			textDraw(&Main_Renderer, PlayerBombsRect, PlayerBombsTexture);

			_itoa_s(Player.Arrows, PlayerArrowsText, 10);
			SDL_DestroyTexture(PlayerArrowsTexture);
			PlayerArrowsTexture = getTextTexture(&Main_Renderer, PlayerArrowsText, mainFont);
			textDraw(&Main_Renderer, PlayerArrowsRect, PlayerArrowsTexture);

			_itoa_s(Player.Coins, PlayerCoinsText, 10);
			SDL_DestroyTexture(PlayerCoinsTexture);
			PlayerCoinsTexture = getTextTexture(&Main_Renderer, PlayerCoinsText, mainFont);
			textDraw(&Main_Renderer, PlayerCoinsRect, PlayerCoinsTexture);

			TextureDisplay(&Main_Renderer);

			SDL_Delay(16);
		}
	}

	free(bullets);
	cleanUp(&Main_Window, &Main_Renderer);

	return 0;
}