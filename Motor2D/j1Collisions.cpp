#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collisions.h"
#include "j1EntityManager.h"
#include "Entity.h"
#include "Player.h"
#include "j1Scene.h"
#include "j1Pathfinding.h"
#include "j1Audio.h"
#include "Brofiler\Brofiler.h"
#include "Mushroom.h"
#include "Beetle.h"

j1Collisions::j1Collisions() : j1Module()
{
	name.create("colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_GROUND][COLLIDER_GROUND] = false;
	matrix[COLLIDER_GROUND][COLLIDER_WALL] = false;
	matrix[COLLIDER_GROUND][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_GROUND][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_GROUND][COLLIDER_BLOCKER] = false;
	matrix[COLLIDER_GROUND][COLLIDER_PICK_UP] = false;
	matrix[COLLIDER_GROUND][COLLIDER_DEATH] = false;

	matrix[COLLIDER_WALL][COLLIDER_GROUND] = false;
	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_BLOCKER] = false;
	matrix[COLLIDER_WALL][COLLIDER_PICK_UP] = false;
	matrix[COLLIDER_WALL][COLLIDER_DEATH] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_GROUND] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_BLOCKER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PICK_UP] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_DEATH] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_GROUND] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_BLOCKER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PICK_UP] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_DEATH] = false;

	matrix[COLLIDER_BLOCKER][COLLIDER_GROUND] = false;
	matrix[COLLIDER_BLOCKER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BLOCKER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_BLOCKER][COLLIDER_BLOCKER] = false;
	matrix[COLLIDER_BLOCKER][COLLIDER_PICK_UP] = false;
	matrix[COLLIDER_BLOCKER][COLLIDER_DEATH] = false;

	matrix[COLLIDER_PICK_UP][COLLIDER_GROUND] = false;
	matrix[COLLIDER_PICK_UP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_PICK_UP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_PICK_UP][COLLIDER_BLOCKER] = false;
	matrix[COLLIDER_PICK_UP][COLLIDER_PICK_UP] = false;
	matrix[COLLIDER_PICK_UP][COLLIDER_DEATH] = false;

	matrix[COLLIDER_DEATH][COLLIDER_GROUND] = false;
	matrix[COLLIDER_DEATH][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_DEATH][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_DEATH][COLLIDER_BLOCKER] = false;
	matrix[COLLIDER_DEATH][COLLIDER_PICK_UP] = false;
	matrix[COLLIDER_DEATH][COLLIDER_DEATH] = false;

}

// Destructor
j1Collisions::~j1Collisions()
{

}

bool j1Collisions::Awake()
{
	LOG("Loading Scene");


	bool ret = true;

	return ret;
}

bool j1Collisions::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdate Collisions", Profiler::Color::Yellow)

		// Remove all colliders scheduled for deletion
		for (uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			if (colliders[i] != nullptr && colliders[i]->to_delete == true)
			{
				delete colliders[i];
				colliders[i] = nullptr;
			}
		}

	return true;
}

// Called before render is available
bool j1Collisions::Update(float dt)
{
	BROFILER_CATEGORY("Update Collisions", Profiler::Color::Green)

	Collider* c;
	if (App->entitymanager->player_entity != nullptr)
	{
		App->entitymanager->player_entity->falling = true;


		//PLAYER COLLISIONS
		for (uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			// skip empty and player colliders
			if (colliders[i] == nullptr || colliders[i]->type == COLLIDER_NONE || colliders[i]->type == COLLIDER_PLAYER)
				continue;

			if (colliders[i]->type == COLLIDER_WALL)
			{
				if (colliders[i]->CheckCollision(App->entitymanager->player_entity->collider->rect) == true)
				{
					if (App->entitymanager->player_entity->collider->rect.x + App->entitymanager->player_entity->collider->rect.w >= colliders[i]->rect.x + colliders[i]->rect.w)
					{
						App->entitymanager->player_entity->pos.x += App->entitymanager->player_entity->speed*dt;
					}
					else if (App->entitymanager->player_entity->collider->rect.x <= colliders[i]->rect.x + colliders[i]->rect.w)
					{
						App->entitymanager->player_entity->pos.x -= App->entitymanager->player_entity->speed*dt;
					}
				}
			}

			if (colliders[i]->type == COLLIDER_GROUND)
			{
				if (colliders[i]->CheckCollision(App->entitymanager->player_entity->collider->rect) == true)
				{
					if (App->entitymanager->player_entity->collider->rect.y + App->entitymanager->player_entity->collider->rect.h >= colliders[i]->rect.y)
					{
						colliders[i]->SetCollisionOffset(App->entitymanager->player_entity->collider->rect, App->entitymanager->player_entity->gravity);
						/*if (App->entitymanager->player_entity->pos.y + App->entitymanager->player_entity->collider->rect.h > colliders[i]->rect.y+1)
						{
							App->entitymanager->player_entity->pos.y -= colliders[i]->rect.y*dt;
						}
						*/
						App->entitymanager->player_entity->pos.y -= colliders[i]->col_offset*dt;
						App->entitymanager->player_entity->falling = false;
						App->entitymanager->player_entity->gliding = false;
					}
				}

			}

			//if (colliders[i]->type == COLLIDER_DEATH)
			//{
			//	if (colliders[i]->CheckCollision(App->entitymanager->player_entity->collider->rect) == true && !App->entitymanager->player_entity->godmode)
			//	{
			//		int j = 0;
			//		while (App->entitymanager->entities[j] != NULL)
			//		{
			//			if (App->entitymanager->entities[j]->death_collider = colliders[i])
			//			{
			//				colliders[i]->SetCollisionOffset(App->entitymanager->player_entity->collider->rect, App->entitymanager->player_entity->gravity);
			//				//App->entitymanager->entities[j]->OnCollision();
			//				App->entitymanager->player_entity->pos.y -= colliders[i]->col_offset*dt;
			//				App->entitymanager->entities[j]->collider->to_delete = true;
			//				colliders[i]->to_delete = true;

			//				//App->entitymanager->player_entity->jumping = true;
			//			}
			//			++j;
			//		}
			//	}
			//}

			if (colliders[i]->type == COLLIDER_ENEMY)
			{
				if (colliders[i]->CheckCollision(App->entitymanager->player_entity->collider->rect) == true && !App->entitymanager->player_entity->godmode)
				{
					App->entitymanager->player_entity->SetPos(500, 1000);
					App->audio->PlayFx(App->entitymanager->player_entity->death_fx);
					App->entitymanager->player_entity->lives -= 1;

				}
			}

			

			if (colliders[i]->type == COLLIDER_PICK_UP)
			{
				if (colliders[i]->CheckCollision(App->entitymanager->player_entity->collider->rect) == true)
				{
					p2List_item<Entity*>* item;
					item = App->entitymanager->coins.start;

					while (item != NULL)
					{
						if (colliders[i] == item->data->collider)
						{
							item->data->OnCollision();
							colliders[i]->to_delete = true;
						}
						item = item->next;
					}
				}
			}

			//ENEMY COLLISIONS
			for (uint j = 0; j < MAX_ENEMIES; j++)
			{
				if (App->entitymanager->entities[j] != nullptr && colliders[i] != nullptr)
				{
					if (colliders[i]->type == COLLIDER_WALL || colliders[i]->type == COLLIDER_BLOCKER)
					{
						if (colliders[i]->CheckCollision(App->entitymanager->entities[j]->collider->rect) == true)
						{
							if (App->entitymanager->entities[j]->collider->rect.x + App->entitymanager->entities[j]->collider->rect.w >= colliders[i]->rect.x + colliders[i]->rect.w)
							{
								App->entitymanager->entities[j]->original_pos.x += App->entitymanager->entities[j]->speed*dt;
							}
							else if (App->entitymanager->entities[j]->collider->rect.x <= colliders[i]->rect.x + colliders[i]->rect.w)
							{
								App->entitymanager->entities[j]->original_pos.x -= App->entitymanager->entities[j]->speed*dt;
							}
						}
					}

					if (colliders[i]->type == COLLIDER_GROUND)
					{
						if (colliders[i]->CheckCollision(App->entitymanager->entities[j]->collider->rect) == true)
						{
							if (App->entitymanager->entities[j]->collider->rect.y + App->entitymanager->entities[j]->collider->rect.h >= colliders[i]->rect.y)
							{
								colliders[i]->SetCollisionOffset(App->entitymanager->entities[j]->collider->rect, App->entitymanager->entities[j]->gravity);
								App->entitymanager->entities[j]->original_pos.y -= colliders[i]->col_offset*dt;

							}
						}

					}
				}
			}
		}
	}

	DebugDraw();

	return true;
}

void j1Collisions::DebugDraw()
{
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		LOG("You can see the colliders");
		debug = !debug;
	}

	if (debug == false) {
		return;
	}
	else {

		Uint8 alpha = 255;
		for (uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			if (colliders[i] == nullptr)
				continue;

			switch (colliders[i]->type)
			{
			case COLLIDER_NONE: // white
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha, false);
				break;
			case COLLIDER_GROUND: // blue
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha, false);
				break;
			case COLLIDER_WALL: // pink
				App->render->DrawQuad(colliders[i]->rect, 255, 91, 165, alpha, false);
				break;
			case COLLIDER_PLAYER: // green
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha, false);
				break;
			case COLLIDER_ENEMY: // yellow
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha, false);
				break;
			case COLLIDER_BLOCKER: // orange
				App->render->DrawQuad(colliders[i]->rect, 229, 83, 0, alpha, false);
				break;
			case COLLIDER_PICK_UP: // red
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha, false);
				break;
			case COLLIDER_DEATH: // black
				App->render->DrawQuad(colliders[i]->rect, 0,0,0, alpha, false);
			}
		}

		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (App->entitymanager->entities[i] != nullptr)
			{
				App->pathfinding->DrawPath(App->entitymanager->entities[i]->path);
			}
		}

	}
}

bool j1Collisions::checkColisionList(Collider * enemCollider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] == nullptr)
			continue;
		if (enemCollider->CheckCollision(colliders[i]->rect))
			return true;
	}
	return false;
}

// Called before quitting
bool j1Collisions::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* j1Collisions::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

bool j1Collisions::EraseCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			return true;
		}
	}

	return false;
}

void j1Collisions::Erase_Non_Player_Colliders()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->type != COLLIDER_PLAYER)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}
// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r)const
{
	
		if (r.y + r.h > rect.y - 2 && r.y < rect.y + rect.h && r.x + r.w >= rect.x  && r.x <= rect.x + rect.w)
		{
			return true;
		}

		else
		{
			return false;
		}
	
}

void Collider::SetCollisionOffset(const SDL_Rect& r, int speed)
{
	col_offset = r.y + r.h + speed - rect.y - 2;
}