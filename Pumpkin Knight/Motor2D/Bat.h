#ifndef __BAT_H__
#define __BAT_H__

#include "Entity.h"
#include "Animation.h"
#include "Path.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1EntityManager.h"

class Bat : public Entity
{
public:
	Bat(int x, int y);
	~Bat();
	void MoveEnemy(float dt);
	p2DynArray<iPoint> path;

private:
	Animation idle;
	Animation fly;

	int counter = 0;

	bool attack = false;

	fPoint position;
};

#endif