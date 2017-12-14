#ifndef __CANDY_H__
#define __CANDY_H__

#include "Entity.h"

class Candy : public Entity
{
public:
	Candy(int x, int y, int score);
	bool Awake(pugi::xml_node&);
	void Draw(float dt);
	void OnCollision();

	~Candy();

private: 
	SDL_Rect rec;
	bool grabbed = false;
	bool alive = true;
	Animation idle;
	Animation explosion;

	int score = 0;
	int candiesGrabbed = 0; 
};

#endif // !__CANDY_H__