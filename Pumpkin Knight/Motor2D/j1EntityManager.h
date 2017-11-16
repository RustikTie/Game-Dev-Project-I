#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "j1Module.h"
#include "Entity.h"
#include "j1Map.h"
#include "p2List.h"
#include "p2Point.h"
#include "Bat.h"
#include "Wolf.h"

#define MAX_ENEMIES 1000
#define SCREEN_SIZE 1
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void EraseEnemies();

	void OnCollision(Collider* c1, Collider* c2);
	bool AddEnemy(ENTITY_TYPES type, int x, int y);
	void SpawnEnemy(const EntityInfo& info);

private:

	EntityInfo queue[MAX_ENEMIES];
	Entity* entities[MAX_ENEMIES];
	SDL_Texture* sprites;

};

#endif