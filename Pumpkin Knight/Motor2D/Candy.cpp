#include "Candy.h"
#include "j1Gui.h"
#include "j1Render.h"


Candy::Candy(int x, int y): Entity(x,y)
{
	idle.PushBack({ 339, 294, 52, 50 });
	idle.PushBack({ 392, 294, 52, 50 });
	animation = &idle;

	explosion.PushBack({ 444, 294, 52, 50 });
	explosion.PushBack({ 497, 294, 52, 50 });
	explosion.PushBack({ 339, 345, 52, 50 });
	explosion.PushBack({ 392, 345, 52, 50 });
	explosion.PushBack({ 444, 345, 52, 50 });

}


Candy::~Candy()
{
}

bool Candy::Awake(pugi::xml_node&)
{
	return true;
}

void Candy::Draw(float dt)
{
	animation->speed = 10.f*dt;
	//App->render->Blit(, pos.x, pos.y, 1,1,false, &animation->GetCurrentFrame());
}