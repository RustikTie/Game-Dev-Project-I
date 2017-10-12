#include "j1Player.h"
#include "SDL/include/SDL.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"


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
	jump.PushBack({ 94, 95, 30, 46 });
	jump.PushBack({ 125, 95, 30, 46 });
	jump.PushBack({ 156, 95, 30, 46 });
	jump.PushBack({ 187, 95, 30, 46 });
	jump.PushBack({ 218, 95, 30, 46 });
	jump.PushBack({ 249, 95, 30, 46 });
	jump.PushBack({ 280, 95, 30, 46 });
	jump.loop = false;
	jump.speed = 0.006f;

	pos.x = 10;
	pos.y = 50;
}


j1Player::~j1Player()
{
}

bool j1Player::Start() 
{
	LOG("Loading Player");

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
	speed = 1.5f;

	// MOVEMENT -------------------------------------------
	//FOWARDS
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		animation = &foward;
		pos.x += speed;
		App->render->camera.x -= 2;
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			jumping = true;
		}
	}
	
	//BACKWARDS
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && diag_jump == false) 
	{
		animation = &backward;
		pos.x -= speed;
	}

	else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		jumping = true;
	}

	else{
		animation = &idle;
	}
	
	if (jumping == true && counter < 835)
	{
		animation = &jump;
		pos.y -= speed;
		++counter;
	}

	if (jumping == true && counter >= 835)
	{
		++counter;
		animation = &jump;
		pos.y += speed;
		
		if (jump.Finished())
		{
			jumping = false;
			jump.Reset();
			counter = 0;
		}
	}
	
	//DRAW PLAYER -----------------------------------------
	App->render->Blit(graphics, pos.x, pos.y, &(animation->GetCurrentFrame()), 0.75f);

	return true;

}


bool j1Player::CleanUp() 
{
	LOG("Unloading Player");

	App->tex->UnLoad(graphics);

	return true;
}

