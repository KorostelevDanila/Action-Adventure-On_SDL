#include "Libraries.h"
//#include "WindowRender.h"

int WINDOW_WEIDTH = 1280;
int WINDOW_HEIGHT = 768;

void WindowAndRendererCreating(SDL_Window** Window, SDL_Renderer** Renderer)
{
	if (SDL_INIT_EVERYTHING == 0) {
		cout << "The problem occured during SDL initialization. SDL Error code: " << SDL_GetError();
		exit(1);
	}
	else {
		*Window = SDL_CreateWindow("Action-Adventure", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WEIDTH, WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
		if (Window == NULL) {
			cout << "The problem occured during window creating. SDL Error code: " << SDL_GetError();
			exit(1);
		}
		else {
			*Renderer = SDL_CreateRenderer(*Window, -1, SDL_RENDERER_ACCELERATED);
			if (*Renderer == NULL) {
				cout << "The problem occured during renderer creatin. SDL Error code: " << SDL_GetError();
				exit(1);
			}
		}
	}
}

void RenderPrep(SDL_Renderer** Renderer)
{
	SDL_SetRenderDrawColor(*Renderer, 60, 169, 234, 135);
	SDL_RenderClear(*Renderer);
}

void RenderPres(SDL_Renderer** Renderer)
{
	SDL_RenderPresent(*Renderer);
}

void cleanUp(SDL_Window** Window, SDL_Renderer** Renderer)
{
	TTF_Quit();
	SDL_DestroyRenderer(*Renderer);
	SDL_DestroyWindow(*Window);
}
