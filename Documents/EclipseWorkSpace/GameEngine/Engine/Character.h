/*
 * Character.h
 *
 *  Created on: 2018-09-20
 *      Author: kevin
 */

#ifndef ENGINE_CHARACTER_H_
#define ENGINE_CHARACTER_H_

#include "DynamicEntity.h"

class Character: public DynamicEntity {
public:
	Character();

	//Constructor with character grid dimensions of sprite sheet.
	Character(sf::Vector2i charDim, sf::Texture& spriteImage);

	virtual int Update(sf::Event& keyEvent);
	virtual sf::Vector2f getNextPosition();
	virtual void SetSpritePosition(void);
	virtual Entity* MakeCopy();

	virtual ~Character();

protected:
	//Sets private variable 'currentFrame'
	virtual void SetCurrentFrameIndex(int state, int dir);

	//Sets the sub-rectangle of the sprite based on the currentFrame index.
	virtual void SetCurrentSubRect(void);

	//Set absolute position of sprite
	virtual void SetNextPosition();
};

#endif /* ENGINE_CHARACTER_H_ */
