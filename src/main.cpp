#include "main.h"

int main(int argc, char** argv) {

	SDL_Surface *surface;
	
	/* Enable standard application logging */
	SDL_LogSetPriority(
		SDL_LOG_CATEGORY_APPLICATION,
		SDL_LOG_PRIORITY_INFO);

	/* Initalize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"SDL_Init fail : %s\n", SDL_GetError());
		return 1;
	}

	/* Create window and renderer for given surface */
	window = SDL_CreateWindow(
		"Shpongle",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		SDL_WINDOW_SHOWN);

	if (!window) {
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Window creation fail : %s\n", SDL_GetError());
		return 1;
	}

	surface = SDL_GetWindowSurface(window);
	renderer = SDL_CreateSoftwareRenderer(surface);
	if (!renderer) {
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Render creation for surface fail : %s\n", SDL_GetError());
		return 1;
	}

	GameLogicInit();

	/* Draw the Image on rendering surface */
	done = 0;
	while (!done) {
		loop();
	}

    SDL_Quit();
    return 0;
}

void
GameLogicInit() {
	paddlePos = 0;
}

void
DrawChessBoard(SDL_Renderer *renderer)
{
	int row = 0, column = 0, x = 0;
	SDL_Rect rect, darea;

	/* Get the Size of the drawing surface */
	SDL_RenderGetViewport(renderer, &darea);

	for (; row < 8; row++) {
		column = row % 2;
		x = column;
		for (; column < 4 + (row % 2); column++) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);

			rect.w = darea.w / 8;
			rect.h = darea.h / 8;
			rect.x = x * rect.w;
			rect.y = row * rect.h;
			x = x + 2;
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void
DrawPaddle(SDL_Renderer *renderer)
{
	/*xywh*/
	SDL_Rect paddle = { 0, paddlePos, 16, 128};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &paddle);
}

/* 
	- ball velocity
	- collision detection
	- collision event
*/

int
loop()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			done = 1;
			return 0;
		}
		if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_ESCAPE)) {
			done = 1;
			return 0;
		}
		if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_UP)) {
			paddlePos+=8;
		}
		if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_DOWN)) {
			paddlePos-=8;
		}
	}

	/* Clear the rendering surface with the specified color */
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	
	DrawChessBoard(renderer);
	DrawPaddle(renderer);
	/* Got everything on rendering surface,
	   now Update the drawing image on window screen */
	SDL_UpdateWindowSurface(window);
	
	return 0;
}