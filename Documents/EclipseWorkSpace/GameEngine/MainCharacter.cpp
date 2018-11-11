#include "MainCharacter.h"


MainCharacter::MainCharacter(void): Character()
{
	up_key = 0;
	down_key = 0;
	left_key = 0;
	right_key = 0;

	this->needFlipXFrame = true;
}

//Constructor with character grid dimensions of sprite sheet.
MainCharacter::MainCharacter(sf::Vector2i charDim, sf::Texture& currentSprite):Character( charDim, currentSprite)
{
	up_key = 0;
	down_key = 0;
	left_key = 0;
	right_key = 0;

	this->needFlipXFrame = true;
}

MainCharacter::~MainCharacter()
{

}

int MainCharacter::Update(sf::Event& keyEvent)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			spriteDirection = LEFT;
			cState = MOVING;
			direction.x = LEFT;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			spriteDirection = RIGHT;
			cState = MOVING;
			direction.x = RIGHT;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			spriteDirection = UP;
			cState = MOVING;
			direction.y = UP;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			spriteDirection = DOWN;
			cState = MOVING;
			direction.y = DOWN;
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		direction.x = IDLE;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		direction.y = IDLE;

	if (direction.x != IDLE && direction.y == IDLE)
		spriteDirection = direction.x;

	if (direction.y != IDLE && direction.x == IDLE)
		spriteDirection = direction.y;

	if (direction.y == IDLE && direction.x == IDLE)
		cState = IDLE;

	//set current frame index based on state and direction
	SetCurrentFrameIndex( cState, spriteDirection);

	//Set sub rectangle for the Sprite.
	SetCurrentSubRect();

	//Set Position of the character.
	//SetPosition( cState, direction);

	//Set Sprite Position
	//SetSpritePosition();

	return 0;
}


void MainCharacter::SetCurrentFrameIndex(int state, int dir)
{
	//To be able to correctly set the index prior knowledge of the image must be known.
	switch (dir)
	{
		case UP:
			currentFrame.y = 2;
			break;
		case DOWN:
			currentFrame.y = 0;
			break;
		case LEFT:
			currentFrame.y = 4;
			break;
		case RIGHT:
			currentFrame.y = 4;
			break;
	}

	if (state == IDLE)
	{
		currentFrame.x = 3;
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

Entity* MainCharacter::MakeCopy()
{
	Entity* chara = new MainCharacter(this->frameRange, this->cTexture);
	chara->cTexture = this->cTexture;
	chara->cSprite = this->cSprite;

	return chara;
}
