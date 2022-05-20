#pragma once

void musicPlay(Mix_Music* music, int MusicIsOn, const char* filename);
Mix_Chunk* sound(const char* file);
void playsound(int SoundIsOn, Mix_Chunk* sound);