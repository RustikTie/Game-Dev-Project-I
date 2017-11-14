#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "j1Module.h"
#include "p2Point.h"

struct SDL_Texture;



class Entity : public j1Module
{
public:
	Entity();
	~Entity();

	void Update();
	void Draw();
	//bool LoadEnemyLayer(pugi::xml_node& node, EnemyLayer* layer);

private:

	fPoint pos;
	SDL_Texture* texture;

};

#endif // !_ENTITY_H_