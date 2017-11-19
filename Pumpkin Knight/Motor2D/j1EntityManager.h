#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "j1Module.h"
#include "Entity.h"
#include "j1Map.h"
#include "j1PLayer.h"
#include "p2List.h"
#include "p2Point.h"
#include "Bat.h"
#include "Wolf.h"

#define MAX_ENEMIES 1000
#define SCREEN_SIZE 1
#define SCREEN_WIDTH 6400
#define SCREEN_HEIGHT 460

enum ENTITY_TYPES
{
	NO_TYPE,
	BAT,
	WOLF,
	PLAYER,
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
	void EraseEnemies();

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&)const;

	void OnCollision(Collider* c1, Collider* c2, float counterforce);
	bool AddEnemy(ENTITY_TYPES type, int x, int y);
	void SpawnEntity(const EntityInfo& info);

	bool despawning = false;
	bool bat = false;
	bool wolf = false;
	bool player = false;

	EntityInfo queue[MAX_ENEMIES];
	Entity* entities[MAX_ENEMIES];
	pugi::xml_document config_file;
	EntityInfo playerInfo;
	//Player* player_entity;
	Entity* playerEntity;

private:

	//Entity* player;

};

#endif