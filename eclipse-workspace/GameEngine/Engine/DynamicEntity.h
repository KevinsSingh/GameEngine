#pragma once

#include "Entity.h"

class DynamicEntity : public Entity
{
public:
	DynamicEntity (void);

	virtual int Update(sf::Event& keyEvent);

	//Get Next Position
	virtual sf::Vector2f getNextPosition();

	//Sets the sprites position
	virtual void SetSpritePosition(void);

	virtual ~DynamicEntity (void);

protected:

	//Sets private variable 'currentFrame' 
	virtual void SetCurrentFrameIndex(int state, int dir);

	//Sets the subrect of the sprite based on the currentFrame index.
	virtual void SetCurrentSubRect(void);

	//Sets Current position of the Character
	virtual void SetPosition(int state, sf::Vector2i dir);

};

