#include "PlayGround.h"


PlayGround::PlayGround() : POSITION_X(0), POSITION_Y(0), snake(nullptr),
playing(false), paused(false)
{
}

PlayGround::PlayGround(const int xPos, const int yPos) :
POSITION_X(xPos), POSITION_Y(yPos), snake(nullptr), playing(false), paused(false)
{
}


PlayGround::~PlayGround()
{
	delete snake;
	//delete playFieldTexture;
}

bool PlayGround::initialize()
{
	bool success = true;
	try
	{
		snake = new Snake();		
	}
	catch (std::bad_alloc ex)
	{
		printf("Failed to create snake! Exception: %s.\n", ex.what());
		success = false;
	}

	// If the snake was created successfuly 
	if (success)
	{	// Initialize the snake
		success = snake->initialize(100, 100);
		playing = false;
		paused = false;
	}
	
	return success;
}

bool PlayGround::loadMedia(SDL_Renderer *renderer)
{
	// If the snake image could not be loaded
	if (!snake->loadImage(renderer))
		return false;	// return false
	else
		// Otherwise return the result of loading background image
		return playFieldTexture.loadImage("Images/snakeBG.png", renderer);
}

bool PlayGround::isPlaying()
{
	return playing;
}

bool PlayGround::isPaused()
{
	return paused;
}

void PlayGround::updatePG()
{
	int headDirection = snake->getHeadDirection();

	while (SDL_PollEvent(&e))
	{
		if (!paused)
		{			
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				moveSnakeUp(headDirection);
				break;
			case SDLK_a:
				moveSnakeLeft(headDirection);
				break;
			case SDLK_d:
				moveSnakeRight(headDirection);
				break;
			case SDLK_s:
				moveSnakeDown(headDirection);
				break;
			case SDLK_p:
				pause();
				break;
			case SDLK_ESCAPE:
				stopPlay();
			}
		}
		else
			if (e.key.keysym.sym == SDLK_p)
				unpause();

		if (e.type == SDL_QUIT)
			stopPlay();
	}
}


void PlayGround::renderPG(SDL_Renderer *renderer)
{
	playFieldTexture.render(0, 0, renderer);
	snake->render(renderer);
}

void PlayGround::moveSnakeUp(int headDirection)
{
	switch (headDirection)
	{
	case DIRECTION_UP_0_DEG:
		snake->goForward(FIELD_WIDTH, POSITION_X, FIELD_HEIGHT, POSITION_Y);
		break;
	case DIRECTION_LEFT_90_DEG:
		snake->goRight(FIELD_WIDTH, POSITION_X, FIELD_HEIGHT, POSITION_Y);
		break;
	case DIRECTION_RIGHT_270_DEG:
		snake->goLeft(FIELD_WIDTH, POSITION_X, FIELD_HEIGHT, POSITION_Y);
	}
}

void PlayGround::moveSnakeDown(int headDirection)
{
	switch (headDirection)
	{
	case DIRECTION_DOWN_180_DEG:
		snake->goForward(FIELD_WIDTH, POSITION_X, FIELD_HEIGHT, POSITION_Y);
		break;
	case DIRECTION_LEFT_90_DEG:
		snake->goLeft(FIELD_WIDTH, POSITION_X, FIELD_HEIGHT, POSITION_Y);
		break;
	case DIRECTION_RIGHT_270_DEG:
		snake->goRight(FIELD_WIDTH, POSITION_X, FIELD_HEIGHT, POSITION_Y);
	}
}

void PlayGround::moveSnakeLeft(int headDirection)
{
	switch (headDirection)
	{
	case DIRECTION_LEFT_90_DEG:
		snake->goForward(FIELD_WIDTH, POSITION_X, FIELD_HEIGHT, POSITION_Y);
		break;
	case DIRECTION_DOWN_180_DEG:
		snake->goRight(FIELD_WIDTH, POSITION_X, FIELD_HEIGHT, POSITION_Y);
		break;
	case DIRECTION_UP_0_DEG:
		snake->goLeft(FIELD_WIDTH, POSITION_X, FIELD_HEIGHT, POSITION_Y);
	}
}

void PlayGround::moveSnakeRight(int headDirection)
{
	switch (headDirection)
	{
	case DIRECTION_RIGHT_270_DEG:
		snake->goForward(FIELD_WIDTH, POSITION_X, FIELD_HEIGHT, POSITION_Y);
		break;
	case DIRECTION_DOWN_180_DEG:
		snake->goLeft(FIELD_WIDTH, POSITION_X, FIELD_HEIGHT, POSITION_Y);
		break;
	case DIRECTION_UP_0_DEG:
		snake->goRight(FIELD_WIDTH, POSITION_X, FIELD_HEIGHT, POSITION_Y);
	}
}

void PlayGround::pause()
{
	paused = true;
}

void PlayGround::unpause()
{
	paused = false;
}

void PlayGround::startPlay()
{
	playing = true;
}

void PlayGround::stopPlay()
{
	playing = false;
}
