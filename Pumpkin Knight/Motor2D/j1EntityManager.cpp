#include "j1EntityManager.h"
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

void j1EntityManager::CreateEntity(EntityType etype, fPoint pos) 
{
	Entity* entity = nullptr;
	SDL_Rect wolfCol;
	wolfCol.x = 150;
	wolfCol.y = 200;
	wolfCol.w = 66;
	wolfCol.h = 34;

	if (etype == WHITE_WOLF)
	{
		entity->texture = App->entity->white_wolf;
		entity->collider = App->collisions->AddCollider(wolfCol, COLLIDER_ENEMY, NULL);
				
		entities.add(entity);
	}


}


void j1EntityManager::DeleteEntity()
{
}