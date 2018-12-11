#include "Coins.h"



Coins::Coins(int x, int y) : Entity(x,y)
{
	idle.PushBack({ 369, 51, 45, 44 });
	idle.PushBack({ 419, 51, 45, 44 });
	idle.PushBack({ 469, 51, 45, 44 });
	idle.PushBack({ 519, 51, 45, 44 });

	explosion.PushBack({ 2, 444, 117, 114 });
	explosion.PushBack({ 142, 444, 117, 114 });
	explosion.PushBack({ 277, 444, 117, 114 });
	explosion.loop = false;
	
	explosion.speed = 5.f;
	animation = &idle;
	alive = true;
	collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 50,50 }, COLLIDER_PICK_UP, (j1Module*)App->entitymanager);
}


Coins::~Coins()
{
}


bool Coins::Awake(pugi::xml_node&)
{
	return true;
}
void Coins::Draw(float dt)
{
	animation->speed *= dt;

	if (!grabbed)
	{
		collider->SetPos(pos.x, pos.y);
		App->render->Blit(App->entitymanager->GetEntityAtlas(), pos.x, pos.y, 1, 1, false, &(animation->GetCurrentFrame()));

	}

	if (grabbed && alive)
	{
		animation = &explosion;
		App->render->Blit(App->entitymanager->GetEntityAtlas(), pos.x, pos.y, 1, 1, false, &(animation->GetCurrentFrame()));
		if (animation->Finished() == true)
			alive = false;
	}

}
void Coins::OnCollision()
{
	grabbed = true;
	App->entitymanager->player_entity->score += score;
	App->entitymanager->player_entity->coins_grabbed += 1;

}
