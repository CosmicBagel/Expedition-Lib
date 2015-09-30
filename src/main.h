#pragma once

#include <SDL.h>

SDL_Window *window;
SDL_Renderer *renderer;
int done;

int paddlePos;

void
GameLogicInit();

void
DrawChessBoard(SDL_Renderer *renderer);

void
DrawPaddle(SDL_Renderer *renderer);

int
loop();
