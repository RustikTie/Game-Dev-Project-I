#include "j1Player.h"
#include "SDL/include/SDL.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collisions.h"
#include "j1Map.h"

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
	
	backward.PushBack({ 1, 189, 30, 46 });
	backward.PushBack({ 32, 189, 30, 46 });
	backward.PushBack({ 63, 189, 30, 46 });
	backward.PushBack({ 94, 189, 30, 46 });
	backward.PushBack({ 125, 189, 30, 46 });
	backward.PushBack({ 156, 189, 30, 46 });
	backward.PushBack({ 187, 189, 30, 46 });
	backward.PushBack({ 218, 189, 30, 46 });
	backward.PushBack({ 249, 189, 30, 46 });
	backward.PushBack({ 280, 189, 30, 46 });
	backward.PushBack({ 311, 189, 30, 46 });
	backward.PushBack({ 342, 189, 30, 46 });
	backward.PushBack({ 373, 189, 30, 46 });
	backward.loop = true;
	backward.speed = 0.02f;

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
	jump.speed = 0.03f;

	jumpBackward.PushBack({280, 283, 30, 46});
	jumpBackward.PushBack({ 249, 283, 30, 46 });
	jumpBackward.PushBack({ 218, 283, 30, 46 });
	jumpBackward.PushBack({ 218, 283, 30, 46 });
	jumpBackward.PushBack({ 187, 283, 30, 46 });
	jumpBackward.PushBack({ 156, 283, 30, 46 });
	jumpBackward.PushBack({ 125, 283, 30, 46 });
	jumpBackward.PushBack({ 94, 283, 30, 46 });
	jumpBackward.PushBack({ 63, 283, 30, 46 });
	jumpBackward.PushBack({ 63, 283, 30, 46 });
	jumpBackward.PushBack({ 32, 283, 30, 46 });
	jumpBackward.PushBack({ 1, 283, 30, 46 });
	jumpBackward.loop = false;
	jumpBackward.speed = 0.03f;

	idleLeft.PushBack({311, 236, 30, 46});
	idleLeft.PushBack({ 280, 236, 30, 46 });
	idleLeft.PushBack({ 249, 236, 30, 46 });
	idleLeft.PushBack({ 218, 236, 30, 46 });
	idleLeft.PushBack({ 187, 236, 30, 46 });
	idleLeft.PushBack({ 156, 236, 30, 46 });
	idleLeft.PushBack({ 125, 236, 30, 46 });
	idleLeft.PushBack({ 94, 236, 30, 46 });
	idleLeft.PushBack({ 63, 236, 30, 46 });
	idleLeft.PushBack({ 32, 236, 30, 46 });
	idleLeft.PushBack({ 1, 236, 30, 46 });
	idleLeft.loop = true;
	idleLeft.speed = 0.01f;

	pos.x = 0;
	pos.y = 250;
}


j1Player::~j1Player()
{
}

bool j1Player::Start() 
{
	LOG("Loading Player");

	player = App->collisions->AddCollider({0, 500, 18*3, 27*3}, COLLIDER_PLAYER, this);

	graphics = App->tex->Load("assets/Pumpkin sprites.png");
	
	return true;
}

bool j1Player::Awake(pugi::xml_node& config) {

	//Load Player info from the config file

	return true;
}

bool j1Player::Update(float dt) 
{
	speed = 0.6f;
	gravity = 0.6f;
	float y = pos.y;

	//MOVEMEMT
	//FORWARD
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		jumping = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_A) != KEY_REPEAT && jumping == false)
	{
		pos.x += speed;
		animation = &forward;
		last_direction = &forward;
		left = false;
		right = true;
	}
	//BACKWARD
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_D) != KEY_REPEAT && jumping == false)
	{
		if (pos.x > 2)
		{
			pos.x -= speed;		
			animation = &backward;
		}
		last_direction = &backward;
		left = true;
		right = false;
	}
	//IDLE RIGHT
	else if (last_direction == nullptr || last_direction == &forward && jumping == false)
	{
		animation = &idle;
		last_direction = &idle;
	}
	//IDLE LEFT
	else if (last_direction == &backward && jumping == false)
	{
		animation = &idleLeft;
		last_direction = &idleLeft;
	}
	//JUMP
	if (jumping == true && right == true)
	{
		pos.x += speed;
		if (jumping == true && counter < 241.9f && last_direction == &forward)
		{
			animation = &jump;
			gravity = 1.0f;
			pos.y -= gravity;
			++counter;
		}
		if (jumping == true && counter >= 241.9f && last_direction == &forward)
		{
			++counter;
			animation = &jump;
			gravity = 1.5f;
			pos.y += gravity;

			if (jump.Finished())
			{
				jumping = false;
				jump.Reset();
				counter = 0;
			}
		}
	}


	if (jumping == true && counter >= 241.9f && last_direction == &forward)
	{
		++counter;
		animation = &jump;		
		pos.x += speed;
		if (jump.Finished())

		{
			animation = &jumpBackward;
			yspeed = 0.9f;
			pos.y += yspeed;
			++counter;
		}
	}

	if (jumping == true && counter >= 241.9f && last_direction == &backward)

		{
			pos.x -= speed;
			++counter;
			animation = &jumpBackward;
			yspeed = 0.9f;
			pos.y += yspeed;

			if (jumpBackward.Finished())
			{
				jumping = false;
				jumpBackward.Reset();
				counter = 0;
			}
		}
	
	
	

	

	

	//DRAW PLAYER -----------------------------------------
	App->render->Blit(graphics, pos.x, pos.y, 3, 3, &(animation->GetCurrentFrame()), 1.0f);

	App->render->camera.x = -pos.x + 400;
	App->render->camera.y = -pos.y + 200;

	if (player->CheckCollision(App->map->collider) == false)
	{
		pos.y += gravity;
	}



	if (player != nullptr)
	{
		player->SetPos(pos.x + 10, pos.y + 50);
	}
	

	return true;

}

void j1Player::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_WALL)
	{
		pos.y -= gravity;
	}
}


bool j1Player::CleanUp() 
{
	LOG("Unloading Player");

	App->tex->UnLoad(graphics);

	return true;
}

void j1Player::Jump() 
{
			
}
