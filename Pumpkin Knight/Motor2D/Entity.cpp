#include "j1Module.h"
#include "Entity.h"
#include "j1EntityManager.h"
#include "j1Textures.h"



Entity::Entity(int x, int y) : j1Module()
{
	white_wolf = App->tex->Load("assets/WolfMedium.png");

}


Entity::~Entity()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Entity::GetCollider() const
{
	return collider;
}

void Entity::Draw(SDL_Texture* sprites)
{
	/*if (collider != nullptr)
		collider->SetPos(pos.x, pos.y);

	if (animation != nullptr)
	{
		App->render->Blit(sprites, pos.x, pos.y, 0, 0, false, &(animation->GetCurrentFrame()));
	}*/

	for (int i = 0; App->entity_manager->entities[i]; ++i)
	{
		App->entity_manager->entities[i]->collider->SetPos(App->entity_manager->entities[i]->pos.x, App->entity_manager->entities[i]->pos.y);
		App->render->Blit(App->entity_manager->entities[i]->texture, App->entity_manager->entities[i]->pos.x, App->entity_manager->entities[i]->pos.y, 1, 1, false, &App->entity_manager->entities[i]->animation->GetCurrentFrame());
	}
}

void Entity::OnCollision(Collider* collider)
{


}

