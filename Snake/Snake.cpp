#include "Snake.h"
#include <atlalloc.h>

Snake::Snake() : 
currentNumOfBodyParts(0), 
lastHeadDirection(DIRECTION_UP_0_DEG)
{
}

Snake::~Snake()
{
	// Delete all pointers to body parts in our array body[]
	for (int i = 0; i < currentNumOfBodyParts; i++)
	{
		delete body[i];
		body[i] = nullptr;
	}
	//delete bodyPartsTexture;
}

void Snake::moveForward(const int xMax, const int xMin,
					    const int yMax, const int yMin)
{
	// Initialize these local vars with head atributes
	int newBodyP = BODYPART_HEAD;
	int newDirection = body[0]->getDirection_Angle();
	int oldBodyP = BODYPART_HEAD;
	int oldDirection = lastHeadDirection;

	// before the loop starts, move with the head and the second body part
	body[0]->moveForward(newDirection, oldBodyP, oldDirection, xMax, xMin, yMax, yMin);

	// store the old values of the body part which is right after head
	oldBodyP = body[1]->getTypeOfBodyPart();
	oldDirection = body[1]->getDirection_Angle();
	body[1]->moveForward(lastHeadDirection, newBodyP, newDirection, xMax, xMin, yMax, yMin);

	// Do this process for the other parts starting from the third one
	for (int i = 2; i < currentNumOfBodyParts - 1; i++)
	{
		// make the old values of the previous BP new for the next body part
		newBodyP = oldBodyP;
		newDirection = oldDirection;

		// and get the old values from the next body part
		oldBodyP = body[i]->getTypeOfBodyPart();
		oldDirection = body[i]->getDirection_Angle();

		// modify the body part's type and direction a move it in proper direction
		body[i]->moveForward(newDirection, newBodyP, lastHeadDirection,
							 xMax, xMin, yMax, yMin);
	}
	
	// Set local var direction for tail
	newDirection = body[currentNumOfBodyParts - 2]->getDirection_Angle();

	// Now move the tail
	body[currentNumOfBodyParts - 1]->moveForward(newDirection, BODYPART_TAIL, 
												 lastHeadDirection,
												 xMax, xMin, yMax, yMin);
}

void Snake::goForward(const int xMax, const int xMin,
					  const int yMax, const int yMin)
{
	// First save the current head direction
	lastHeadDirection = body[0]->getDirection_Angle();

	// Then move tha snake forward
	moveForward(xMax, xMin, yMax, yMin);
}

void Snake::goLeft(const int xMax, const int xMin,
				   const int yMax, const int yMin)
{	
	// First save current head direction before changing it
	lastHeadDirection = body[0]->getDirection_Angle();
	
	// Than change the head direction
	body[0]->turnLeft();

	// and move it forward with all other parts
	moveForward(xMax, xMin, yMax, yMin);
}

void Snake::goRight(const int xMax, const int xMin,
				    const int yMax, const int yMin)
{
	// First save current head direction
	lastHeadDirection = body[0]->getDirection_Angle();

	// Than change the head direction
	body[0]->turnRight();

	// and move it forward with all other parts
	moveForward(xMax, xMin, yMax, yMin);
}

bool Snake::initialize(int xPos, int yPos)
{
	int poc = 0;
	bool success = true;
	// Set a head of our snake
	try
	{
		body[0] = new BodyPart(xPos, yPos, BODYPART_HEAD, DIRECTION_UP_0_DEG);
		poc++;

		// Set a body
		body[1] = new BodyPart(*body[0], 0, 10, BODYPART_STRAIGHT);
		poc++;
		body[2] = new BodyPart(*body[1], 0, 10, BODYPART_STRAIGHT);
		poc++;

		// Set a tail
		body[3] = new BodyPart(*body[2], 0, 10, BODYPART_TAIL);
		poc++;
	}
	catch (std::bad_alloc ex)
	{
		printf("Failed to initialize body part %d! Exception: %s.\n", poc, ex.what());
		for (int i = 0; i < poc; i++)
			delete body[i];
		success = false;
	}

	// If the body was successfully created continue in further snake initialization
	if (success)
	{
		// Set the number of body parts
		currentNumOfBodyParts = 4;

		// Initialize clip rectangles (source rectangels)
		for (int i = 0; i < BODYPART_TOTAL; ++i)
		{
			clipRects[i].w = clipRects[i].h = 10;
			clipRects[i].x = i * 10;
			clipRects[i].y = 0;
		}

		// Set the direction our snake is heading
		lastHeadDirection = DIRECTION_UP_0_DEG;
	}

	return success;
}

bool Snake::loadImage(SDL_Renderer *renderer)
{
	return bodyPartsTexture.loadImage("Images/body_parts.png", renderer);
}

void Snake::render(SDL_Renderer *renderer)
{
	// Render every part of the snake's body
	for (int i = 0; i < currentNumOfBodyParts; ++i)
	{
		bodyPartsTexture.render(
			body[i]->getX_Location(),					// get x coor
			body[i]->getY_Location(),					// get y coor
			renderer,
			&clipRects[body[i]->getTypeOfBodyPart()],
			body[i]->getDirection_Angle());
	}		
}

int Snake::getHeadDirection()
{
	return body[0]->getDirection_Angle();
}

