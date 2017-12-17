#include "Candy.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "j1EntityManager.h"

Candy::Candy(int x, int y, int score): Entity(x,y)
{
	this->score = score;
	if (score == 100)
	{
		idle.PushBack({ 339, 294, 52, 50 });
		idle.PushBack({ 392, 294, 52, 50 });
		explosion.PushBack({ 444, 294, 52, 50 });
		explosion.PushBack({ 497, 294, 52, 50 });
		explosion.PushBack({ 339, 345, 52, 50 });
		explosion.PushBack({ 392, 345, 52, 50 });
		explosion.PushBack({ 444, 345, 52, 50 });
	}
	else if (score == 500)
	{
		idle.PushBack({ 0, 397, 52, 50 });
		idle.PushBack({ 53, 397, 52, 50 });
		explosion.PushBack({ 106, 397, 52, 50 });
		explosion.PushBack({ 158, 397, 52, 50});
		explosion.PushBack({ 0, 448, 52, 50 });
		explosion.PushBack({ 53, 448, 52, 50 });
		explosion.PushBack({ 444, 345, 52, 50 });
	}
	else if (score == 1000)
	{
		idle.PushBack({ 0, 499, 52, 50 });
		idle.PushBack({ 53, 499, 52, 50 });
		explosion.PushBack({ 106, 499, 52, 50 });
		explosion.PushBack({ 158, 499, 52, 50 });
		explosion.PushBack({ 0, 550, 52, 50 });
		explosion.PushBack({ 53, 550, 52, 50 });
		explosion.PushBack({ 444, 345, 52, 50 });
	}
	animation = &idle;
	alive = true;	
	explosion.loop = false;
	collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 50, 50 }, COLLIDER_CANDY, (j1Module*)App->entity_manager);
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
	animation->speed = 5.f*dt;
	
	if (grabbed == false)
	{
		collider->SetPos(pos.x, pos.y);
		App->render->Blit(App->entity_manager->GetEntityAtlas(), pos.x, pos.y, 1, 1, false, &(animation->GetCurrentFrame()));
	}
	if (grabbed == true && alive == true)
	{
		animation = &explosion;
		App->render->Blit(App->entity_manager->GetEntityAtlas(), pos.x, pos.y, 1, 1, false, &(animation->GetCurrentFrame()));
		if(animation->Finished() == true)
		{
			alive = false;
		}
	}
	
}

void Candy::OnCollision()
{
	grabbed = true;
	App->entity_manager->player_entity->score += score;
	App->entity_manager->player_entity->candiesGrabbed += 1;
	LOG("SCORE: %d, CANDIES: %d", App->entity_manager->player_entity->score , App->entity_manager->player_entity->candiesGrabbed);
}