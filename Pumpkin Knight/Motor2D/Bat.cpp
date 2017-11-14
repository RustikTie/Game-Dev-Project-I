#include "Bat.h"



Bat::Bat(int x, int y) : Entity (x,y)
{
	batsprite = App->tex->Load("assests/bat.png");

	fly.PushBack({ 0, 0, 31, 31 });
	fly.PushBack({ 32, 0, 31, 31 });
	fly.PushBack({ 64, 0, 31, 31 });
	fly.PushBack({ 96, 0, 31, 31 });
	fly.PushBack({ 128, 0, 31, 31 });
	fly.speed = 1.5f;
	fly.loop = true;
}


Bat::~Bat()
{
}

void Bat::MoveEnemy()
{

}