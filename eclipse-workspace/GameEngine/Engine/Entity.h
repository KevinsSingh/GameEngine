#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>

#define MOVING		0x31
#define IDLE		0x32

#define UP			0x33
#define DOWN		0x34
#define LEFT		0x35
#define RIGHT		0x36


class Entity
{
public:
	Entity(void);

	int GetInstanceID();
	void SetSprite( sf::Sprite& sprite);
	void SetImage( sf::Texture& image);
	virtual sf::Rect<float> getRect();
	virtual void SetPosition(sf::Vector2f pos);
	virtual void SetNextPosition();

	virtual sf::Vector2f getNextPosition() = 0;
	virtual void SetSpritePosition(void) = 0;
	virtual Entity* MakeCopy() = 0;

	virtual void SetState( int state);

	//Get rectangle of next Position.
	virtual sf::Rect<float> getNextRect();

	sf::Sprite& GetSprite();
	const sf::Texture* GetImage();
	int GetState();

	virtual int Update(sf::Event& keyEvent);

	virtual ~Entity(void);

	//Variables holding the Sprite and image.
	sf::Sprite cSprite;
	sf::Texture cTexture;

	static int InstanceCounter;

protected:

	//Variable to Identify instance of the object
	int instanceID;

	//Current state of character: Moving or Idle.
	int cState;

	//Direction of movement by character.
	sf::Vector2i direction;

	//Current Direction of the Character: ^, v, >, <
	int spriteDirection;

	//Speed of object. measured in pixels
	int speed;

	//Variable to keep count of the current frame index
	int frameCount;	

	//Variable to keep count of the current position index
	int positionCount;

	//Threshold which determines when to increment framecount. This regulates the frameRate.
	int frameDelay;

	//index of current frame based on direction and state.
	sf::Vector2i currentFrame;

	//Absolute position of the sprite.
	sf::Vector2f position;

	//Next calculated position.
	sf::Vector2f nextPosition;

	//Threshold to determine when to increment position by 'speed' pixels. 
	int positionDelay;

	//These variables characterize the image which is stored in the Sprite.
	int imageWidth;
	int imageHeight; 	
	sf::Vector2i frameRange; 
	sf::Vector2i subRectDIM;

	//Flag to determine if Sprite frame in X direction needs to be reflected.
	bool needFlipXFrame;
};
