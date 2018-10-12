#include "Player.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Input.h"

Player::Player(int x, int y) : Entity(x, y)
{
	//IDLE
	idle.PushBack({ 67, 196, 66, 92 });
	idle.loop = false;
	idle.speed = 10.f;

	current_anim = &idle;
}

Player::~Player()
{
	App->tex->UnLoad(graphics);
}

bool Player::Start()
{
	LOG("Loading Player");

	graphics = App->tex->Load("textures/p1_spritesheet.png");

	return true;
}

bool Player::Awake(pugi::xml_node& config)
{
	pugi::xml_node player = config.child("player");

	original_pos.x = player.child("position").attribute("x").as_float();
	original_pos.y = player.child("position").attribute("y").as_float();
	speed = player.child("speed").attribute("value").as_float();
	gravity = player.child("gravity").attribute("value").as_float();
	acceleration = player.child("acceleration").attribute("value").as_float();
	deceleration = player.child("deceleration").attribute("value").as_float();
	jump_height = player.child("jump_height").attribute("value").as_float();
	jump_speed = player.child("jump_speed").attribute("value").as_float();
	x_scale = player.child("scale").attribute("x").as_float();
	y_scale = player.child("scale").attribute("y").as_float();

	return true;
}

void Player::MoveEntity(float dt)
{
	current_anim = &idle;
	//FORWARD
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		original_pos.x = +speed;
		//LOG("pos = %f", original_pos.x);
	}

	//BACKWARD
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		original_pos.x = -speed;
	}

	//JUMP & GLIDE
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && !falling)
	{
		jumping = true;
		jump_height = (pos.y - jump_height);
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		gliding = true;
		jumping = false;
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		gliding = false;
	}
}

void Player::Jump_Glide(float dt)
{
	if (!jumping && !godmode && !gliding)
	{
		pos.y += gravity * dt;
	}
	if (gliding)
	{
		pos.y += gravity * dt / 5;
	}
	if (jumping && pos.y > jump_height)
	{
		//animation = &jump;
		pos.y -= jump_speed*gravity * dt;
	}
	else if (pos.y <= jump_height)
	{
		jumping = false;
	}
}

void Player::Draw(float dt)
{
	App->render->Blit(graphics, pos.x, pos.y, x_scale, y_scale, flip, &(current_anim->GetCurrentFrame()));
}

bool Player::Load(pugi::xml_node&)
{
	return true;
}

bool Player::Save(pugi::xml_node&) const
{
	return true;
}