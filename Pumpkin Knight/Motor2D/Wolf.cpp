#include "Wolf.h"


Wolf::Wolf(int x, int y) : Entity(x, y)
{
	wolfsprite = App->tex->Load("assets/wolfMedium.png");
	idle.PushBack({ 0, 33, 64, 64 });
	idle.PushBack({ 65, 33, 64, 64 });

	idle.speed = 1.5f;
	idle.loop = true;

	walk.PushBack({ 65, 98, 64, 32 });
	walk.PushBack({ 130, 98, 64, 32 });
	walk.PushBack({ 195, 98, 64, 32 });
	walk.PushBack({ 260, 98, 64, 32 });
	walk.speed = 1.5f;
	walk.loop = true;

	animation = &walk;

	collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 64, 32 }, COLLIDER_ENEMY, (j1Module*)App->entity_manager);
}


Wolf::~Wolf()
{
}

void Wolf::MoveEnemy()
{
	iPoint enemyposition = { (int)original_pos.x,(int)original_pos.y };
}