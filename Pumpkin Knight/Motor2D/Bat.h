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

	bool Awake(pugi::xml_node&);
	void MoveEnemy(float dt);
	
private:
	Animation idle;
	Animation fly;

	uint counter = 0;

	bool attack_x = false;
	bool attack_y = false;
	bool move = false;

	fPoint position;
	fPoint speed;
};

#endif