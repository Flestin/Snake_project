#pragma once
#include "BodyPart.h"
#include "Texture.h"

const int MAX_BODY_PARTS = 100;

class Snake
{
private:
	BodyPart *body[MAX_BODY_PARTS];
	int currentNumOfBodyParts;
	int lastHeadDirection;
	Texture bodyPartsTexture;
	SDL_Rect clipRects[BODYPART_TOTAL];
	
	// Moves all parts of the snake forward in their direction
	void moveForward(const int xMax, const int xMin,
					 const int yMax, const int yMin);
	
public:
	Snake();
	~Snake();

	// Moves the snake with all his body forward but first it saves its head position
	void goForward(const int xMax, const int xMin,
			       const int yMax, const int yMin);

	// Saves the position of its head than change direction and moves snake forward
	void goLeft(const int xMax, const int xMin,
			    const int yMax, const int yMin);

	// Saves the position of its head than change direction and moves snake forward
	void goRight(const int xMax, const int xMin,
				 const int yMax, const int yMin);

	// Initializes the body of this snake
	bool initialize(int xPos, int yPos);

	// Loads a texture needed to render this snake in graphic interface
	bool loadImage(SDL_Renderer *renderer);

	// Returns the current head direction
	int getHeadDirection();

	// Renders the whole body of this snake
	void render(SDL_Renderer *renderer);

	// Returns the x coordinate of a body part specified by its index
	int getX_ofBodyPart(int index) { return body[index]->getX_Location(); }

	// Returns the y coordinate of a body part specified by its index
	int getY_ofBodyPart(int index) { return body[index]->getY_Location(); }

	// Returns direction of a certain body part
	int getDirection(int index)
	{
		return body[index]->getDirection_Angle();
	}

	// for tests

	// Returns the number of body parts the snake currently has
	int getNumOfBodyParts() { return currentNumOfBodyParts; }

	

	
	char *getBodyType(int index)
	{
		char *type;
		switch (body[index]->getTypeOfBodyPart())
		{
		case BODYPART_HEAD:
			type = "head";
			break;
		case BODYPART_TAIL:
			type = "tail";
			break;
		case BODYPART_CURVED_LEFT:
			type = "cLeft";
			break;
		case BODYPART_CURVED_RIGHT:
			type = "cRight";
			break;
		case BODYPART_STRAIGHT:
			type = "straight";
			break;
		default:
			type = "nothing";
		}		
		return type;
	}	
};

