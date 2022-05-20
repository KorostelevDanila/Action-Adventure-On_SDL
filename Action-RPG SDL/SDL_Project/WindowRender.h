#pragma once //Заголовочный файл функций, связанных с отрисовкой

void WindowAndRendererCreating(SDL_Window** Window, SDL_Renderer** Renderer); //Создание окна и отрисовщика
void RenderPrep(SDL_Renderer** Renderer); //Подготовка отрисовщика
void RenderPres(SDL_Renderer** Renderer); //Отрисовка

void cleanUp(SDL_Window** Window, SDL_Renderer** Renderer); //Очистка памяти от окна и отрисовщика