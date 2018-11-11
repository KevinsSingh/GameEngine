#pragma once
#include "Engine/Character.h"

class MainCharacter :	public Character
{
public:
	MainCharacter(void);

	//Constructor with character grid dimensions of sprite sheet.
	MainCharacter(sf::Vector2i charDim, sf::Texture& currentSprite);

	virtual int Update(sf::Event& keyEvent);
	virtual Entity* MakeCopy();

	virtual ~MainCharacter(void);

protected:
	bool up_key;
	bool down_key;
	bool left_key;
	bool right_key;

private:
	//Sets private variable 'currentFrame'
	virtual void SetCurrentFrameIndex(int state, int dir);

};

