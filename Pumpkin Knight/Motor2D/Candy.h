#ifndef __CANDY_H__
#define __CANDY_H__

#include "Entity.h"

class Candy : public Entity
{
public:
	Candy(int x, int y);
	bool Awake(pugi::xml_node&);
	void Draw(float dt);
	void OnCollision();

	~Candy();

private: 
	SDL_Rect rec;
	bool grabbed = false;
	Animation idle;
	Animation explosion;

};

#endif // !__CANDY_H__