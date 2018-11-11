#pragma once
#include "Entity.h"

class StaticEntity :	public Entity
{

public:
	StaticEntity(void);

	void SetState(){ cState=IDLE; }

	int Update(void);

	virtual ~StaticEntity(void);	

protected:

};

