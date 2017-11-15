#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "j1Module.h"
#include "Entity.h"
#include "j1Map.h"
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

	Entity* CreateEntity(ObjectLayer object);
	void DeleteEntity();

public:

	p2List<Entity*> entities;
};

#endif