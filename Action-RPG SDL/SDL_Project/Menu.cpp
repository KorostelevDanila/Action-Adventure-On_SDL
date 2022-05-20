#include "Libraries.h"

int MainMenu(SDL_Renderer** Renderer, int& MusicIsOn, int& SoundIsOn)
{
	Mix_Music* MainMenuOST = NULL;
	if (MusicIsOn == -1) musicPlay(MainMenuOST, -1, "Game Files//Music//MainMenuMusic.mp3");
	
	Mix_Chunk* click = sound("Game Files//Music//click sound.wav");

	SDL_Texture* MainMenuScreen = TextureLoad("Game Files//MainMenu.png", Renderer);
	SDL_Rect Start = { 204, 400, 400 - 204, 508 - 400 };
	SDL_Rect Load = { 548, 400, 742 - 548, 502 - 400 };
	SDL_Rect Options = { 902, 400, 1096 - 902, 502 - 400 };
	SDL_Event event;
	bool inMenu = true;

	while (inMenu) {
		RenderPrep(Renderer);
		SDL_RenderCopy(*Renderer, MainMenuScreen, NULL, NULL);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) return 0;
			else
			if (event.motion.x > Start.x && event.motion.x < Start.x + Start.w && event.motion.y > Start.y && event.motion.y < Start.y + Start.h && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				playsound(SoundIsOn, click);
				inMenu = false;
				return 1;
			} else
			if (event.motion.x > Load.x && event.motion.x < Load.x + Load.w && event.motion.y > Load.y && event.motion.y < Load.y + Load.h && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				playsound(SoundIsOn, click);
				inMenu = false;
				return 2;
			} else
			if (event.motion.x > Options.x && event.motion.x < Options.x + Options.w && event.motion.y > Options.y && event.motion.y < Options.y + Options.h && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				playsound(SoundIsOn, click);
				OptionsMenu(Renderer, MusicIsOn, SoundIsOn, click, MainMenuOST);
			}
		}
		TextureDisplay(Renderer);
		SDL_Delay(16);
	}
	SDL_DestroyTexture(MainMenuScreen);
	Mix_FreeMusic(MainMenuOST);
	Mix_FreeChunk(click);
	//SDL_DestroyTexture();
	return 0;
}

void OptionsMenu(SDL_Renderer** Renderer, int& MusicIsOn, int& SoundIsOn, Mix_Chunk* click, Mix_Music* MainMenuOST)
{
	SDL_Texture* MainMenuScreen = TextureLoad("Game Files//MenuTextures//OptionsMenu.png", Renderer);
	SDL_Texture* MusicON = TextureLoad("Game Files//MenuTextures//MusicOn.png", Renderer);
	SDL_Texture* MusicOFF = TextureLoad("Game Files//MenuTextures//MusicOff.png", Renderer);
	SDL_Texture* SoundON = TextureLoad("Game Files//MenuTextures//SoundOn.png", Renderer);
	SDL_Texture* SoundOFF = TextureLoad("Game Files//MenuTextures//SoundOff.png", Renderer);
	SDL_Rect MusicButton = { 210, 386, 187, 109 };
	SDL_Rect SoundButton = { 588, 386, 187, 109 };
	SDL_Rect BackButton = { 902, 400, 1096 - 902, 502 - 400 };
	SDL_Event event;

	bool inMenu = true;

	while (inMenu) {
		RenderPrep(Renderer);
		SDL_RenderCopy(*Renderer, MainMenuScreen, NULL, NULL);
		if (MusicIsOn == -1) SDL_RenderCopy(*Renderer, MusicON, NULL, &MusicButton);
		else SDL_RenderCopy(*Renderer, MusicOFF, NULL, &MusicButton);

		if (SoundIsOn == 1) SDL_RenderCopy(*Renderer, SoundON, NULL, &SoundButton);
		else SDL_RenderCopy(*Renderer, SoundOFF, NULL, &SoundButton);

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) exit(1);
			else
			if (event.motion.x > MusicButton.x && event.motion.x < MusicButton.x + MusicButton.w && event.motion.y > MusicButton.y && event.motion.y < MusicButton.y + MusicButton.h && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				playsound(SoundIsOn, click);
				if (MusicIsOn == -1) {
					MusicIsOn = 0;
				}
				else {
					MusicIsOn = -1;
				}
				if (!Mix_PlayingMusic()) musicPlay(MainMenuOST, MusicIsOn, "Game Files//Music//MainMenuMusic.mp3");
				else if (Mix_PausedMusic()) musicPlay(MainMenuOST, MusicIsOn, "Game Files//Music//MainMenuMusic.mp3");
				else Mix_PauseMusic();
				//inMenu = false;
			}
			else
			if (event.motion.x > SoundButton.x && event.motion.x < SoundButton.x + SoundButton.w && event.motion.y > SoundButton.y && event.motion.y < SoundButton.y + SoundButton.h && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				if (SoundIsOn == 1) SoundIsOn = 0;
				else SoundIsOn = 1;
				playsound(SoundIsOn, click);
				//inMenu = false;
			}
			else
			if (event.motion.x > BackButton.x && event.motion.x < BackButton.x + BackButton.w && event.motion.y > BackButton.y && event.motion.y < BackButton.y + BackButton.h && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				playsound(SoundIsOn, click);
				inMenu = false;
			}
		}
		TextureDisplay(Renderer);
		//SDL_Delay(16);
	}

	SDL_DestroyTexture(MusicOFF);
	SDL_DestroyTexture(MusicON);
	SDL_DestroyTexture(SoundON);
	SDL_DestroyTexture(SoundOFF);
	SDL_DestroyTexture(MainMenuScreen);
}

void GameOver(SDL_Renderer** Renderer)
{
	SDL_Texture* MainMenuScreen = TextureLoad("Game Files//MenuTextures//GameOverScreen.png", Renderer);
	SDL_Rect Exit = { 531, 414, 187, 109 };
	Mix_Chunk* click = sound("Game Files//Music//click sound.wav");
	SDL_Event event;
	bool menu = true;
	while (menu) {
		RenderPrep(Renderer);
		SDL_RenderCopy(*Renderer, MainMenuScreen, NULL, NULL);
		while (SDL_PollEvent(&event)) {
			if (event.motion.x > Exit.x && event.motion.x < Exit.x + Exit.w && event.motion.y > Exit.y && event.motion.y < Exit.y + Exit.h && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				playsound(1, click);
				menu = false;
			}
		}
		TextureDisplay(Renderer);
	}
	SDL_DestroyTexture(MainMenuScreen);
}

void Victory(SDL_Renderer** Renderer)
{
	SDL_Texture* MainMenuScreen = TextureLoad("Game Files//MenuTextures//VictoryScreen.png", Renderer);
	SDL_Rect Exit = { 531, 414, 187, 109 };
	Mix_Chunk* click = sound("Game Files//Music//click sound.wav");
	SDL_Event event;
	bool menu = true;
	while (menu) {
		RenderPrep(Renderer);
		SDL_RenderCopy(*Renderer, MainMenuScreen, NULL, NULL);
		while (SDL_PollEvent(&event)) {
			if (event.motion.x > Exit.x && event.motion.x < Exit.x + Exit.w && event.motion.y > Exit.y && event.motion.y < Exit.y + Exit.h && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				playsound(1, click);
				menu = false;
			}
		}
		TextureDisplay(Renderer);
	}
	SDL_DestroyTexture(MainMenuScreen);
}

void LoadNewGame(Entity* Player, int& MapX, int& MapY)
{
	MapX = 2;
	MapY = 1;

	Player->x = 640;
	Player->y = 384;
	Player->dx = 16;
	Player->dy = 16;
	Player->Lives = 5;
	Player->Damage = 1;
	Player->Arrows = 0;
}

bool LoadGame(Entity* Player, int& MapX, int& MapY, const char* savepath) {
	ifstream file;
	file.open(savepath);

	if (!file) {
		cout << "Problem occured during save loading." << endl;
		return false;
	}

	file >> MapX;
	file >> MapY;

	file >> Player->x;
	file >> Player->y;
	file >> Player->dx;
	file >> Player->dy;
	file >> Player->Lives;
	file >> Player->Damage;
	file >> Player->Arrows;
	file >> Player->Bombs;

	file >> Player->fireAbility;
	file >> Player->fightAbility;

	file >> Player->Coins;

	file.close();

	return true;
}

bool PauseMenu(SDL_Renderer** Renderer, int& MusicIsOn, int& SoundIsOn, Entity* Player, int& MapX, int& MapY)
{
	Mix_Music* MainMenuOST = NULL;
	if (MusicIsOn == -1) musicPlay(MainMenuOST, -1, "Game Files//Music//MainMenuMusic.mp3");

	Mix_Chunk* click = sound("Game Files//Music//click sound.wav");

	SDL_Texture* MainMenuScreen = TextureLoad("Game Files//MenuTextures//PauseMenu.png", Renderer);
	SDL_Rect Continue = { 156, 363, 187, 109 };
	SDL_Rect Save = { 438, 357, 187, 109 };
	SDL_Rect Options = { 720, 357, 187, 109 };
	SDL_Rect Quit = { 984, 354, 187, 109 };
	SDL_Event event;
	bool inMenu = true;
	bool choose = true;

	while (inMenu) {
		RenderPrep(Renderer);
		SDL_RenderCopy(*Renderer, MainMenuScreen, NULL, NULL);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) return 0;
			else
			if (event.motion.x > Continue.x && event.motion.x < Continue.x + Continue.w && event.motion.y > Continue.y && event.motion.y < Continue.y + Continue.h && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				playsound(SoundIsOn, click);
				inMenu = false;
				choose = true;
			//return 1;
			}
			else
			if (event.motion.x > Save.x && event.motion.x < Save.x + Save.w && event.motion.y > Save.y && event.motion.y < Save.y + Save.h && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && !(Player->isInDungeon) && !(Player->isInLegacyDungeon)) {
				playsound(SoundIsOn, click);
				SaveGame(Player, MapX, MapY);
				inMenu = false;
				choose = true;
			//return 2;
			}
			else
			if (event.motion.x > Options.x && event.motion.x < Options.x + Options.w && event.motion.y > Options.y && event.motion.y < Options.y + Options.h && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				playsound(SoundIsOn, click);
				OptionsMenu(Renderer, MusicIsOn, SoundIsOn, click, MainMenuOST);
			}
			else
				if (event.motion.x > Quit.x && event.motion.x < Quit.x + Quit.w && event.motion.y > Quit.y && event.motion.y < Quit.y + Quit.h && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
					playsound(SoundIsOn, click);
					inMenu = false;
					choose = false;
			}
		}
		TextureDisplay(Renderer);
		SDL_Delay(16);
	}
	SDL_DestroyTexture(MainMenuScreen);
	Mix_FreeMusic(MainMenuOST);
	Mix_FreeChunk(click);
	return choose;
}


void SaveGame(Entity* Player, int MapX, int MapY)
{
	ofstream file;
	file.open("Game Files//Saves//Save File.txt");

	if (!file) {
		cout << "Problem occured during save loading." << endl;
		//return false;
	}

	file << MapX << endl;
	file << MapY << endl;

	file << Player->x << endl;
	file << Player->y << endl;
	file << Player->dx << endl;
	file << Player->dy << endl;
	file << Player->Lives << endl;
	file << Player->Damage << endl;
	file << Player->Arrows << endl;
	file << Player->Bombs << endl;

	file << Player->fireAbility << endl;
	file << Player->fightAbility << endl;

	file << Player->Coins;

	file.close();

	//return true;
}
