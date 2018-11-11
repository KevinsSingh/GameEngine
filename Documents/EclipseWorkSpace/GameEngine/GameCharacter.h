/*
 * GameCharacter.h
 *
 *  Created on: 2018-09-22
 *      Author: kevin
 */

#ifndef GAMECHARACTER_H_
#define GAMECHARACTER_H_

#include "Engine/Character.h"

class GameCharacter: public Character {

public:
	GameCharacter();
	GameCharacter(sf::Vector2i charDim, sf::Texture& currentSprite);

	virtual int Update(sf::Event& keyEvent);
	virtual Entity* MakeCopy();

	virtual ~GameCharacter();

private:
	//Sets private variable 'currentFrame'
	virtual void SetCurrentFrameIndex(int state, int dir);

	//Distance traveled by game character, Simple AI. (Number of frames before direction changes)
	int distance;
};

#endif /* GAMECHARACTER_H_ */
