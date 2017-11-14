#ifndef __ENTITY_H__
#define __ENTITY_H__


#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Collisions.h"

struct SDL_Texture;



class Entity : public j1Module
{
public:
	Entity(int x, int y);
	~Entity();

	const Collider* GetCollider() const;

	void Draw(SDL_Texture* sprites);

	void OnCollision(Collider* collider);
	//bool LoadEnemyLayer(pugi::xml_node& node, EnemyLayer* layer);

private:

	Animation* animation;
	fPoint pos;
	SDL_Texture* texture;

private:

	Collider* collider = nullptr;

};

#endif // !_ENTITY_H_