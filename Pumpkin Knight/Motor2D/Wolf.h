#ifndef __WOLF_H__
#define __WOLF_H__

#include "Entity.h"
#include "Animation.h"
#include "Path.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Pathfinding.h"
#include "j1EntityManager.h"

class Wolf : public Entity
{
public:
	Wolf(int x, int y);
	~Wolf();

	bool Awake(pugi::xml_node&);
	void MoveEntity(float dt);

private:
	Animation idle;
	Animation walk;

	int counter = 0;

	bool move = false;
	bool attack = false;

	fPoint position;
	fPoint speed;

	//SDL_Texture* wolfsprite = nullptr;
};

#endif

