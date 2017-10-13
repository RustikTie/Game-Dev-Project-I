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
	foward.speed = 0.04f;
	
	backward.PushBack({ 1, 1, 30, 46 });
	backward.PushBack({ 373, 1, 30, 46 });
	backward.PushBack({ 342, 1, 30, 46 });
	backward.PushBack({ 311, 1, 30, 46 });
	backward.PushBack({ 280, 1, 30, 46 });
	backward.PushBack({ 249, 1, 30, 46 });
	backward.PushBack({ 218, 1, 30, 46 });
	backward.PushBack({ 187, 1, 30, 46 });
	backward.PushBack({ 156, 1, 30, 46 });
	backward.PushBack({ 125, 1, 30, 46 });
	backward.PushBack({ 94, 1, 30, 46 });
	backward.PushBack({ 63, 1, 30, 46 });
	backward.PushBack({ 32, 1, 30, 46 });
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
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		animation = &foward;
		speed = 1.0f;
		right = true;
	}

	
	//BACKWARDS
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT ) 
	{
		animation = &backward;
		speed = 1.0f;
		right = false;
	}

	else
	{
		animation = &idle;
	}
	if (jumping == true && right == true)
	{
		pos.x += speed/2;
	}
	else if (jumping == true && right == false)
	{
		pos.x -= speed / 2;
	}
	else if (jumping == false && right == true)
	{
		pos.x += speed;
	}
	else if (jumping == false && right == false)
	{
		pos.x -= speed;
	}
	if (jumping == true && counter < 241.9f)
	{
		animation = &jump;
		gravity = 1.0f;
		pos.y -= gravity;
		++counter;
	}

	if (jumping == true && counter >= 241.9f)
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

