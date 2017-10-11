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

	//jump.PushBack({})

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
	speed = 0.1f;

	// MOVEMENT -------------------------------------------
	//FOWARDS
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		animation = &foward;
		pos.x += speed;
	}
	
	//BACKWARDS
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		animation = &backward;
		pos.x -= speed;
	}
	else{
		animation = &idle;
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

