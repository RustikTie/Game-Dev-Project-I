#include "j1EntityManager.h"
#include "Entity.h"
#include "Wolf.h"
#include "Player.h"
#include "Candy.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1Textures.h"
#include "Brofiler\Brofiler.h"


#define SPAWN_MARGIN 100

j1EntityManager::j1EntityManager()
{
	name.create("entities");

}

bool j1EntityManager::Awake(pugi::xml_node& config)
{
	config_file.load_file("config.xml");
	entity_config = config;
	return true;
}

// Destructor
j1EntityManager::~j1EntityManager()
{
}

bool j1EntityManager::Start()
{
	LOG("loading entities");
	entityAtlas = App->tex->Load("assets/enemySprites.png");

	if (App->scene->start == false)
	{
		if (player_entity == nullptr)
		{
			player_entity = new Player(100, 200);
			player_entity->Awake(entity_config);
			player_entity->Start();
		}
	}
	return true;
}

bool j1EntityManager::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdate EntityManager", Profiler::Color::Yellow)

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
	BROFILER_CATEGORY("PreUpdate EntityManager", Profiler::Color::Green)

		if (dt < 1)
		{
			for (uint i = 0; i < MAX_ENEMIES; ++i)
			{
				if (entities[i] != nullptr)
				{
					entities[i]->MoveEntity(dt);
					entities[i]->Draw(dt);
					entities[i]->Awake(entity_config);
				}
				if (player_entity != nullptr)
				{
					player_entity->MoveEntity(dt);
					player_entity->Draw(dt);
				}
			}
		}
	
	return true;
}

bool j1EntityManager::PostUpdate()
{
	BROFILER_CATEGORY("PreUpdate EntityManager", Profiler::Color::Blue)

	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			if ((abs((int)App->render->camera.y) + SCREEN_HEIGHT + SPAWN_MARGIN) < entities[i]->pos.y)
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
		case ENTITY_TYPES::PLAYER:
			entities[i] = new Player(info.x, info.y);
			break;
		case ENTITY_TYPES::CANDY:
			entities[i] = new Candy(info.x, info.y);
			candies.add(entities[i]);
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

			if (c2->type == COLLIDER_BLOCKER)
			{
				if (!entities[i]->flip)
				{
					entities[i]->original_pos.x -= counterforce;
				}
				else
				{
					entities[i]->original_pos.x += counterforce;
				}
			}

			if (c2->type == COLLIDER_WALL)
			{
				if (!entities[i]->flip)
				{
					entities[i]->original_pos.x -= counterforce;
				}
				else
				{
					entities[i]->original_pos.x += counterforce;
				}
			}
		}

		if (player_entity != nullptr && player_entity->GetCollider() == c1)
		{
			if (c2->type == COLLIDER_GROUND)
			{
				player_entity->pos.y -= counterforce;
			}

			if (c2->type == COLLIDER_WALL)
			{
				player_entity->original_pos.x -= counterforce;
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

bool j1EntityManager::Load(pugi::xml_node& data)
{
	player_entity->pos.x = data.child("player_pos").attribute("x").as_float();
	player_entity->pos.y = data.child("player_pos").attribute("y").as_float();

	return true;
}

bool j1EntityManager::Save(pugi::xml_node& data)const
{
	pugi::xml_node& node = data.append_child("player_pos");

	node.append_attribute("x") = player_entity->pos.x;
	node.append_attribute("y") = player_entity->pos.y;

	return true;
}

SDL_Texture* j1EntityManager::GetEntityAtlas() const
{
	return entityAtlas;
}