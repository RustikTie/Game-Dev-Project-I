#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "j1Module.h"
#include "p2Point.h"

struct SDL_Texture;

enum EntityType
{
	BAT,
	WOLF,
	PLAYER
};

class Entity : public j1Module
{
public:
	Entity();
	~Entity();

	void Update();
	void Draw();
	
private:

	fPoint pos;
	EntityType type;
	SDL_Texture* texture;

};

#endif // !_ENTITY_H_