#pragma once
#include "Snake.h"


const int FIELD_WIDTH = 703;
const int FIELD_HEIGHT = 800;

class PlayGround
{
	const int POSITION_X, POSITION_Y;
	Snake *snake;
	Texture playFieldTexture;
	SDL_Event e;
	bool playing;
	bool paused;

public:
	PlayGround();
	PlayGround(const int xPos, const int yPos);
	~PlayGround();

	// Initializes the playGround
	bool initialize();

	// Loads background image and snake image
	bool loadMedia(SDL_Renderer *renderer);

	// Is the gameplay paused?
	bool isPaused();

	bool isPlaying();

	// Evaluates all events and update snake
	void updatePG();

	// Renders background and than the snake
	void renderPG(SDL_Renderer *renderer);


	/* Move snake in desired direction */
	void moveSnakeUp(int headDirection);
	void moveSnakeDown(int headDirection);
	void moveSnakeLeft(int headDirection);
	void moveSnakeRight(int headDirection);

	// Pauses the game
	void pause();

	// Resumes the game
	void unpause();

	// Starts the game
	void startPlay();

	// Stops the game
	void stopPlay();
};

