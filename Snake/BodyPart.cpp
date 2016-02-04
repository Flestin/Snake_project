#include "BodyPart.h"
#include <allocators>

BodyPart::BodyPart(int xC, int yC, int bodyType, int dir) :
x(xC), y(yC), typeOfBodyPart(bodyType), direction(dir)
{
}

BodyPart::BodyPart(BodyPart &otherB, int plusX, int plusY, int bodyType)
{
	// Set the coordinates
	x = otherB.x + plusX;
	y = otherB.y + plusY;

	// If body type wasn't included in params, set it to the value of
	if (bodyType == -1)		// the otherB
		typeOfBodyPart = otherB.typeOfBodyPart;
	else
		typeOfBodyPart = bodyType;
	// set the same direction to this part
	direction = otherB.direction;
}


BodyPart::~BodyPart()
{
}

void BodyPart::setBodyTypeAndDirection(int newD, int newBT, int currentPart_or_HeadD)
{
	// If it's a head before me while I am not a head
	if (newBT == BODYPART_HEAD && typeOfBodyPart != BODYPART_HEAD)
	{

		// Then if my direction is not equal to the direction that the head had before moving further
		if (direction != currentPart_or_HeadD || typeOfBodyPart != BODYPART_STRAIGHT) // bolo tu newD
		{

			// Then if the head has the same direction as it had before
			if (currentPart_or_HeadD == newD)
				typeOfBodyPart = BODYPART_STRAIGHT;		// Make my bodytype straight
			//but, if the head has a different direction than it had before
			else
			{

				// Based on where the head is currently heading change my bodyType
				switch (currentPart_or_HeadD)
				{
				// *********************************************************** Head goes left
				case DIRECTION_LEFT_90_DEG:
					if (newD == DIRECTION_DOWN_180_DEG)				// Head went DOWN  before
						typeOfBodyPart = BODYPART_CURVED_RIGHT;
					else											// Head went UP	   before
						typeOfBodyPart = BODYPART_CURVED_LEFT;
					break;
				// ********************************************************** Head goes right
				case DIRECTION_RIGHT_270_DEG:
					if (newD == DIRECTION_DOWN_180_DEG)				// Head went DOWN  before
						typeOfBodyPart = BODYPART_CURVED_LEFT;
					else											// Head went UP	   before
						typeOfBodyPart = BODYPART_CURVED_RIGHT;
					break;
				// ************************************************************* Head goes up
				case DIRECTION_UP_0_DEG:
					if (newD == DIRECTION_LEFT_90_DEG)				// Head went LEFT  before
						typeOfBodyPart = BODYPART_CURVED_RIGHT;
					else											// Head went RIGHT before
						typeOfBodyPart = BODYPART_CURVED_LEFT;
					break;
				// *********************************************************** Head goes down
				case DIRECTION_DOWN_180_DEG:
					if (newD == DIRECTION_LEFT_90_DEG)				// Head went LEFT  before
						typeOfBodyPart = DIRECTION_LEFT_90_DEG;
					else											// Head went RIGHT before
						typeOfBodyPart = DIRECTION_RIGHT_270_DEG;
					break;
				}
			}

			// Set the direction to the new one
			direction = newD;
		}
		/* else... if my direction is the same as the head direction before me, there is no point in
		 modifying my direction, because there is no chance that if this condition would be true, my
		 bodypart wan't STRAIGHT. That means - if the condition is true, my type of body is already
		 STRAIGHT!  And that I'm supposed to be :). Don't have to modify it!! */
	}
	// If it isn't head before me or I am the head
	else
	{
		// Then if I am a tail
		if (typeOfBodyPart == BODYPART_TAIL)
			// change my direction to the direction of a body part before me
			direction = newD;

		// but if I'm not a tail and also not a head => I am a normal body part and before me 
		// is another normal body part
		else if (newBT != BODYPART_HEAD)
		{
			// give me its old body type and direction
			typeOfBodyPart = newBT;
			direction = newD;
		}
	}
}

void BodyPart::moveForward(int newDirection, int newBodyType, int currentHeadDir, 
							const int xMax, const int xMin,
							const int yMax, const int yMin)
{
	if (typeOfBodyPart != BODYPART_TAIL)
		setBodyTypeAndDirection(newDirection, newBodyType, currentHeadDir);
	
	switch (direction)
	{
	case DIRECTION_UP_0_DEG:
		moveForwardUP(yMax, yMin);
		break;

	case DIRECTION_LEFT_90_DEG:
		moveForwardLEFT(xMax, xMin);
		break;

	case DIRECTION_DOWN_180_DEG:
		moveForwardDOWN(yMax, yMin);
		break;

	case DIRECTION_RIGHT_270_DEG:
		moveForwardRIGHT(xMax, xMin);
		break;
	}	

	if (typeOfBodyPart == BODYPART_TAIL)
		setBodyTypeAndDirection(newDirection, newBodyType, currentHeadDir);
}


void BodyPart::moveForwardUP(const int yMax, const int yMin)
{
	int hY = y - 10;
	if (hY < yMax && hY > yMin)
		y = hY;
}

void BodyPart::moveForwardDOWN(const int yMax, const int yMin)
{
	int hY = y + 10;
	if (hY < yMax && hY > yMin)
		y = hY;
}

void BodyPart::moveForwardRIGHT(const int xMax, const int xMin)
{
	int hX = x + 10;
	if (hX < xMax && hX > xMin)
		x = hX;
}

void BodyPart::moveForwardLEFT(const int xMax, const int xMin)
{
	int hX = x - 10;
	if (hX < xMax && hX > xMin)
		x = hX;
}

void BodyPart::turnLeft()
{
	switch (direction)
	{
	case DIRECTION_UP_0_DEG:
		direction = DIRECTION_LEFT_90_DEG;
		break;
	case DIRECTION_LEFT_90_DEG:
		direction = DIRECTION_DOWN_180_DEG;
		break;
	case DIRECTION_DOWN_180_DEG:
		direction = DIRECTION_RIGHT_270_DEG;
		break;
	case DIRECTION_RIGHT_270_DEG:
		direction = DIRECTION_UP_0_DEG;
		break;
	default:
		direction = DIRECTION_UP_0_DEG;
	}
}

void BodyPart::turnRight()
{
	switch (direction)
	{
	case DIRECTION_UP_0_DEG:
		direction = DIRECTION_RIGHT_270_DEG;
		break;
	case DIRECTION_LEFT_90_DEG:
		direction = DIRECTION_UP_0_DEG;
		break;
	case DIRECTION_DOWN_180_DEG:
		direction = DIRECTION_LEFT_90_DEG;
		break;
	case DIRECTION_RIGHT_270_DEG:
		direction = DIRECTION_DOWN_180_DEG;
		break;
	default:
		direction = DIRECTION_UP_0_DEG;
	}
}

int BodyPart::getDirection_Angle()
{
	return direction;
}

int BodyPart::getTypeOfBodyPart()
{
	return typeOfBodyPart;
}

