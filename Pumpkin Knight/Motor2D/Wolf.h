#ifndef __WOLF_H__
#define __WOLF_H__

#include "Entity.h"
#include "Animation.h"
#include "Path.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Pathfinding.h"
#include "j1EntityManager.h"

class Wolf : public Entity
{
public:
	Wolf(int x, int y);
	~Wolf();
	void MoveEnemy(float dt);
	p2DynArray<iPoint> path;
private:
	Animation idle;
	Animation walk;

	int counter = 0;

	bool attack = false;

	fPoint position;

	//SDL_Texture* wolfsprite = nullptr;
};

#endif

