#pragma once

// Represents type of body part
enum typeOfBodyParts
{
	BODYPART_HEAD,
	BODYPART_STRAIGHT,
	BODYPART_CURVED_LEFT,
	BODYPART_CURVED_RIGHT,
	BODYPART_TAIL,
	BODYPART_TOTAL
};

// Represents a direction / angle of the body part
enum direction_angle
{
	DIRECTION_UP_0_DEG = 0,
	DIRECTION_LEFT_90_DEG = 90,
	DIRECTION_DOWN_180_DEG = 180,
	DIRECTION_RIGHT_270_DEG = 270
};

class BodyPart
{
private:
	// Body part's coordinates
	int x, y;
	// What type of bodypart it is
	int typeOfBodyPart;
	// Current direction of the body part
	int direction;
	
	void setBodyTypeAndDirection(int newDirection, int newBodyType,
		int currentHeadDirection);

public:
	BodyPart(int x, int y, int bodyType = BODYPART_STRAIGHT, 
		int direction = DIRECTION_UP_0_DEG);

	/* A half copy constructor.
	* assigns a value to x and y regard to the values in otherBodyPart.
	* sets the bodyType to the bodyType of otherBodyPart if not included.
	* sets the direction the same as the otherBodyPart has.*/
	BodyPart(BodyPart &otherBodyPart, int plusX = 0, int plusY = 0,
		int bodyType = -1);
	~BodyPart();
	

	/* Moves a body part forward regard to its direction and changes its
	   bodyType regard to its current body type
	 * This function modifies values of the current bodyPart with the
	   parameters given.													*/	 
	void moveForward(int newDirection, int newBodyType, int currentHeadDir,
		const int xMax, const int xMin, 
		const int yMax, const int yMin);

	// Moves the part in UP direction
	void moveForwardUP(const int yMax, const int yMin);

	// Moves the part in DOWN direction
	void moveForwardDOWN(const int yMax, const int yMin);

	// Moves the part in RIGHT direction
	void moveForwardRIGHT(const int xMax, const int xMin);

	// Moves the part in LEFT direction
	void moveForwardLEFT(const int xMax, const int xMin);

	// Turns the part to the left depending on its current direction
	void turnLeft();

	// Turns the part to the right depending on its current direction
	void turnRight();

	// Returns the direction/angle the part is heading
	int getDirection_Angle();

	// Returns the type of body
	int getTypeOfBodyPart();

	// Returns the x coordinate of this body part
	int getX_Location() { return x; }

	// Returns the y coordinate of this body part
	int getY_Location() { return y; }



	// for tests
	

	void setB(int newD, int newBT, int currentPart_or_HeadD)
	{
		// If it's a head before me while I am not a head
		if (newBT == BODYPART_HEAD && typeOfBodyPart != BODYPART_HEAD)
		{	// Then
			// If my direction is not equal to the direction that the head had before moving further
			if (direction != newD)
			{	// Than
				// if the head has the same direction as it had before
				if (currentPart_or_HeadD == newD)
					typeOfBodyPart = BODYPART_STRAIGHT;		// Make my bodytype straight
				// but, if the head has a different direction than it had before
				else
				{
					// Based on where the head is currently heading change my bodyType
					switch (currentPart_or_HeadD)
					{
					case DIRECTION_LEFT_90_DEG:				//##########<LEFT>##########
						if (newD == DIRECTION_DOWN_180_DEG)	//==========-DOWN-=========#
							typeOfBodyPart = BODYPART_CURVED_RIGHT;//---curve_right<---#
						else								//===========-UP-==========#
							typeOfBodyPart = BODYPART_CURVED_LEFT;//--->curve_left<----#
						break;								//##########################
					case DIRECTION_RIGHT_270_DEG:			//##########<RIGHT>##########
						if (newD == DIRECTION_DOWN_180_DEG)
							typeOfBodyPart = BODYPART_CURVED_LEFT;
						else
							typeOfBodyPart = BODYPART_CURVED_RIGHT;
						break;
					case DIRECTION_UP_0_DEG:				//############<UP>###########
						if (newD == DIRECTION_LEFT_90_DEG)
							typeOfBodyPart = BODYPART_CURVED_RIGHT;
						else
							typeOfBodyPart = BODYPART_CURVED_LEFT;
						break;
					case DIRECTION_DOWN_180_DEG:			//############<DOWN>#########
						if (newD == DIRECTION_LEFT_90_DEG)
							typeOfBodyPart = DIRECTION_LEFT_90_DEG;
						else
							typeOfBodyPart = DIRECTION_RIGHT_270_DEG;
						break;
					}
				}
				direction = newD;
			}
			// else... if my direction is the same as the head direction before me, there is no point in 
			// modifying my direction, because there is no chance that if this condition would be true, my bodypart 
			// wan't STRAIGHT. That means - if the condition is true, my type of body is already STRAIGHT!
			// And that I'm supposed to be :). Don't have to modify it!!
		}
		// If it isn't head before me or I am the head
		else
		{	// Than
			// if I am a tail
			if (typeOfBodyPart == BODYPART_TAIL)
				// change my direction to the direction of a body part before me
				direction = newBT;
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
};