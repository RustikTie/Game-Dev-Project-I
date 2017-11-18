#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Animation.h"
#include "Path.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Pathfinding.h"
#include "j1EntityManager.h"

class Player : public Entity
{
public:
	Player(int x, int y);
	~Player();
	void MovePlayer(float dt);

private:
	Animation* animation = nullptr;
	Animation* last_direction = nullptr;
	Animation idle;
	Animation forward;
	Animation jump;
	Animation death;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* textures = nullptr;

	int counter = 0;


	fPoint position;

};

#endif

