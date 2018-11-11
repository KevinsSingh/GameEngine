/*
 * EngineMediator.h
 *
 *  Created on: 2018-06-09
 *      Author: kevin
 */

#ifndef ENGINE_ENGINEMEDIATOR_H_
#define ENGINE_ENGINEMEDIATOR_H_

#include "LevelManager.h"
#include "ObjectManager.h"
#include "AudioManager.h"
#include "Camera.h"

#define EVENT_OBJECT_LIST_UPDATED	0x51

class LevelManager;
class ObjectManager;
class AudioManager;
class Camera;

class EngineMediator {

private:
	LevelManager* levelManager;
	ObjectManager* objectManager;
	Camera* camera;
	AudioManager* audioManager;

public:
	EngineMediator();
	void Init(LevelManager* levelManager, ObjectManager* objectManager, Camera* camera, AudioManager* audioManager);
	int CheckObjectEvent();
	int CheckLevelEvent();
	bool NeedToUpdateObjectList();

	bool checkSolidTile(sf::Vector2f tile);
	sf::Vector2f GetPositionOf(int id);
	sf::Vector2f GetPositionOfMainChar();
	std::vector <EntityRecord>* GetCurrentRecordList();

	virtual ~EngineMediator();
};

#endif /* ENGINE_ENGINEMEDIATOR_H_ */
