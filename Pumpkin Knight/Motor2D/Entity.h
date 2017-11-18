#ifndef __ENTITY_H__
#define __ENTITY_H__


#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Collisions.h"

struct SDL_Texture;



class Entity
{
public:
	Entity(int x, int y);
	~Entity();

	const Collider* GetCollider() const;

	virtual void Draw(SDL_Texture* sprites);

	virtual void OnCollision(Collider* collider);
	//bool LoadEnemyLayer(pugi::xml_node& node, EnemyLayer* layer);
	virtual void MoveEnemy(float dt) {};

	SDL_Texture* sprites = nullptr;

public:

	Animation* animation = nullptr;

	fPoint pos;
	fPoint collider_pos;
	fPoint original_pos;

	Collider* collider = nullptr;

	int initial_pos;

	bool flip;
	
};

#endif // !_ENTITY_H_