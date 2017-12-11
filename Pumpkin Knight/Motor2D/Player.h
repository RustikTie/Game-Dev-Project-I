#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Animation.h"
#include "Path.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Pathfinding.h"
#include "j1EntityManager.h"

class Player : public Entity
{
public:
	Player(int x, int y);
	~Player();
	bool Start();
	void MoveEntity(float dt);
	void Jump(float dt);
	bool Awake(pugi::xml_node& config);
	void Draw(float dt);

	void SetPos(float x, float y) {
		pos.x = x;
		pos.y = y;
	}

	float getX()
	{
		return pos.x;
	}
		float getY()
	{
		return pos.y;
	}
	Collider* playercollider = nullptr;

	float gravity;
	float speed;
	float jump_height;
	float max_height;

	bool falling = false;
	bool jumping = false;
	bool double_jumping = false;
	bool contact = false;
	bool godmode = false;

	fPoint velocity;
	fPoint acceleration;
	fPoint jump_speed;
	fPoint jumping_speed;


	fPoint position;
	int score = 0;
	int lives = 3;

private:
	//Animation* animation = nullptr;
	//Animation* last_direction = nullptr;
	Animation idle;
	Animation forward;
	Animation jump;
	Animation death;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* textures = nullptr;

	int counter = 0;
	bool dead = false;
	SDL_Rect heart;

};

#endif

