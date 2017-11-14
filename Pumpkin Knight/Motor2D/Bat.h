#ifndef __BAT_H__
#define __BAT_H__

#include "Entity.h"
#include "Animation.h"
#include "j1App.h"
#include "j1Textures.h"

class Bat : public Entity
{
public:
	Bat(int x, int y);
	~Bat();
	void MoveEnemy();
private:
	Animation idle;
	Animation fly;

	fPoint position;

	SDL_Texture* batsprite = nullptr;

};

#endif