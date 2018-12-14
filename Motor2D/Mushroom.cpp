#include "Mushroom.h"
#include "Player.h"

Mushroom::Mushroom(int x, int y) : Entity(x, y)
{
	type = MUSHROOM;

	idle.PushBack({ 249, 0, 82, 90 });
	idle.PushBack({ 166, 0, 82, 90 });
	idle.PushBack({ 83, 0, 82, 90 });
	idle.PushBack({ 0, 0, 82, 90 });
	idle.loop = true;
	idle.speed = 3.f;

	walk.PushBack({ 249, 96, 82, 90 });
	walk.PushBack({ 166, 96, 82, 90 });
	walk.PushBack({ 83, 96, 82, 90 });
	walk.PushBack({ 0, 96, 82, 90 });
	walk.loop = true;
	walk.speed = 8.f;

	collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 50, 60}, COLLIDER_ENEMY, (j1Module*)App->entitymanager);
	death_collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 40, 10 }, COLLIDER_DEATH, (j1Module*)App->entitymanager);
}
				
Mushroom::~Mushroom()
{
	//App->tex->UnLoad(sprites);
}

bool Mushroom::Awake(pugi::xml_node& config)
{
	pugi::xml_node player = config.child("mushroom");

	speed = player.child("speed").attribute("value").as_float();
	move = player.child("move").attribute("value").as_bool();
	attack = player.child("attack").attribute("value").as_bool();
	x_scale = player.child("scale").attribute("value").as_float();
	y_scale = player.child("scale").attribute("value").as_float();
	alert_radius = player.child("alert_radius").attribute("value").as_float();
	gravity = player.child("gravity").attribute("value").as_float();

	return true;
}

void Mushroom::MoveEntity(float dt)
{
	if (alive)
	{

		pos = original_pos;

		original_pos.y += gravity * dt;

		iPoint EnemyPos = { (int)original_pos.x, (int)original_pos.y };
		iPoint PlayerPos = { (int)App->entitymanager->player_entity->pos.x, (int)App->entitymanager->player_entity->pos.y };

		if (EnemyPos.x - PlayerPos.x < alert_radius)
		{

		}


		if (abs(PlayerPos.x - EnemyPos.x) < alert_radius)
		{
			counter = 0;

			App->pathfinding->CreatePath(EnemyPos, PlayerPos);
			App->pathfinding->BackTracking(PlayerPos, path);

			move = true;
		}
		if (move)
		{
			iPoint Destination = { path[counter].x, path[counter].y };
			animation = &walk;

			if (EnemyPos.x < Destination.x)
			{
				original_pos.x += speed * dt;
				flip = true;
				if (EnemyPos.x >= Destination.x)
				{
					counter++;
					move = false;
				}
			}

			else
			{
				original_pos.x -= speed * dt;
				flip = false;
				if (EnemyPos.x <= Destination.x)
				{
					counter++;
					move = false;
				}
			}


			if (EnemyPos.x != Destination.x && EnemyPos.y != Destination.y)
			{
				move = false;
			}

		}
		else
		{
			animation = &idle;
		}

		if (abs(App->entitymanager->player_entity->pos.x - EnemyPos.x) >= alert_radius)
		{
			move = false;
		}

		collider->SetPos((int)pos.x + 10, (int)pos.y + 20);
		death_collider->SetPos((int)pos.x + 15, (int)pos.y + 10);
	}

}

void Mushroom::Draw(float dt)
{
	if (alive)
	{
		App->render->Blit(App->entitymanager->GetEntityAtlas(), pos.x, pos.y, x_scale, y_scale, flip, &(animation->GetCurrentFrame()));
	}
}

bool Mushroom::Load(pugi::xml_node& data)
{
	original_pos.x = data.attribute("x").as_float();
	original_pos.y = data.attribute("y").as_float();
	
	return true;
}

bool Mushroom::Save(pugi::xml_node& data) const
{
	pugi::xml_node playernode = data.append_child("position");
	playernode.append_attribute("x") = original_pos.x;
	playernode.append_attribute("y") = original_pos.y;

	return true;
}

void Mushroom::OnCollision()
{
	alive = false;
}
