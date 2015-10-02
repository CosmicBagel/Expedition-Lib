#pragma once

#include <SDL.h>

typedef struct Int2d {
	int x;
	int y;
} Int2d;

void AddInt2d(Int2d *a,const Int2d *b) {
	a->x += b->x;
	a->y += b->y;
};

SDL_Window *window;
SDL_Renderer *renderer;
int done;

Int2d ballPos;
Int2d paddlePos;
Int2d ballVel;

int
loop();

void
GameLogicInit();

void
UpdateGame();

void
OnUpKey();

void 
OnDownKey();

void
DrawChessBoard(SDL_Renderer *renderer);

void
DrawBackdrop(SDL_Renderer *renderer);

void
DrawPaddle(SDL_Renderer *renderer);

void 
DrawBall(SDL_Renderer *renderer);