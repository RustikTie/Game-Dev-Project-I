#include "Entity.h"



Entity::Entity(int x, int y)
{
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
	if (collider != nullptr)
		collider->SetPos(pos.x, pos.y);

	if (animation != nullptr)
	{
		App->render->Blit(sprites, pos.x, pos.y, 0, 0, false, &(animation->GetCurrentFrame()));
	}
}

void Entity::OnCollision(Collider* collider)
{


}

