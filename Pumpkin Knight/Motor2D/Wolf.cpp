#include "Wolf.h"


Wolf::Wolf(int x, int y) : Entity(x, y)
{
	sprites = App->tex->Load("assets/wolfLight.png");
	App->entity_manager->wolf = true;

	idle.PushBack({ 0, 0, 64, 32 });
	//idle.PushBack({ 65, 0, 64, 32 });

	idle.speed = 0.15f;
	idle.loop = true;

	walk.PushBack({ 65, 98, 64, 32 });
	walk.PushBack({ 130, 98, 64, 32 });
	walk.PushBack({ 195, 98, 64, 32 });
	walk.PushBack({ 260, 98, 64, 32 });
	walk.speed = 0.1f;
	walk.loop = true;

	animation = &idle;

	collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 64*2, 32*2 }, COLLIDER_ENEMY, (j1Module*)App->entity_manager);

	initial_pos = original_pos.x;
}

bool Wolf::Awake(pugi::xml_node& config)
{
	pugi::xml_node wolf_entity = config.child("config").child("entities");

	speed.x = wolf_entity.child("wolf").child("speed").attribute("x").as_float();
	speed.y = wolf_entity.child("wolf").child("speed").attribute("y").as_float();
	move = wolf_entity.child("wolf").child("move").attribute("value").as_bool(false);
	attack = wolf_entity.child("wolf").child("attack").attribute("value").as_bool(false);
	flip = wolf_entity.child("wolf").child("flip").attribute("value").as_bool(false);

	return true;
}

Wolf::~Wolf()
{
	App->tex->UnLoad(sprites);
}

void Wolf::MoveEnemy(float dt)
{
	pos = original_pos;
	original_pos.y += App->player->gravity*dt;


	iPoint EnemyPos = { (int)original_pos.x + 64, (int)original_pos.y + 32};
	iPoint PlayerPos{ (int)App->player->pos.x + 30, (int)App->player->pos.y + 46 };

	if ((abs(App->player->pos.x - EnemyPos.x) < 400) && !move)
	{
		counter = 0;

		App->pathfinding->CreatePath(EnemyPos, PlayerPos);
		App->pathfinding->BackTrackingGround(PlayerPos, path);
		
		move = true;
		attack = true;

		//attack = true;
		//App->pathfinding->DrawPath(path);
	}

	if (move)
	{
		/*iPoint Destination = App->map->MapToWorld(path[counter].x, path[counter].y);*/
		iPoint Destination = { path[counter].x, path[counter].y };
		animation = &walk;
		
		if (EnemyPos.x < Destination.x)
		{
			original_pos.x += speed.x*dt;
			flip = false;
			if (EnemyPos.x >= Destination.x)
			{
				counter++;
				move = false;
			}
		}

		else
		{
			original_pos.x -= speed.x*dt;
			flip = true;
			if (EnemyPos.x <= Destination.x)
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
		animation = &idle;
	}

	if (abs(App->player->pos.x - EnemyPos.x) >= 400)
	{
		move = false;
	}
	
}