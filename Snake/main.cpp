#include "PlayGround.h"
#include <iostream>
#include <conio.h>

// Hah I'm using the git banch :D:D

SDL_Window *gWindow;
SDL_Renderer *gRenderer;

void printSnake(Snake *snake)
{
	int amount = snake->getNumOfBodyParts();
	for (int i = 0; i < amount; ++i)
	{		
		printf("[%3i] %-8s -> X:%3i    Y:%3i     Angle:%4i  ||\n",
			i,
			snake->getBodyType(i),
			snake->getX_ofBodyPart(i),
			snake->getY_ofBodyPart(i),
			snake->getDirection(i));
	}
}

int main(int args, char *argc[])
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	PlayGround *pg = new PlayGround(0, 0);
	gWindow = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		FIELD_WIDTH, FIELD_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	
	if (pg->initialize() && pg->loadMedia(gRenderer))
	{

		pg->startPlay();
		bool quit = false;
		
		while (!quit)
		{
			pg->updatePG();
			
			SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
			SDL_RenderClear(gRenderer);
			pg->renderPG(gRenderer);
			SDL_RenderPresent(gRenderer);

			quit = !pg->isPlaying();
		}
	}


	delete pg;
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	IMG_Quit();
	SDL_Quit();
	return 0;

}
