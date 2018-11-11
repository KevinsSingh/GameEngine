/*
 * LevelManager.cpp
 *
 *  Created on: 2018-06-09
 *      Author: kevin
 */

#include "LevelManager.h"

LevelManager::LevelManager()
{
	this->currentLevel = NULL;
	this->levelArchive = std::map<int, Level*>();
	this->mediator = NULL;
	this->camera = NULL;
	this->event = -1;
	needUpdateObjectList = true;
}

LevelManager::LevelManager(std::map<int, Level*> levelArchive, Camera* camera, EngineMediator* mediator,  int levelID)
{
	this->levelArchive = levelArchive;
	this->currentLevel = this->levelArchive[levelID];
	this->mediator = mediator;
	this->camera = camera;
	this->event = -1;
	needUpdateObjectList = true;
}

//Adds a new level to the Archive.
int LevelManager::AddLevel(Level* level, int levelID)
{
	this->levelArchive[levelID] = level;
	return levelID;
}

//Removes the specified Level from the Archive.
int LevelManager::RemoveLevel(int levelID)
{
	std::map<int, Level*>::iterator iter;

	iter = this->levelArchive.find(levelID);
	this->levelArchive.erase(iter->first);

	return levelID;
}

//Updates the level based on Input from the Mediator.
void LevelManager::updateCurrentLevel()
{
	int event = 0;

	event = this->mediator->CheckObjectEvent();

	if (event == EVENT_OBJECT_LIST_UPDATED)
	{
		//Load new level
		needUpdateObjectList = false;
	}

}

//Set current level
void LevelManager::SetCurrentLevel(int levelID)
{
	this->currentLevel = this->levelArchive[levelID];
}

//Returns pointer to current level.
Level* LevelManager::GetCurrentLevel()
{
	return this->currentLevel;
}

//Returns flag to indicate whether the object list has been updated.
bool LevelManager::NeedToUpdateObjectList()
{
	return needUpdateObjectList;
}

//Returns a list of Entities that the Object manager needs to load.
std::vector <EntityRecord>* LevelManager::getCurrentObjectList()
{
	return this->currentLevel->GetEntityList();
}

int LevelManager::GetEvent()
{
	return this->event;
}

void LevelManager::Render(sf::RenderWindow* window)
{
	this->currentLevel->Draw(window);
}

LevelManager::~LevelManager()
{
}


