/*
 * ObjectManager.cpp
 *
 *  Created on: 2018-06-09
 *      Author: kevin
 */

#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	this->gameObjectArchive = map<int, Entity*>();
	this->currentObjectList = vector<Entity*>();
	this->currentRecordList = NULL;
	this->mediator = NULL;
	this->event = -1;
}

ObjectManager::ObjectManager(std::map <int, Entity*> objectArchive, EngineMediator* engineMediator)
{
	this->mediator = engineMediator;
	this->gameObjectArchive = objectArchive;
	this->currentObjectList = std::vector<Entity*>();
	this->currentRecordList = NULL;
	this->event = -1;
}

ObjectManager::~ObjectManager()
{
	//Free the memory used on the heap by each object and Clear the current object list.
	for (vector<Entity*>::iterator object = this->currentObjectList.begin(); object != currentObjectList.end(); object++)
	{
		Entity* entity = (*object);

		if (entity != NULL)
			delete entity;
	}

	this->currentObjectList.clear();
}

bool ObjectManager::CheckTileCollision( sf::Rect<float> rect)
{
	sf::Vector2f vertex;

	//Check top left corner
	vertex.x = rect.left;
	vertex.y = rect.top;

	if (this->mediator->checkSolidTile(vertex))
		return true;

	//Check top right corner
	vertex.x = rect.left + rect.width;

	if(this->mediator->checkSolidTile(vertex))
		return true;

	//Check bottom left corner
	vertex.x = rect.left;
	vertex.y = rect.top + rect.height;

	if(this->mediator->checkSolidTile(vertex))
		return true;

	//Check bottom right corner
	vertex.x = rect.left + rect.width;

	if(this->mediator->checkSolidTile(vertex))
		return true;

	return false;
}

int ObjectManager::Update(sf::Event event)
{
	bool needUpdate = false;

	needUpdate = this->mediator->NeedToUpdateObjectList();

	if (needUpdate)
	{
		//Free the memory used on the heap by each object and Clear the current object list.
		{
			for (vector<Entity*>::iterator object = this->currentObjectList.begin(); object != currentObjectList.end(); object++)
			{
				Entity* entity = (*object);

				if (entity != NULL)
					delete entity;
			}

			this->currentObjectList.clear();
		}

		//Get the latest Record list from the Mediator.
		this->currentRecordList = this->mediator->GetCurrentRecordList();

		vector<EntityRecord>::iterator record;

		for (record = this->currentRecordList->begin(); record != this->currentRecordList->end(); record++ )
		{
			Entity* entity;
			entity = this->gameObjectArchive.at(record->objectID)->MakeCopy();
			entity->SetPosition(record->position);

			if (entity != NULL)
				this->currentObjectList.push_back(entity);
		}

		this->event = EVENT_OBJECT_LIST_UPDATED;
	}

	for (vector<Entity*>::iterator object = this->currentObjectList.begin(); object != this->currentObjectList.end(); object++)
	{
		sf::Vector2f objectPosition;
		Entity* entity = (*object);
		bool isSolid = false;

		entity->Update(event);

		objectPosition = entity->getNextPosition();

		isSolid = this->CheckTileCollision(entity->getNextRect());

		if (!isSolid)
		{
			bool collision = false;

			//Check for collision with other objects.
			for (vector<Entity*>::iterator otherObject = this->currentObjectList.begin(); otherObject != this->currentObjectList.end(); otherObject++)
			{
				Entity* otherEntity = (*otherObject);

				if (entity->GetInstanceID() != otherEntity->GetInstanceID())
				{
					//Check for intersection between rectangles
					collision = entity->getNextRect().intersects(otherEntity->getRect());
				}
			}

			if (!collision)
			{
				entity->SetSpritePosition();
			}
		}
	}

	return 0;
}

int ObjectManager::GetEvent()
{
	return this->event;
}

void ObjectManager::Render(sf::RenderWindow* window)
{
	vector<Entity*>::iterator object;

	for (object = this->currentObjectList.begin(); object!= this->currentObjectList.end(); object++)
	{
		window->draw((*object)->GetSprite());
	}
}

sf::Vector2f ObjectManager::GetPositionOf(int id)
{
	return this->currentObjectList[id]->GetSprite().getPosition();
}

sf::Vector2f ObjectManager::GetPositionOfMainChar()
{
	Entity* mainChar;
	mainChar = this->currentObjectList.at(0);

	return mainChar->GetSprite().getPosition();
}
