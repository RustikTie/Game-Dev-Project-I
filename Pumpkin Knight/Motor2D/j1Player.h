#pragma once
#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "j1Collisions.h"

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
	int getX()
	{
		return pos.x;
	}
	int getY()
	{
		return pos.y;
	}
	void SetPos(float x, float y) {
		pos.x = x;
		pos.y = y;
	}
	Collider* player;

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
	float counter = 0.0f;
	bool right = false;
	bool left = false;

	fPoint pos;
	float gravity;
	float speed;
	float ground;
};

#endif