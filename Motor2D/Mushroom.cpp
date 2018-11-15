#include "Mushroom.h"

Mushroom::Mushroom(int x, int y) : Entity(x, y)
{
	collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 82, 95 }, COLLIDER_ENEMY, (j1Module*)App->entitymanager);
}
				
Mushroom::~Mushroom()
{
	App->tex->UnLoad(sprites);
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

	return true;
}

void Mushroom::MoveEntity(float dt)
{
	fPoint EnemyPos = { pos.x, pos.y };
	fPoint PlayerPos = { App->entitymanager->player_entity->pos.x, App->entitymanager->player_entity->pos.y };

	if (abs(PlayerPos.x - EnemyPos.x) < alert_radius)
	{

	}

}

void Mushroom::Draw(float dt)
{

}