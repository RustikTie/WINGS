#include "Mushroom.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Input.h"

Mushroom::Mushroom(int x, int y) : Entity(x, y)
{

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

	return true;
}

void Mushroom::MoveEntity(float dt)
{

}

void Mushroom::Draw(float dt)
{

}