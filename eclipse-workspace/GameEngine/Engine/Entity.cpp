#include "Entity.h"

int Entity::InstanceCounter = 0;

Entity::Entity(void)
{

	//Variable to Identify instance of the object
	instanceID = InstanceCounter++;

	//Current state of character: Moving or Idle.
	cState = 0;

	//Direction of movement made by Character
	direction.x = 0;
	direction.y = 0;

	//Current Direction of the Character: >, <, ^, v
	spriteDirection = DOWN;

	//Speed of object. measured in pixels
	speed = 0;

	//Variable to keep count of the current frame index
	frameCount = 0;

	//Variable to keep count of the current position index
	positionCount = 0;

	//Threshold which determines when to increment framecount. This regulates the frameRate.
	frameDelay = 0;

	//index of current frame based on direction and state.
	currentFrame = sf::Vector2i();

	//Absolute position of the sprite.
	position = sf::Vector2f();

	//Threshold to determine when to increment position by 'speed' pixels.
	positionDelay = 0;

	//Variables holding the Sprite and a pointer to the current map
	cSprite = sf::Sprite();
	cTexture = sf::Texture();

	//These variables characterize the image which is stored in the Sprite.
	imageWidth = 0;
	imageHeight = 0;
	frameRange = sf::Vector2i();
	subRectDIM = sf::Vector2i();

	needFlipXFrame = false;
}

int Entity::GetInstanceID()
{
	return this->instanceID;
}

int Entity::Update(sf::Event& keyEvent)
{
	return 0;
}

void Entity::SetSprite( sf::Sprite& sprite)
{
	cSprite = sprite; 
}

void Entity::SetImage( sf::Texture& image)
{
	cTexture = image;
	cSprite.setTexture(image);
}

void Entity::SetPosition(sf::Vector2f pos)
{
	cSprite.setPosition(pos);
	position = pos;
}

void Entity::SetNextPosition()
{

}

void Entity::SetState( int state)
{
	cState = state;
}

sf::Sprite& Entity::GetSprite()
{
	return cSprite;
}

const sf::Texture* Entity::GetImage()
{
	return cSprite.getTexture();
}

int Entity::GetState()
{
	return cState;
}

sf::Rect<float> Entity::getRect()
{
	sf::Rect<float> spriteRect;

	spriteRect.top = this->position.y;
	spriteRect.left = this->position.x;

	spriteRect.width = this->subRectDIM.x;
	spriteRect.height = this->subRectDIM.y;

	return spriteRect;
}

sf::Rect<float> Entity::getNextRect()
{
	sf::Rect<float> spriteRect;

	spriteRect.top = this->nextPosition.y;
	spriteRect.left = this->nextPosition.x;

	spriteRect.width = this->subRectDIM.x;
	spriteRect.height = this->subRectDIM.y;

	return spriteRect;
}
Entity::~Entity(void)
{
}
