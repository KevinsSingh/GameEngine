/*
 * ObjectManager.h
 *
 *  Created on: 2018-06-09
 *      Author: kevin
 */

#ifndef ENGINE_OBJECTMANAGER_H_
#define ENGINE_OBJECTMANAGER_H_

#include "EngineMediator.h"
#include "Level.h"
#include "DynamicEntity.h"
#include "StaticEntity.h"
#include <map>

class EngineMediator;

class ObjectManager {

private:
	EngineMediator *mediator;
	std::map <int, Entity*> gameObjectArchive;
	std::vector <Entity*> currentObjectList;
	std::vector <EntityRecord>* currentRecordList;
	int event;

	//Helper Functions
	bool CheckTileCollision( sf::Rect<float> rect);

public:
	ObjectManager();
	ObjectManager(std::map <int, Entity*> objectArchive, EngineMediator* engineMediator);
	int AddToArchive(Entity* obj);
	int Update(sf::Event event);
	void Render(sf::RenderWindow *window);
	sf::Vector2f GetPositionOf(int id);
	sf::Vector2f GetPositionOfMainChar();
	int GetEvent();
	virtual ~ObjectManager();
};

#endif /* ENGINE_OBJECTMANAGER_H_ */
