#pragma once
#include "PlayGround.h"

const int WINDOW_WIDTH = FIELD_WIDTH;
const int WINDOW_HEIGHT = FIELD_HEIGHT;

class Game
{
private:
	SDL_Window *gWindow;
	SDL_Renderer *gRenderer;
	bool isRunning;
	PlayGround *playMode;

public:
	Game();
	~Game();

	// Initializes SDL and its subsystems, window and renderer
	bool initializeGame();
	bool loadMedia();
	void close();

	void startGame();
	void pauseGame();
	void stopGame();

	bool isPlaying();
};

