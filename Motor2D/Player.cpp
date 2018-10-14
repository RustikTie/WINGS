#include "Player.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Input.h"

Player::Player(int x, int y) : Entity(x, y)
{
	//IDLE
	idle.PushBack({ 67, 196, 66, 92 });
	idle.PushBack({ 0, 196, 66, 92 });
	idle.loop = true;
	idle.speed = 0.00003f;

	walk.PushBack({ 0, 0, 72, 97 });
	walk.PushBack({ 73, 0, 72, 97 });
	walk.PushBack({ 146 , 0, 72, 97 });
	walk.PushBack({ 0, 98 , 72, 97 });
	walk.PushBack({ 73 , 98 , 72, 97 });
	walk.PushBack({ 146, 98 , 72, 97 });
	walk.PushBack({ 219, 0, 72, 97 });
	walk.PushBack({ 292, 0, 72, 97 });
	walk.PushBack({ 219, 98, 72, 97 });
	walk.PushBack({ 365, 0, 72, 97 });
	walk.PushBack({ 292, 98, 72, 97 });
	walk.loop = true;
	walk.speed = 0.00015f;

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
	collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 72, 97 }, COLLIDER_PLAYER, (j1Module*)App->entitymanager);

	return true;
}

bool Player::Awake(pugi::xml_node& config)
{
	pugi::xml_node player = config.child("player");

	/*pos.x = player.child("position").attribute("x").as_float();
	pos.y = player.child("position").attribute("y").as_float();*/
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
	//FORWARD
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		pos.x += speed * dt;
		current_anim = &walk;
		flip = false;
	}

	//BACKWARD
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		pos.x -= speed * dt;
		current_anim = &walk;
		flip = true;
	}

	//IDLE
	else
	{
		current_anim = &idle;
	}

	//JUMP & GLIDE
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && !falling)
	{
		jumping = true;
		max_height = (pos.y - jump_height);
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
	
	
	//JUMP & GLIDE SIDEWAYS
	


	//GODMODE
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		if (!godmode)
		{
			godmode = true;
		}
		else
		{
			godmode = false;
		}
	}

	if (!godmode)
	{
		Jump_Glide(dt); 
	}

	//CAMERA
	App->render->camera.x = (-pos.x + 400);
	App->render->camera.y = (-pos.y + 400);
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
	if (jumping && pos.y > max_height)
	{
		//animation = &jump;
		pos.y -= jump_speed * dt;
	}
	else if (pos.y <= max_height)
	{
		falling = true;
		jumping = false;
	}
}

void Player::Draw(float dt)
{
	App->render->Blit(graphics, pos.x, pos.y, x_scale, y_scale, flip, &(current_anim->GetCurrentFrame()));
	collider->SetPos(pos.x + 10, pos.y + 50);

}

bool Player::Load(pugi::xml_node& data)
{
	pos.x = data.child("player").attribute("x").as_float();
	pos.y = data.child("player").attribute("y").as_float();
	App->scene->level1 = data.child("player").attribute("map1").as_bool();
	App->scene->level2 = data.child("player").attribute("map2").as_bool();

	App->scene->ChangeMap(pos.x, pos.y);

	return true;
}

bool Player::Save(pugi::xml_node& data) const
{
	pugi::xml_node playernode = data.append_child("player");
	playernode.append_attribute("x") = pos.x;
	playernode.append_attribute("y") = pos.y;
	playernode.append_attribute("map1") = App->scene->level1;
	playernode.append_attribute("map2") = App->scene->level2;

	return true;
}