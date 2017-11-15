#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "j1Module.h"
#include "Entity.h"
#include "j1Map.h"
#include "p2List.h"
#include "p2Point.h"

#define MAX_ENEMIES 1000

enum ENTITY_TYPES
{
	NO_TYPE,
	BAT,
	WOLF,
};

class Entity;

struct EntityInfo
{
	ENTITY_TYPES type = ENTITY_TYPES::NO_TYPE;
	int x, y;
};

class j1EntityManager : public j1Module
{
public:

	j1EntityManager();
	~j1EntityManager();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();


	Entity* CreateEntity(ObjectLayer* object, uint id, uint i);


	void SpawnEntity(const EntityInfo& info);

	void DeleteEntity();

public:
	EntityInfo queue[MAX_ENEMIES];
	p2List<Entity*> entities;

	SDL_Texture* sprites;
};

#endif