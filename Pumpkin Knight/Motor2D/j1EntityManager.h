#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "j1Module.h"
#include "Entity.h"
#include "p2List.h"
#include "p2Point.h"


class j1EntityManager : public j1Module
{
public:

	j1EntityManager();
	~j1EntityManager();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool Update(float dt);
	bool PostUpdate(float dt);
	bool CleanUp();

	//Entity* CreateEntity(EntityType etype, ColType ctype, fPoint pos);
	void DeleteEntity();

private:

	p2List<Entity*> entities;
};

#endif