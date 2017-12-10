#include "Wolf.h"


Wolf::Wolf(int x, int y) : Entity(x, y)
{
	
	App->entity_manager->wolf = true;

	idle.PushBack({ 0, 98, 65, 32 });
	//idle.PushBack({ 65, 0, 64, 32 });

	idle.speed = 0.15f;
	idle.loop = true;

	walk.PushBack({ 65, 98, 65, 32 });
	walk.PushBack({ 130, 98, 65, 32 });
	walk.PushBack({ 195, 98, 65, 32 });
	walk.PushBack({ 260, 98, 65, 32 });
	walk.speed = 0.1f;
	walk.loop = true;

	animation = &idle;

	collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 64*2, 32*2 }, COLLIDER_ENEMY, (j1Module*)App->entity_manager);

	initial_pos = original_pos.x;
}

bool Wolf::Awake(pugi::xml_node& config)
{
	pugi::xml_document	config_file;
	pugi::xml_node		config2;
	
	config2 = App->LoadConfig(config_file);

	config2 = config2.child("entities").child("wolf");

	speed.x = config2.child("speed").attribute("x").as_float();
	speed.y = config2.child("speed").attribute("y").as_float();
	move = config2.child("move").attribute("value").as_bool(false);
	attack = config2.child("attack").attribute("value").as_bool(false);
	x_scale = config2.child("scale").attribute("x").as_int();
	y_scale = config2.child("scale").attribute("x").as_int();

	return true;
}

Wolf::~Wolf()
{
	App->tex->UnLoad(sprites);
}

void Wolf::MoveEntity(float dt)
{
	pos = original_pos;
	original_pos.y += App->entity_manager->player_entity->gravity*dt;


	iPoint EnemyPos = { (int)original_pos.x + 64, (int)original_pos.y + 32};
	iPoint PlayerPos{ (int)App->entity_manager->player_entity->pos.x + 30, (int)App->entity_manager->player_entity->pos.y + 46 };

	if ((abs(App->entity_manager->player_entity->pos.x - EnemyPos.x) < 400) && !move)
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

	if (abs(App->entity_manager->player_entity->pos.x - EnemyPos.x) >= 400)
	{
		move = false;
	}
	
}

void Wolf::Draw(float dt)
{
	animation->speed = 10.f*dt;
	collider->SetPos(pos.x, pos.y);
	App->render->Blit(App->entity_manager->GetEntityAtlas(), pos.x, pos.y, x_scale, y_scale, flip, &(animation->GetCurrentFrame()));
}