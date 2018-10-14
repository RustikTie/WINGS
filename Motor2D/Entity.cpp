#include "j1Module.h"
#include "Entity.h"
#include "j1EntityManager.h"
#include "j1Textures.h"



Entity::Entity(int x, int y) : pos(x, y), original_pos(x, y), collider_pos(0, 0)
{

}

bool Entity::Awake(pugi::xml_node& entity)
{
	Awake(entity);

	return true;
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

void Entity::Draw(float dt)
{


	/*if (animation != nullptr)
	{

	App->render->Blit(sprite, pos.x, pos.y, x_scale, y_scale, flip, &(animation->GetCurrentFrame()));

	}*/
	
	if (collider != nullptr)
	{
	collider->SetPos(pos.x, pos.y);
	}

	if (collider->type == COLLIDER_PLAYER)
	{
	collider->SetPos(pos.x + 10, pos.y + 50);

	}
	
	/*for (int i = 0; App->entity_manager->entities[i]; ++i)
	{
	App->entity_manager->entities[i]->collider->SetPos(App->entity_manager->entities[i]->pos.x, App->entity_manager->entities[i]->pos.y);
	App->render->Blit(App->entity_manager->entities[i]->texture, App->entity_manager->entities[i]->pos.x, App->entity_manager->entities[i]->pos.y, 1, 1, false, &App->entity_manager->entities[i]->animation->GetCurrentFrame());
	}*/
}

void Entity::OnCollision(Collider* c)
{
	if (collider->type == COLLIDER_PLAYER)
	{

	}
}