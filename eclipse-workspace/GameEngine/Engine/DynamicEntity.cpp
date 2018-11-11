#include "DynamicEntity.h"


DynamicEntity ::DynamicEntity (void):Entity()
{
	currentFrame.x = 0;
	currentFrame.y = 0;

	frameDelay = 0;
	positionDelay = 0;
	frameCount = 0;
	positionCount = 0;
	speed = 5;

	position.x = 0;
	position.y = 0;

	spriteDirection = DOWN;
	cState = IDLE;
}

void DynamicEntity::SetCurrentFrameIndex(int state, int dir)
{
	//To be implemented by Child object
}

void DynamicEntity ::SetCurrentSubRect(void)
{
	//To be implemented by Child object
}

void DynamicEntity ::SetPosition(int state, sf::Vector2i dir)
{
	//To be implemented by Child object
}

void DynamicEntity ::SetSpritePosition(void)
{
	cSprite.setPosition( position.x, position.y);
}

sf::Vector2f DynamicEntity::getNextPosition()
{
	return this->position;
}

int DynamicEntity ::Update(sf::Event& keyEvent)
{
	return 0;
}

DynamicEntity ::~DynamicEntity (void)
{

}
