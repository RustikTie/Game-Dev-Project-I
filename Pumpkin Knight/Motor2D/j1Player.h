#pragma once
#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "j1Collisions.h"
#include "j1Map.h"

struct SDL_Texture;

class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();

	void OnCollision(Collider* c1, Collider* c2);
	bool Awake(pugi::xml_node&);
	bool Start();
	bool Update(float dt);
	bool CleanUp();
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&)const;
	float getX()
	{
		return pos.x;
	}
	float getY()
	{
		return pos.y;
	}
	void SetPos(float x, float y) {
		pos.x = x;
		pos.y = y;
	}
	void Jump();
	Collider* player;

private:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* textures = nullptr;
	Animation* animation = nullptr;
	Animation* last_direction = nullptr;
	Animation idle;
	Animation forward;
	Animation jump;
	
	bool jumping = false;
	bool double_jumping = false;
	bool flip = false;
	bool falling = false; 
	bool dead = false;

	fPoint pos;
	float gravity;
	float speed;
	fPoint velocity;
	fPoint acceleration;
	fPoint jump_speed;
	float jump_height = 200;
	float max_height;

};

#endif