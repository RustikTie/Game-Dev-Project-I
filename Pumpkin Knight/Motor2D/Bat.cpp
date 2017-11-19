#include "Bat.h"


Bat::Bat(int x, int y) : Entity (x,y)
{
	sprites = App->tex->Load("assets/bat.png");
	App->entity_manager->bat = true;

	fly.PushBack({ 0, 0, 31, 44 });
	fly.PushBack({ 32, 0, 31, 44 });
	fly.PushBack({ 64, 0, 31, 44 });
	fly.PushBack({ 96, 0, 31, 44 });
	fly.PushBack({ 128, 0, 31, 44 });
	fly.speed = 0.4f;

	fly.loop = true;

	animation = &fly;


	collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 31 * 2, 31 * 2}, COLLIDER_ENEMY, (j1Module*)App->entity_manager);

	initial_pos = original_pos.x;
}

bool Bat::Awake(pugi::xml_node& config)
{
	pugi::xml_node bat_entity = config.child("config").child("entities");

	speed.x = bat_entity.child("bat").child("speed").attribute("x").as_float();
	speed.y = bat_entity.child("bat").child("speed").attribute("y").as_float();

	return true;
}

Bat::~Bat()
{
	App->tex->UnLoad(sprites);
}

void Bat::MoveEnemy(float dt)
{
	pos = original_pos;

	

	iPoint EnemyPos = { (int)original_pos.x + 32, (int)original_pos.y };
	iPoint PlayerPos{ (int)App->player->pos.x + 30, (int)App->player->pos.y + 46 };

	if ((abs(App->player->pos.x - EnemyPos.x) < 400) && !move)
	{
		counter = 0;
		//iPoint PlayerPos{ (int)App->player->pos.x + 30, (int)App->player->pos.y + 46 };
		App->pathfinding->CreatePath(EnemyPos, PlayerPos);
		App->pathfinding->BackTrackingAir(PlayerPos, path);
		
		move = true;
		attack_x = true;
		//App->pathfinding->DrawPath(path);
	}

	if (move)
	{
		iPoint Destination = { path[counter].x, path[counter].y };

		animation = &fly;
		
		if (EnemyPos.x < Destination.x)
		{
			original_pos.x += speed.x*dt;
			flip = true;
			if (EnemyPos.x >= Destination.x)
			{
				counter++;
				move = false;
			}
		}

		else
		{
			original_pos.x -= speed.x*dt;
			flip = false;
			if (EnemyPos.x <= Destination.x)
			{
				counter++;
				move = false;
			}
		}

		if (EnemyPos.y < Destination.y)
		{
			original_pos.y += speed.y*dt;
			if (EnemyPos.y >= Destination.y)
			{
				counter++;
				move = false;
			}
		}
		 
		else 
		{
			original_pos.y -= speed.y*dt;
			if (EnemyPos.y < Destination.y)
			{
				counter++;
				move = false;
			}
		}

		
		if (EnemyPos.x != Destination.x && EnemyPos.y != Destination.y)
		{
			move = false;
		}

	}
	else
	{
		animation = &fly;
	}

	if (abs(App->player->pos.x - EnemyPos.x) >= 400)
	{
		move = false;
	}
}