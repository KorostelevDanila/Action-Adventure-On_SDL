#pragma once //������������ ���� �������, ��������� � ����������

void WindowAndRendererCreating(SDL_Window** Window, SDL_Renderer** Renderer); //�������� ���� � �����������
void RenderPrep(SDL_Renderer** Renderer); //���������� �����������
void RenderPres(SDL_Renderer** Renderer); //���������

void cleanUp(SDL_Window** Window, SDL_Renderer** Renderer); //������� ������ �� ���� � �����������