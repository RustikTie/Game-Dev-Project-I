#include "Wolf.h"


Wolf::Wolf(int x, int y) : Entity(x, y)
{
	white_wolf = App->tex->Load("assets/wolfMedium.png");
	idle.PushBack({ 0, 33, 64, 64 });
	idle.PushBack({ 65, 33, 64, 64 });

	idle.speed = 1.5f;
	idle.loop = true;

	walk.PushBack({ 65, 98, 64, 32 });
	walk.PushBack({ 130, 98, 64, 32 });
	walk.PushBack({ 195, 98, 64, 32 });
	walk.PushBack({ 260, 98, 64, 32 });
	walk.speed = 0.3f;
	walk.loop = true;

	animation = &walk;

	collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 64*2, 32*2 }, COLLIDER_ENEMY, (j1Module*)App->entity_manager);
}


Wolf::~Wolf()
{
}

void Wolf::MoveEnemy(float dt)
{
	//animation = &walk;
	pos = original_pos;
	original_pos.y += App->player->gravity*dt;
	
	iPoint EnemyPos = { (int)original_pos.x + 64, (int)original_pos.y + 32};
	iPoint PlayerPos{ (int)App->player->pos.x + 30, (int)App->player->pos.y + 46 };
	App->pathfinding->CreatePath(EnemyPos, PlayerPos);
	App->pathfinding->BackTracking(PlayerPos, path);
	App->pathfinding->DrawPath(path);
	
}