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
				SpawnEntity(queue[i]);
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
			entities[i]->MoveEnemy(dt);
			entities[i]->Draw(entities[i]->sprites);
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
			if (entities[i]->pos.y >(-App->render->camera.y + SCREEN_HEIGHT + (SPAWN_MARGIN + 1)) || entities[i]->pos.y < (-App->render->camera.y - (SPAWN_MARGIN + 1)))
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

	//App->tex->UnLoad(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
		if (queue[i].type != NO_TYPE)
		{
			queue[i].type = NO_TYPE;
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


void j1EntityManager::SpawnEntity(const EntityInfo& info)
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
		case ENTITY_TYPES::BAT:
			entities[i] = new Bat(info.x, info.y);
			break;
		}
	}
}

void j1EntityManager::OnCollision(Collider* c1, Collider* c2, float counterforce)
{
	
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr && entities[i]->GetCollider() == c1)
		{
			if (c2->type == COLLIDER_GROUND)
			{
				entities[i]->original_pos.y -= counterforce;
			}
		}
	}

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
