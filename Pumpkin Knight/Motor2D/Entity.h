#ifndef __ENTITY_H__
#define __ENTITY_H__


#include "j1Module.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "Animation.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Collisions.h"

struct SDL_Texture;



class Entity
{
protected:
	Animation* animation = nullptr;

public:
	Entity(int x, int y);
	~Entity();

	const Collider* GetCollider() const;

	virtual bool Awake(pugi::xml_node&);

	virtual void Draw(SDL_Texture* sprites);

	virtual void OnCollision(Collider* collider);
	//bool LoadEnemyLayer(pugi::xml_node& node, EnemyLayer* layer);
	virtual void MoveEnemy(float dt) {};

public:

	SDL_Texture* sprites = nullptr;

	fPoint pos;
	fPoint collider_pos;
	fPoint original_pos;
	fPoint speed;

	Collider* collider = nullptr;

	p2DynArray<iPoint> path;

	int initial_pos;

	bool flip = false;
};

#endif // !_ENTITY_H_