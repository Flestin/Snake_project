#include "Game.h"


Game::Game() : gWindow(nullptr), gRenderer(nullptr), isRunning(false)
{
	try
	{
		playMode = new PlayGround(0, 0);
	}
	catch (std::bad_alloc ex)
	{
		printf("Failed to allocate playGround! Exception: %s.\n",
			ex.what());
	}
}


Game::~Game()
{
	close();
}

bool Game::initializeGame()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Unable to initialize SDL! SDL_Error: %s.\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			printf("Warning: linear rendering not set!\n");

		// Create a window
		gWindow = SDL_CreateWindow(
			"Snake",											// Title
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,		// X Y positions
			WINDOW_WIDTH, WINDOW_HEIGHT,						// Dimension of the window
			SDL_WINDOW_SHOWN);									// Window flag

		// If the window wasn't created
		if (!gWindow)
		{
			printf("Unable to create window! SDL_Error: %s.\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer
			gRenderer = SDL_CreateRenderer(gWindow, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			// If the renderer wasn't created
			if (!gRenderer)
			{
				printf("Failed to create renderer! SDL_Error: %s.\n",
					SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize SDL_img
				if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
				{
					printf("Failed to initialize SDL_img! SDL_img_error: %s.\n",
						IMG_GetError());
					success = false;
				}
			}
		}
	}

	if (success)
	{
		if (!playMode->initialize())
		{
			printf("Failed to initialize playground!\n");
			success = false;
		}
	}
	return success;
}