#include "Player.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Input.h"
#include "j1Audio.h"
#include "j1GUIManager.h"
#include "Widgets.h"
#include "Text.h"

Player::Player(int x, int y) : Entity(x, y)
{
	//IDLE
	idle.PushBack({ 67, 196, 66, 92 });
	idle.PushBack({ 0, 196, 66, 92 });
	idle.loop = true;
	idle.speed = 2.f;

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
	walk.speed = 12.f;

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

	// PLAYER DATA
	pos.x = player.child("position").attribute("x").as_float();
	pos.y = player.child("position").attribute("y").as_float();
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
	death_border = player.child("death_border").attribute("value").as_float();
	lives = player.child("lives").attribute("value").as_int();

	collider = App->collisions->AddCollider({ (int)pos.x, (int)pos.y, 72, 97 }, COLLIDER_PLAYER, (j1Module*)App->entitymanager);

	// SFX
	walk_fx = App->audio->LoadFx("audio/fx/Walk.wav");
	jump_fx = App->audio->LoadFx("audio/fx/Jump.wav");
	glide_fx = App->audio->LoadFx("audio/fx/Glide.wav");
	death_fx = App->audio->LoadFx("audio/fx/Death.wav");

	//	GUI
	if (score == 0)
	{
		App->gui->AddImage(850, 10, IMAGE, true, rect_score, 0.5f);

		sprintf_s(score_text, 10, "%i", score);
		score_counter = App->gui->AddText(900, 24, TEXT, true, score_text, 0);
	}

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
		if (!jumping && !gliding && !falling)
			App->audio->PlayFx(walk_fx);
	}

	//BACKWARD
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		pos.x -= speed * dt;
		current_anim = &walk;
		flip = true;
		if (!jumping && !gliding && !falling)
			App->audio->PlayFx(walk_fx);

	}

	//IDLE
	else
	{
		current_anim = &idle;
	}

	//JUMP & GLIDE
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && !falling && !godmode)
	{
		jumping = true;
		max_height = (pos.y - jump_height);
		App->audio->PlayFx(jump_fx);

	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && falling && !godmode)
	{
		if (!gliding)
		{
			App->audio->PlayFx(glide_fx);

		}
		gliding = true;
		jumping = false;
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		gliding = false;
	}
	
	
	//JUMP & GLIDE SIDEWAYS

	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		if (!godmode)
		{
			godmode = true;
			old_grav = gravity;
			gravity = 0;
		}
		else
		{
			godmode = false;
			gravity = old_grav;
		}
	}

	if (godmode)
	{
		
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			pos.y -= speed * dt;
			current_anim = &idle;
		}
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			pos.y += speed * dt;
			current_anim = &idle;
		}
	}
	


	//DEATH
	if (pos.y > death_border)
	{
		pos.x = original_pos.x;
		pos.y = original_pos.y;
		lives -= 2;
		LOG("dead");
		App->audio->PlayFx(death_fx);

	}
	//CAMERA

	App->render->camera.x = (-pos.x + 400);
	App->render->camera.y = (-pos.y + 400);

	current_anim->speed = 100.f*dt;


	if (lives <= 0)
	{
		App->scene->menu = true;
		App->scene->level1 = false;
		App->scene->level2 = false;
		App->scene->Start();
	}
	

	
}

void Player::Jump_Glide(float dt)
{
	if (!jumping && !gliding)
	{
		pos.y += gravity*dt;
	}
	if (gliding)
	{
		pos.y += gravity * dt / 2;
	}
	if (jumping && pos.y > max_height)
	{
		//animation = &jump;
		pos.y -= jump_speed * dt;
	}
	if (pos.y <= max_height)
	{
		jumping = false;
	}
}

void Player::Draw(float dt)
{
	App->render->Blit(graphics, pos.x, pos.y, x_scale, y_scale, flip, &(current_anim->GetCurrentFrame()));
	collider->SetPos(pos.x, pos.y);
	App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 395, pos.y - 392, 1.f, 1.f, false, &character);

	switch (lives)
	{
	case 6:
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 230, pos.y - 390, 1.f, 1.f, false, &life);
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 340, pos.y - 390, 1.f, 1.f, false, &life);
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 285, pos.y - 390, 1.f, 1.f, false, &life);
		break;
	case 5:
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 230, pos.y - 390, 1.f, 1.f, false, &half);
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 285, pos.y - 390, 1.f, 1.f, false, &life);
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 340, pos.y - 390, 1.f, 1.f, false, &life);
		break;
	case 4:
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 230, pos.y - 390, 1.f, 1.f, false, &empty);
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 285, pos.y - 390, 1.f, 1.f, false, &life);
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 340, pos.y - 390, 1.f, 1.f, false, &life);
		break;
	case 3:
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 230, pos.y - 390, 1.f, 1.f, false, &empty);
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 285, pos.y - 390, 1.f, 1.f, false, &half);
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 340, pos.y - 390, 1.f, 1.f, false, &life);
		break;
	case 2:
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 230, pos.y - 390, 1.f, 1.f, false, &empty);
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 285, pos.y - 390, 1.f, 1.f, false, &empty);
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 340, pos.y - 390, 1.f, 1.f, false, &life);
		break;
	case 1:
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 230, pos.y - 390, 1.f, 1.f, false, &empty);
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 285, pos.y - 390, 1.f, 1.f, false, &empty);
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 340, pos.y - 390, 1.f, 1.f, false, &half);
		break;
	case 0: 
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 230, pos.y - 390, 1.f, 1.f, false, &empty);
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 285, pos.y - 390, 1.f, 1.f, false, &empty);
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x - 340, pos.y - 390, 1.f, 1.f, false, &empty);
		break;
	}

	UpdateScore();

}

bool Player::Load(pugi::xml_node& data)
{
	pos.x = data.child("player").attribute("x").as_float();
	pos.y = data.child("player").attribute("y").as_float();
	lives = data.child("player").attribute("lives").as_int();
	score = data.child("player").attribute("score").as_int();
	if (App->scene->level1 != data.child("player").attribute("map1").as_bool())
	{
		App->scene->ChangeMap(pos.x, pos.y);
	}
	App->scene->level1 = data.child("player").attribute("map1").as_bool();
	App->scene->level2 = data.child("player").attribute("map2").as_bool();


	return true;
}

bool Player::Save(pugi::xml_node& data) const
{
	pugi::xml_node playernode = data.append_child("player");
	playernode.append_attribute("x") = pos.x;
	playernode.append_attribute("y") = pos.y;
	playernode.append_attribute("lives") = lives;
	playernode.append_attribute("score") = score;
	playernode.append_attribute("map1") = App->scene->level1;
	playernode.append_attribute("map2") = App->scene->level2;

	return true;
}

void Player::OnCollision()
{

}

void Player::UpdateScore()
{
	sprintf_s(score_text, 10, "%i", score);
	score_counter->EditText(score_text);
}