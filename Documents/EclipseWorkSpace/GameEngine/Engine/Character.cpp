/*
 * Character.cpp
 *
 *  Created on: 2018-09-20
 *      Author: kevin
 */

#include "Character.h"

Character::Character()
{
}

Character::Character(sf::Vector2i charDim, sf::Texture& spriteImage):DynamicEntity()
{
	sf::Vector2u size;

	this->cTexture = spriteImage;
	this->cSprite.setTexture(spriteImage);
	size = spriteImage.getSize();

	frameRange.x = charDim.x;
	frameRange.y = charDim.y;

	subRectDIM.x = (int)size.x/charDim.x;
	subRectDIM.y = (int)size.y/charDim.y;

}

Character::~Character() {
	// TODO Auto-generated destructor stub
}

int Character::Update(sf::Event &keyEvent)
{
	//To Be implemented by derived classes
	return 0;
}

Entity* Character::MakeCopy()
{
	//To Be implemented by derived classes
	return NULL;
}

void Character::SetCurrentFrameIndex(int state, int dir)
{
	//To Be implemented by derived classes
}

void Character::SetCurrentSubRect(void)
{
	sf::IntRect subRect;

	if (currentFrame.y < frameRange.y && currentFrame.x < frameRange.x)
	{
		subRect.top = subRectDIM.y * currentFrame.y;
		subRect.left = subRectDIM.x * currentFrame.x;
		subRect.width = subRectDIM.x;
		subRect.height = subRectDIM.y;

		cSprite.setTextureRect( subRect );

		if (spriteDirection == LEFT && needFlipXFrame)
		{
			cSprite.setOrigin(cSprite.getLocalBounds().width, 0);
			cSprite.setScale(-1,1);
		}
		else
		{
			cSprite.setOrigin(0, 0);
			cSprite.setScale(1,1);
		}
	}
}

void Character::SetNextPosition()
{
	this->position = nextPosition;
}

void Character::SetSpritePosition(void)
{
	this->SetNextPosition();
	cSprite.setPosition( position );
}

sf::Vector2f Character::getNextPosition()
{
	int sign_x = 0;
	int sign_y = 0;

	nextPosition = position;

	if (direction.x == RIGHT)
		sign_x = 1;
	else if (direction.x == LEFT)
		sign_x = -1;


	if (direction.y == DOWN)
		sign_y = 1;
	else if (direction.y == UP)
		sign_y= -1;


	if (cState == MOVING)
	{
		//if (positionCount == positionDelay)
		//{
			nextPosition.x = position.x + (sign_x * speed);
			nextPosition.y = position.y + (sign_y * speed);

			//positionCount = 0;
		//}

		//positionCount++;
	}

	return nextPosition;
}
