#ifndef __WOLF_H__
#define __WOLF_H__

#include "Entity.h"
#include "Animation.h"
#include "j1App.h"
#include "j1Textures.h"

class Wolf : public Entity
{
public:
	Wolf(int x, int y);
	~Wolf();
	void MoveEnemy();
private:
	Animation idle;
	Animation walk;

	fPoint position;

	SDL_Texture* wolfsprite = nullptr;
};

#endif

