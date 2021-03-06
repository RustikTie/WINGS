#include "Beetle.h"
#include "Player.h"

Beetle::Beetle(int x, int y) : Entity(x, y)
{
	type = BEETLE;

	idle.PushBack({ 8, 188, 128, 116 });
	idle.PushBack({ 173, 188, 128, 116 });
	idle.PushBack({ 327, 188, 128, 116 });
	idle.loop = true;
	idle.speed = 3.f;

	fly.PushBack({ 8, 318, 128, 116 });
	fly.PushBack({ 154, 318 , 128, 116 });
	fly.PushBack({ 296, 318 , 128, 116 });
	fly.loop = true;
	fly.speed = 8.f;

	collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y+50, 128, 60 }, COLLIDER_ENEMY, (j1Module*)App->entitymanager);
	death_collider = App->collisions->AddCollider({ (int)pos.x+5, (int)pos.y+45, 118, 10 }, COLLIDER_DEATH, (j1Module*)App->entitymanager);

}

Beetle::~Beetle()
{
	//App->tex->UnLoad(sprites);
}

bool Beetle::Awake(pugi::xml_node& config)
{
	pugi::xml_node player = config.child("beetle");

	speed = player.child("speed").attribute("value").as_float();
	move = player.child("move").attribute("value").as_bool();
	attack = player.child("attack").attribute("value").as_bool();
	x_scale = player.child("scale").attribute("value").as_float();
	y_scale = player.child("scale").attribute("value").as_float();
	alert_radius = player.child("alert_radius").attribute("value").as_float();
	gravity = player.child("gravity").attribute("value").as_float();

	return true;
}

void Beetle::MoveEntity(float dt)
{
	if (alive)
	{
		pos = original_pos;

		iPoint EnemyPos = { (int)original_pos.x, (int)original_pos.y };
		iPoint PlayerPos = { (int)App->entitymanager->player_entity->pos.x, (int)App->entitymanager->player_entity->pos.y };

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

			animation = &fly;
			//x
			if (EnemyPos.x < Destination.x + 50)
			{
				original_pos.x += speed * dt;
				flip = true;
				if (EnemyPos.x >= Destination.x + 50)
				{
					counter++;
					move = false;
				}
			}

			if (EnemyPos.x > Destination.x - 50)
			{
				original_pos.x -= speed * dt;
				flip = false;
				if (EnemyPos.x <= Destination.x - 50)
				{
					counter++;
					move = false;
				}
			}
			//y
			if (EnemyPos.y < Destination.y + 50)
			{
				original_pos.y += speed * dt;
				if (EnemyPos.y >= Destination.y + 50)
				{
					counter++;
					move = false;
				}
			}

			if (EnemyPos.y > Destination.y - 50)
			{
				original_pos.y -= speed * dt;
				if (EnemyPos.y <= Destination.y - 50)
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
			animation = &fly;
		}

		if (abs(App->entitymanager->player_entity->pos.x - EnemyPos.x) >= alert_radius)
		{
			move = false;
		}
		collider->SetPos(pos.x, pos.y + 50);
		death_collider->SetPos(pos.x + 5, pos.y + 40);
	}

}

void Beetle::Draw(float dt)
{
	if (alive)
	{

		App->render->Blit(App->entitymanager->GetEntityAtlas(), pos.x, pos.y, x_scale, y_scale, flip, &(animation->GetCurrentFrame()));
	}
	
}

bool Beetle::Load(pugi::xml_node& data)
{
	original_pos.x = data.attribute("x").as_float();
	original_pos.y = data.attribute("y").as_float();
	return true;
}

bool Beetle::Save(pugi::xml_node& data) const
{
	pugi::xml_node playernode = data.append_child("position");
	playernode.append_attribute("x") = original_pos.x;
	playernode.append_attribute("y") = original_pos.y;
	return true;
}

void Beetle::OnCollision()
{
	alive = false;
}