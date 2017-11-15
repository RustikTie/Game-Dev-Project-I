#include "j1EntityManager.h"
#include "Entity.h"
#include "Wolf.h"

#define SPAWN_MARGIN 100

j1EntityManager::j1EntityManager()
{
	name.create("entities");
}


j1EntityManager::~j1EntityManager()
{
}

bool j1EntityManager::Awake(pugi::xml_node&) 
{

	return true;
}
bool j1EntityManager::Start()
{

	return true;
}
bool j1EntityManager::PreUpdate()
{

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENTITY_TYPES::NO_TYPE)
		{
			if (queue[i].y > App->render->camera.y - SPAWN_MARGIN)
			{
				LOG("Spawning entity at %d", queue[i].y);
				SpawnEntity(queue[i]);
				queue[i].type = ENTITY_TYPES::NO_TYPE;

			}
		}
	}
	return true;
}
bool j1EntityManager::Update(float dt)
{

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (entities[i] != nullptr)
		{
		}
	return true;
}
bool j1EntityManager::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			if (entities[i]->pos.x < -500 || entities[i]->pos.y > 1000 || entities[i]->pos.x < -500 || entities[i]->pos.x > 1300)
			{
				LOG("DeSpawning entity at %d", entities[i]->pos.y);
				delete entities[i];
				entities[i] = nullptr;
			}
		}
	}
	return true;
}
bool j1EntityManager::CleanUp()
{
	LOG("Freeing all entities");

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

Entity* j1EntityManager::CreateEntity(ObjectLayer* object, uint id, uint i) 
{
	Entity* entity = nullptr;
	SDL_Rect wolfCol;
	wolfCol.x = 150;
	wolfCol.y = 200;
	wolfCol.w = 66;
	wolfCol.h = 34;
	
	if (object[i].entity_type[id] == WHITE_WOLF)
	{
		entity->texture = App->entity->white_wolf;
		entity->collider = App->collisions->AddCollider(wolfCol, COLLIDER_ENEMY, NULL);
		entity->pos.x = object[i].x[id];
		entity->pos.y = object[i].y[id];
		entity->animation = NULL;
		entities.add(entity);		
	}

	return entity;
}

bool j1EntityManager::AddEnemy(int path, ENTITY_TYPES type, int x, int y)
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
	for (uint i = 0; entities[i] != nullptr && i < MAX_ENEMIES; ++i)
	{
		if (i != MAX_ENEMIES)
		{
			switch (info.type)
			{
			case ENTITY_TYPES::BAT:
				entities[i] = new Bat(info.x, info.y);
				break;
			case ENTITY_TYPES::WOLF:
				entities[i] = new Wolf(info.x, info.y);
				break;
			}
		}
	}

}

void j1EntityManager::DeleteEntity()
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