#include "j1Player.h"
#include "SDL/include/SDL.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collisions.h"

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

	foward.PushBack({ 1, 1, 30, 46 });
	foward.PushBack({ 32, 1, 30, 46 });
	foward.PushBack({ 63, 1, 30, 46 });
	foward.PushBack({ 94, 1, 30, 46 });
	foward.PushBack({ 125, 1, 30, 46 });
	foward.PushBack({ 156, 1, 30, 46 });
	foward.PushBack({ 187, 1, 30, 46 });
	foward.PushBack({ 218, 1, 30, 46 });
	foward.PushBack({ 249, 1, 30, 46 });
	foward.PushBack({ 280, 1, 30, 46 });
	foward.PushBack({ 311, 1, 30, 46 });
	foward.PushBack({ 342, 1, 30, 46 });
	foward.PushBack({ 373, 1, 30, 46 });
	foward.loop = true;
	foward.speed = 0.02f;
	
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

	player = App->collisions->AddCollider({0, 500, 18*3, 27*3}, COLLIDER_PLAYER);

	graphics = App->tex->Load("assets/Pumpkin sprites.png");
	if (graphics != NULL)
	{
		LOG("pene");
	}
	return true;
}

bool j1Player::Awake(pugi::xml_node& config) {

	//Load Player info from the config file

	return true;
}

bool j1Player::Update(float dt) 
{
	speed = 0.0f;
	gravity = 0.6f;
	
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
	{
		jumping = true;
	}

	// MOVEMENT -------------------------------------------
	//FOWARDS
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		animation = &foward;
		speed = 0.7f;
		right = true;
		left = false;
		last_direction = &foward;
	}

	
	//BACKWARDS
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		animation = &backward;
		speed = 0.7f;
		left = true;
		right = false;
		last_direction = &backward;
	}


	//IDLE
	else if (last_direction == &foward || last_direction == nullptr)
	{
		animation = &idle;
	}
	else if (last_direction == &backward)
	{
		animation = &idleLeft;
	}
	else
	{
		last_direction = &foward;
	}
	//JUMP
	if (jumping == true && right == true)
	{
		pos.x += speed - 0.2f;
	}
	else if (jumping == true && left == true)
	{
		pos.x -= (speed - 0.2f);
	}
	else if (jumping == false && right == true)
	{
		pos.x += speed;
		right = false;
	}
	else if (jumping == false && left == true)
	{
		pos.x -= speed;
		left = false;
	}
	if (jumping == true && counter < 241.9f && last_direction == &foward)
	{
		animation = &jump;
		gravity = 1.0f;
		pos.y -= gravity;
		++counter;
	}
	if (jumping == true && counter < 241.9f && last_direction == &backward)
	{
		animation = &jumpBackward;
		gravity = 1.0f;
		pos.y -= gravity;
		++counter;
	}

	if (jumping == true && counter >= 241.9f && last_direction == &foward)
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

	if (jumping == true && counter >= 241.9f && last_direction == &backward)
	{
		++counter;
		animation = &jumpBackward;
		gravity = 1.5f;
		pos.y += gravity;

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

	if (player != nullptr)
	{
		player->SetPos(pos.x + 10, pos.y + 50);
	}

	return true;

}


bool j1Player::CleanUp() 
{
	LOG("Unloading Player");

	App->tex->UnLoad(graphics);

	return true;
}

