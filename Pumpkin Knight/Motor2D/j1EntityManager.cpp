#include "j1EntityManager.h"
#include "Entity.h"
#include "Wolf.h"
#include "j1Map.h"

#define SPAWN_MARGIN 100

j1EntityManager::j1EntityManager()
{
	name.create("entities");
}

// Destructor
j1EntityManager::~j1EntityManager()
{
}

bool j1EntityManager::Start()
{
	LOG("loading entities");
	return true;
}

bool j1EntityManager::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENTITY_TYPES::NO_TYPE)
		{
			if (queue[i].y * SCREEN_SIZE > App->render->camera.y - SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", queue[i].y* SCREEN_SIZE);
				SpawnEnemy(queue[i]);
				queue[i].type = ENTITY_TYPES::NO_TYPE;

			}
		}
	}

	return true;
}

// Called before render is available
bool j1EntityManager::Update(float dt)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			entities[i]->Draw(sprites);
		}
	}
	return true;
}

bool j1EntityManager::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			if (entities[i]->pos.y * SCREEN_SIZE < -500 || entities[i]->pos.y * SCREEN_SIZE > 1000 || entities[i]->pos.x * SCREEN_SIZE < -500 || entities[i]->pos.x * SCREEN_SIZE > 1300)
			{
				LOG("DeSpawning enemy at %d", entities[i]->pos.y * SCREEN_SIZE);
				delete entities[i];
				entities[i] = nullptr;
			}
		}
	}

	return true;
}

// Called before quitting
bool j1EntityManager::CleanUp()
{
	LOG("Freeing all enemies");

	App->tex->UnLoad(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
	}

	return true;
}

bool j1EntityManager::AddEnemy(ENTITY_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENTITY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;

			ret = true;
			break;
		}
	}

	return ret;
}


void j1EntityManager::SpawnEnemy(const EntityInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; entities[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENTITY_TYPES::WOLF:
			entities[i] = new Wolf(info.x, info.y);
			break;

		}
	}
}

void j1EntityManager::OnCollision(Collider* c1, Collider* c2)
{

}

void j1EntityManager::EraseEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENTITY_TYPES::NO_TYPE)
		{
			queue[i].type = ENTITY_TYPES::NO_TYPE;
		}
	}
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
	}
}
