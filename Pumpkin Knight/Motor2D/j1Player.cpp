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

	idle.PushBack({0,0,30,46});
	idle.loop = false;

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

	return true;
}

bool j1Player::Awake(pugi::xml_node& config) {

	//Load Player info from the config file

	return true;
}

bool j1Player::Update() 
{
	speed = 1;

	// MOVEMENT -------------------------------------------
	//FOWARDS
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		pos.x += speed;
	}

	//BACKWARDS
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		pos.x -= speed;
	}

	animation = &idle;

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

