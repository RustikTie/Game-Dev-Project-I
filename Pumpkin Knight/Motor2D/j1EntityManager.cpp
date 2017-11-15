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
	for (int i = 0; App->entity_manager->entities[i]; ++i)
	{
		entities[i]->collider->SetPos(entities[i]->pos.x, entities[i]->pos.y);
		App->render->Blit(entities[i]->texture,entities[i]->pos.x, entities[i]->pos.y, 1, 1, false, &entities[i]->animation->GetCurrentFrame());
	}

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


void j1EntityManager::DeleteEntity()
{
}