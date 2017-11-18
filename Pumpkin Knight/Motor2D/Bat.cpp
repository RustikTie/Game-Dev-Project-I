#include "Bat.h"


Bat::Bat(int x, int y) : Entity (x,y)
{
	batsprite = App->tex->Load("assets/bat.png");
	App->entity_manager->bat = true;

	fly.PushBack({ 0, 0, 31, 44 });
	fly.PushBack({ 32, 0, 31, 44 });
	fly.PushBack({ 64, 0, 31, 44 });
	fly.PushBack({ 96, 0, 31, 44 });
	fly.PushBack({ 128, 0, 31, 44 });
	fly.speed = 0.3f;
	fly.loop = true;

	animation = &fly;

	collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 31*3 , 31*3  }, COLLIDER_ENEMY, (j1Module*)App->entity_manager);

	initial_pos = original_pos.x;
}


Bat::~Bat()
{
	//App->tex->UnLoad(batsprite);
}

void Bat::MoveEnemy(float dt)
{
	pos = original_pos;

	fPoint speed;

	iPoint EnemyPos = { (int)original_pos.x + 64, (int)original_pos.y + 32 };
	iPoint PlayerPos{ (int)App->player->pos.x + 30, (int)App->player->pos.y + 46 };

	if ((abs(PlayerPos.x - EnemyPos.x) < 500))
	{
		App->pathfinding->CreatePath(EnemyPos, PlayerPos);
		App->pathfinding->BackTracking(PlayerPos, path);
		attack = true;
		//App->pathfinding->DrawPath(path);
	}

	if (attack)
	{
		animation = &fly;
		if (EnemyPos.x < PlayerPos.x)
		{
			speed.x = 2;
			flip = true;
		}

		if (EnemyPos.x > PlayerPos.x)
		{
			speed.x = -2;
			flip = false;
		}

		if (EnemyPos.y < PlayerPos.y)
		{
			speed.y = 2;
		}

		if (EnemyPos.y > PlayerPos.y)
		{
			speed.y = -2;
		}

		//iPoint Destination = App->map->MapToWorld(path[counter].x, path[counter].y);

		if (EnemyPos.x != PlayerPos.x && EnemyPos.y != PlayerPos.y)
		{
			original_pos.x += speed.x;
			original_pos.y += speed.y;
		}

		if (EnemyPos == PlayerPos)
		{
			counter++;
		}

		if (abs(PlayerPos.x - (int)original_pos.x) >= 400)
		{
			attack = false;
			//initial_pos = original_pos.x;
		}
	}
	else
	{
		animation = &fly;
	}
}