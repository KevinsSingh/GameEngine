/*
 * EngineMediator.cpp
 *
 *  Created on: 2018-06-09
 *      Author: kevin
 */

#include "EngineMediator.h"

EngineMediator::EngineMediator()
{
	this->levelManager = NULL;
	this->objectManager = NULL;
	this->camera = NULL;
	this->audioManager = NULL;

}

void EngineMediator::Init(LevelManager* levelManager, ObjectManager* objectManager, Camera* camera, AudioManager* audioManager)
{
	this->levelManager = levelManager;
	this->objectManager = objectManager;
	this->camera = camera;
	this->audioManager = audioManager;
}

EngineMediator::~EngineMediator() {
	// TODO Auto-generated destructor stub
}

int EngineMediator::CheckObjectEvent()
{
	int event = 0;

	event = this->objectManager->GetEvent();

	return event;
}

int EngineMediator::CheckLevelEvent()
{
	int event = 0;

	event = this->levelManager->GetEvent();

	return event;
}

bool EngineMediator::checkSolidTile(sf::Vector2f tile)
{
	Level* level = NULL;
	level = this->levelManager->GetCurrentLevel();

	return level->IsSolidTile(tile.x, tile.y);
}

bool EngineMediator::NeedToUpdateObjectList()
{
	return this->levelManager->NeedToUpdateObjectList();
}

std::vector <EntityRecord>* EngineMediator::GetCurrentRecordList()
{
	return this->levelManager->getCurrentObjectList();
}

sf::Vector2f EngineMediator::GetPositionOf(int id)
{
	return this->objectManager->GetPositionOf(id);
}

sf::Vector2f EngineMediator::GetPositionOfMainChar()
{
	return this->objectManager->GetPositionOfMainChar();
}

