#include "Beetle.h"

Beetle::Beetle(int x, int y) : Entity(x, y)
{
	collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 82, 95 }, COLLIDER_ENEMY, (j1Module*)App->entitymanager);
}

Beetle::~Beetle()
{
	App->tex->UnLoad(sprites);
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

	return true;
}

void Beetle::MoveEntity(float dt)
{
	pos = original_pos;
	original_pos.y += App->entitymanager->player_entity->gravity*dt;

	iPoint EnemyPos = { (int)original_pos.x, (int)original_pos.y };
	iPoint PlayerPos = { (int)App->entitymanager->player_entity->pos.x, (int)App->entitymanager->player_entity->pos.y };

	if (abs(PlayerPos.x - EnemyPos.x) < alert_radius && !move)
	{
		counter = 0;

		App->pathfinding->CreatePath(EnemyPos, PlayerPos);
		App->pathfinding->BackTrackingGround(PlayerPos, path);

		move = true;
	}

	if (move)
	{
		iPoint Destination = { path[counter].x, path[counter].y };

		animation = &fly;

		if (EnemyPos.x < Destination.x)
		{
			original_pos.x += speed*dt;
			flip = true;
			if (EnemyPos.x >= Destination.x)
			{
				counter++;
				move = false;
			}
		}

		else
		{
			original_pos.x -= speed*dt;
			flip = false;
			if (EnemyPos.x <= Destination.x)
			{
				counter++;
				move = false;
			}
		}

		if (EnemyPos.y < Destination.y)
		{
			original_pos.y += speed*dt;
			if (EnemyPos.y >= Destination.y)
			{
				counter++;
				move = false;
			}
		}

		else
		{
			original_pos.y -= speed*dt;
			if (EnemyPos.y < Destination.y)
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
}

void Beetle::Draw(float dt)
{

}

bool Beetle::Load(pugi::xml_node& data)
{

	return true;
}

bool Beetle::Save(pugi::xml_node& data) const
{
	
	return true;
}