#include "Player.h"
#include "j1Render.h"
#include "j1Scene.h"

Player::Player(int x, int y) : Entity(x, y)
{

}

Player::~Player()
{
	
}

bool Player::Start()
{
	LOG("Loading Player");

	//collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 18 * 3, 27 * 3 }, COLLIDER_PLAYER, (j1Module*)App->entity_manager);
	//sprites = App->tex->Load("assets/Pumpkin sprites.png");

	return true;
}

bool Player::Awake(pugi::xml_node& config)
{
	pugi::xml_node player = config.child("player");

	original_pos.x = player.child("position").attribute("x").as_float();
	original_pos.y = player.child("position").attribute("y").as_float();

	return true;
}