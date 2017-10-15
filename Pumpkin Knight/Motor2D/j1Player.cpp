#include "j1Player.h"
#include "SDL/include/SDL.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collisions.h"
#include "j1Map.h"
#include "j1Audio.h"

j1Player::j1Player() : j1Module()
{
	name.create("player");
	animation = NULL;
	graphics = NULL;

	idle.PushBack({ 1,48,30,46 });
	idle.PushBack({ 32,48,30,46 });
	idle.PushBack({ 63,48,30,46 });
	idle.PushBack({ 94,48,30,46 });
	idle.PushBack({ 125,48,30,46 });
	idle.PushBack({ 156,48,30,46 });
	idle.PushBack({ 187,48,30,46 });
	idle.PushBack({ 218,48,30,46 });
	idle.PushBack({ 249,48,30,46 });
	idle.PushBack({ 280,48,30,46 });
	idle.PushBack({ 311,48,30,46 });
	idle.loop = true;
	idle.speed = 0.01f;

	forward.PushBack({ 1, 1, 30, 46 });
	forward.PushBack({ 32, 1, 30, 46 });
	forward.PushBack({ 63, 1, 30, 46 });
	forward.PushBack({ 94, 1, 30, 46 });
	forward.PushBack({ 125, 1, 30, 46 });
	forward.PushBack({ 156, 1, 30, 46 });
	forward.PushBack({ 187, 1, 30, 46 });
	forward.PushBack({ 218, 1, 30, 46 });
	forward.PushBack({ 249, 1, 30, 46 });
	forward.PushBack({ 280, 1, 30, 46 });
	forward.PushBack({ 311, 1, 30, 46 });
	forward.PushBack({ 342, 1, 30, 46 });
	forward.PushBack({ 373, 1, 30, 46 });
	forward.loop = true;
	forward.speed = 0.02f;

	jump.PushBack({ 1, 95, 30, 46 });
	jump.PushBack({ 32, 95, 30, 46 });
	jump.PushBack({ 63, 95, 30, 46 });
	jump.PushBack({ 63, 95, 30, 46 });
	jump.PushBack({ 94, 95, 30, 46 });
	jump.PushBack({ 125, 95, 30, 46 });
	jump.PushBack({ 156, 95, 30, 46 });
	jump.PushBack({ 187, 95, 30, 46 });
	jump.PushBack({ 218, 95, 30, 46 });
	jump.PushBack({ 218, 95, 30, 46 });
	jump.PushBack({ 249, 95, 30, 46 });
	jump.PushBack({ 280, 95, 30, 46 });
	jump.loop = false;
	jump.speed = 0.04f;

	pos.x = 100;
	pos.y = 200;
}


j1Player::~j1Player()
{
}

bool j1Player::Start() 
{
	LOG("Loading Player");

	player = App->collisions->AddCollider({ 0, 500, 18 * 3, 27 * 3 }, COLLIDER_PLAYER, this);
	graphics = App->tex->Load("assets/Pumpkin sprites.png");
	
	return true;
}

bool j1Player::Awake(pugi::xml_node& config) 
{

	//Load Player info from the config file

	return true;
}

bool j1Player::Update(float dt) 
{
	speed = 0.8f;
	gravity = 0.8f;
	float y = pos.y;

	//MOVEMEMT
	//FORWARD
	if (falling == false)
	{
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		{
			jumping = true;
			if (counter >= 90)
			{
				if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
				{
					double_jumping = true;
				}
			}
		}
	}
	
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		flip = false;
		right = true;
		pos.x += speed;
		if (falling == false)
		{
			animation = &forward;
		}
		if (jumping == false)
			App->audio->PlayFx(1, 0);
	}
	//BACKWARD
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		flip = true;
		left = true;
		pos.x -= speed;		
		if (falling == false)
		{
			animation = &forward;
		}
		if (jumping == false)
			App->audio->PlayFx(1, 0);
	}
	//IDLE RIGHT
	else 
	{
		animation = &idle;
		right = false;
		left = false;
	}
	
	//JUMP

	Jump();

	if (jumping == true && flip == false && right == true && player->CheckCollision(App->map->collider) == false)
	{
		speed = 0.1f;
	}
	else if (jumping == true && flip == true && left == true && player->CheckCollision(App->map->collider) == false)
	{
		speed = 0.1f;
	}
	//DRAW PLAYER -----------------------------------------
	App->render->Blit(graphics, pos.x, pos.y, 3, 3, flip, &(animation->GetCurrentFrame()), 1.0f);

	App->render->camera.x = -pos.x + 400;
	//App->render->camera.y = -pos.y + 200;

	if (player->CheckCollision(App->map->collider) == false)
	{
		pos.y += gravity;
	}


	if (player != nullptr)
	{
		player->SetPos(pos.x + 10, pos.y + 50);
	}
	
	if (pos.y > 500)
	{
		if (pos.y > 600)
		{
			pos.x = 100;
			pos.y = 200;
		}
	
	}

	return true;

}

void j1Player::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_WALL && (player->rect.y + player->rect.h) <= (c2->rect.y +1) && (player->rect.y + player->rect.h) < (c2->rect.y + c2->rect.h))
	{
		pos.y -= gravity;
		falling = false;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && c2->type == COLLIDER_WALL && (player->rect.x + player->rect.w) >= c2->rect.x && (player->rect.x + player->rect.w) < (c2->rect.x + c2->rect.w) && 
		(player->rect.y + player->rect.h - 1) > c2->rect.y && (player->rect.y + player->rect.h - 1) < (c2->rect.y + c2->rect.h)) //COLL FOWARD
	{
		pos.x -= speed;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && c2->type == COLLIDER_WALL && (player->rect.x) > c2->rect.x && (player->rect.x) <= (c2->rect.x + c2->rect.w) &&
		(player->rect.y + player->rect.h - 1) > c2->rect.y && (player->rect.y + player->rect.h - 1) < (c2->rect.y + c2->rect.h))
	{
		pos.x += speed;
	}
	

	
}

bool j1Player::Load(pugi::xml_node& data)
{
	pos.x = data.child("player_pos").attribute("x").as_float();
	pos.y = data.child("player_pos").attribute("y").as_float();

	return true;
}

bool j1Player::Save(pugi::xml_node& data)const
{
	pugi::xml_node& node = data.append_child("player_pos");

	node.append_attribute("x") = pos.x;
	node.append_attribute("y") = pos.y;

	return true;
}

bool j1Player::CleanUp() 
{
	LOG("Unloading Player");

	App->tex->UnLoad(graphics);
	if (player != NULL)
		player->to_delete = true;

	return true;
}

void j1Player::Jump() 
{
	
	if (jumping == true)
	{
		if (counter < 250.0f  && player->CheckCollision(App->map->collider) == false)
		{
			gravity = 0;

			pos.y -= 1.0f;
			animation = &jump;
			++counter;
			if (double_jumping == true)
			{
				pos.y -= 1.0f;
			}
		}
		else if (counter >= 250.0f && player->CheckCollision(App->map->collider) == false)
		{
			gravity = 0;

			double_jumping = false;
			pos.y += 1.5f;
			jump.GetCurrentFrame();
			++counter;
			if (jump.Finished())
			{
				gravity = 0.8f;
				counter = 0;
				jump.Reset();
				jumping = false;
				falling = true;
			}
		}
		else if (player->CheckCollision(App->map->collider) == true)
		{
			gravity = 0.8f;
			counter = 0;
			jump.Reset();
			jumping = false;
			falling = true;
			
		}
	}
}
