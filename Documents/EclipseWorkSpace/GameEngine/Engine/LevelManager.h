/*
 * LevelManager.h
 *
 *  Created on: 2018-06-09
 *      Author: kevin
 */

#ifndef ENGINE_LEVELMANAGER_H_
#define ENGINE_LEVELMANAGER_H_

#include "EngineMediator.h"
#include "Level.h"
#include "Camera.h"
#include <map>

using namespace std;

class EngineMediator;
class Camera;

class LevelManager {

private:
	//Pointer to Mediator Object - Allows communication with other Managers.
	EngineMediator* mediator;

	//An archive of all the Levels loaded into the game.
	std::map <int, Level*> levelArchive;

	//Pointer to the current level.
	Level* currentLevel;

	//Pointer to the Camera object containing view of the current map.
	Camera* camera;

	//Event Indicator
	int event;

	//flag indicating whether to update the object list
	bool needUpdateObjectList;

public:
	//Default Constructor
	LevelManager();
	//Constructor with predefined Level Archive for the Game.
	LevelManager(map<int, Level*> levelArchive, Camera* camera, EngineMediator* mediator, int levelID);
	//Adds a new level to the Archive.
	int AddLevel(Level* level, int levelID);
	//Removes the specified Level from the Archive.
	int RemoveLevel(int levelID);
	//Updates the level based on Input from the Mediator.
	void updateCurrentLevel();
	//Set current level
	void SetCurrentLevel(int levelID);
	//Returns pointer to current level.
	Level* GetCurrentLevel();
	//Returns flag to indicate whether the object list has been updated.
	bool NeedToUpdateObjectList();
	//Returns a list of Entities that the Object manager needs to load.
	std::vector <EntityRecord>* getCurrentObjectList();
	//Check for change in event.
	int GetEvent();
	//Render Current Level
	void Render(sf::RenderWindow *window);
	//Destructor.
	virtual ~LevelManager();
};

#endif /* ENGINE_LEVELMANAGER_H_ */
