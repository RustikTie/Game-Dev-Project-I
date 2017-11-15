#include "j1EntityManager.h"
#include "Entity.h"
#include "Wolf.h"


j1EntityManager::j1EntityManager()
{
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
bool j1EntityManager::Update(float dt)
{

	return true;
}
bool j1EntityManager::PostUpdate(float dt)
{

	return true;
}
bool j1EntityManager::CleanUp()
{

	return true;
}

Entity* j1EntityManager::CreateEntity(ObjectLayer object) 
{
	Entity* entity = nullptr;
	SDL_Rect wolfCol;
	wolfCol.x = 150;
	wolfCol.y = 200;
	wolfCol.w = 66;
	wolfCol.h = 34;

	if (object.entity_type == WHITE_WOLF)
	{
		entity->texture = App->entity->white_wolf;
		entity->collider = App->collisions->AddCollider(wolfCol, COLLIDER_ENEMY, NULL);
		entity->pos.x = object.x[0];
		entity->pos.y = object.y[0];
		entity->animation = App->entity->animation;
		entities.add(entity);
	}

	return entity;
}


void j1EntityManager::DeleteEntity()
{
}