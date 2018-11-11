/*
 * GameCharacter.cpp
 *
 *  Created on: 2018-09-22
 *      Author: kevin
 */

#include "GameCharacter.h"

GameCharacter::GameCharacter() {
	// TODO Auto-generated constructor stub
	distance = 5;
	speed = 3;
}

//Constructor with character grid dimensions of sprite sheet.
GameCharacter::GameCharacter(sf::Vector2i charDim, sf::Texture& currentSprite):Character( charDim, currentSprite)
{
	distance = 5;
	speed = 3;
	frameDelay = 1;
}

int GameCharacter::Update(sf::Event& keyEvent)
{
	int random = 0;

	if ( distance == 5)
	{
		//initialize random seed
		srand(time(NULL));

		//Generate number between 1 and 4;
		random = rand() % 4 + 1;

		//Set Random Direction
		this->spriteDirection = 0x32 + random;

		switch (this->spriteDirection)
		{
			case UP:
				direction.x = IDLE;
				direction.y = UP;
				break;
			case DOWN:
				direction.x = IDLE;
				direction.y = DOWN;
				break;
			case LEFT:
				direction.x = LEFT;
				direction.y = IDLE;
				break;
			case RIGHT:
				direction.x = RIGHT;
				direction.y = IDLE;
				break;
			default:
				break;
		}

		//Generate random state;
		this->cState = (rand() % 2 + 1) + 0x30;

		distance = 0;
	}

	distance++;

	SetCurrentFrameIndex( cState, spriteDirection);

	SetCurrentSubRect();

	return 0;
}

Entity* GameCharacter::MakeCopy()
{
	Entity* chara = new GameCharacter(this->frameRange, this->cTexture);
	chara->cTexture = this->cTexture;
	chara->cSprite = this->cSprite;

	return chara;

}

void GameCharacter::SetCurrentFrameIndex(int state, int dir)
{
	//To be able to correctly set the index prior knowledge of the image must be known.
	switch (dir)
	{
		case UP:
			currentFrame.y = 0;
			break;
		case DOWN:
			currentFrame.y = 2;
			break;
		case LEFT:
			currentFrame.y = 3;
			break;
		case RIGHT:
			currentFrame.y = 1;
			break;
	}

	if (state == IDLE)
	{
		currentFrame.x = 1;
	}

	if (state == MOVING)
	{
		if( frameCount == frameDelay)
		{
			currentFrame.x++;

			if ( currentFrame.x == frameRange.x)
				currentFrame.x = 0;

			frameCount = 0;
		}
		else
			frameCount++;
	}
}


GameCharacter::~GameCharacter() {
	// TODO Auto-generated destructor stub
}

