#pragma once
#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();


	bool Awake(pugi::xml_node& config);
	bool Start();
	bool Update(float dt);
	bool CleanUp();

private:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* textures = nullptr;
	Animation* animation = nullptr;
	Animation* animation2 = nullptr;
	Animation idle;
	Animation foward;
	Animation backward;
	Animation jump;
	Animation death;

	bool jumping = false;
	int counter = 0;
	bool diag_jump = false;

	fPoint pos;
	float speed;
};

#endif