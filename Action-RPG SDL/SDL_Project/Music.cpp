#include "Libraries.h"

void musicPlay(Mix_Music* music, int MusicIsOn, const char* filename) {
	music = Mix_LoadMUS(filename);
	Mix_PlayMusic(music, MusicIsOn);
}

Mix_Chunk* sound(const char* file)
{
	//Mix_PlayChannel(-1, sound, 0);
	return Mix_LoadWAV(file);
}

void playsound(int SoundIsOn, Mix_Chunk* sound) {
	if (SoundIsOn == 1) Mix_PlayChannel(-1, sound, 0);
}
