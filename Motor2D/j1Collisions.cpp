#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collisions.h"
//#include "j1EntityManager.h"
//#include "Entity.h"
//#include "Player.h"
#include "j1Scene.h"
//#include "Candy.h"
#include "Brofiler\Brofiler.h"

j1Collisions::j1Collisions() : j1Module()
{
	name.create("colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_GROUND][COLLIDER_GROUND] = false;
	matrix[COLLIDER_GROUND][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_GROUND][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_GROUND][COLLIDER_BLOCKER] = false;
	matrix[COLLIDER_GROUND][COLLIDER_GOD] = false;
	matrix[COLLIDER_GROUND][COLLIDER_CANDY] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_GROUND] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_BLOCKER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_GOD] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_CANDY] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_GROUND] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_BLOCKER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_GOD] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_CANDY] = false;

	matrix[COLLIDER_BLOCKER][COLLIDER_GROUND] = false;
	matrix[COLLIDER_BLOCKER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BLOCKER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_BLOCKER][COLLIDER_BLOCKER] = false;
	matrix[COLLIDER_BLOCKER][COLLIDER_GOD] = false;
	matrix[COLLIDER_BLOCKER][COLLIDER_CANDY] = false;

	matrix[COLLIDER_GOD][COLLIDER_GROUND] = false;
	matrix[COLLIDER_GOD][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_GOD][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_GOD][COLLIDER_BLOCKER] = false;
	matrix[COLLIDER_GOD][COLLIDER_GOD] = false;
	matrix[COLLIDER_GOD][COLLIDER_CANDY] = false;

	matrix[COLLIDER_CANDY][COLLIDER_GROUND] = false;
	matrix[COLLIDER_CANDY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_CANDY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_CANDY][COLLIDER_BLOCKER] = false;
	matrix[COLLIDER_CANDY][COLLIDER_GOD] = false;
	matrix[COLLIDER_CANDY][COLLIDER_CANDY] = false;
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

		Collider* c1;
	Collider* c2;

	float enemygravity;
	float force;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr || colliders[i]->type == COLLIDER_NONE)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			//GRAVITY PLAYER
			//if (c1->type == COLLIDER_GROUND && c2->type == COLLIDER_PLAYER && c1->CheckCollision(c2->rect) == true && !App->entity_manager->player_entity->godmode)
			//{
			//	App->entity_manager->player_entity->pos.y -= (App->entity_manager->player_entity->gravity)*dt;
			//	App->entity_manager->player_entity->falling = false;
			//	App->entity_manager->player_entity->contact = false;
			//	//App->entity_manager->OnCollision(c2, c1, enemygravity);
			//}
			//FOWARD and BACKWARD COLLISION PLAYER w/ WALL
			/*if (c1->type == COLLIDER_WALL && c2->type == COLLIDER_PLAYER && c1->CheckCollision(c2->rect) && !App->entity_manager->player_entity->godmode)
			{
				App->entity_manager->player_entity->pos.x -= (App->entity_manager->player_entity->speed)*dt;
			}*/
			//PLAYER ENEMY COLLISION
			/*if (c2->type == COLLIDER_ENEMY && c1->type == COLLIDER_PLAYER && c1->CheckCollision(c2->rect) && !App->entity_manager->player_entity->godmode)
			{

				if (App->entity_manager->player_entity->lives >= 0)
				{
					App->entity_manager->player_entity->lives -= 1;
					App->entity_manager->player_entity->SetPos(100, 200);
				}
			}*/
			//GRAVITY ENEMY
			/*if (c1->type == COLLIDER_GROUND && c2->type == COLLIDER_ENEMY && c1->CheckCollisionDownwards(c2->rect, enemygravity, dt) == true)
			{
				if (App->entity_manager->wolf)
				{
					App->entity_manager->OnCollision(c2, c1, enemygravity);
				}

			}*/

			//ENEMY BLOCKERS
			/*if (c1->type == COLLIDER_BLOCKER && c2->type == COLLIDER_ENEMY && c1->CheckCollisionDownwards(c2->rect, force, dt) == true)
			{
				if (App->entity_manager->wolf)
				{
					App->entity_manager->OnCollision(c2, c1, force);
				}

			}
			if (c1->type == COLLIDER_WALL && c2->type == COLLIDER_ENEMY && c1->CheckCollisionDownwards(c2->rect, force, dt) == true)
			{
				if (App->entity_manager->wolf)
				{
					App->entity_manager->OnCollision(c2, c1, force);
				}

			}
			if (c1->type == COLLIDER_CANDY && c2->type == COLLIDER_PLAYER && c1->CheckCollision(c2->rect) == true)
			{
				c1->to_delete = true;
				App->entity_manager->player_entity->score += 1;

			}
			if (c2->type == COLLIDER_CANDY && c1->type == COLLIDER_PLAYER && c2->CheckCollision(c1->rect) == true)
			{
				p2List_item<Entity*>* item;
				item = App->entity_manager->candies.start;
				while (item != NULL)
				{
					if (c2 == item->data->collider)
					{
						item->data->OnCollision();
						c2->to_delete = true;
					}
					item = item->next;
				}

			}*/
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
			case COLLIDER_CANDY: // red
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha, false);
				break;
			}
		}

		/*for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (App->entity_manager->entities[i] != nullptr)
			{
				App->pathfinding->DrawPath(App->entity_manager->entities[i]->path);
			}
		}*/

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

bool Collider::CheckCollision(const SDL_Rect& r) const
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

//Collisions between entitities

//bool Collider::CheckCollisionDownwards(const SDL_Rect& r, float& gravity, float dt)
//{
//	if (r.y + r.h > rect.y - 2 && r.y < rect.y + rect.h && r.x + r.w >= rect.x  && r.x <= rect.x + rect.w)
//	{
//		gravity = App->entity_manager->player_entity->gravity*dt;
//		return true;
//	}
//
//	else
//	{
//		return false;
//	}
//}
//
//bool Collider::CheckCollisionForward(const SDL_Rect& r, float& force, float dt)
//{
//	if (r.y + r.h  > rect.y && r.y + r.h < rect.y + rect.h && r.x + r.w >= rect.x && r.x + r.w < rect.x + rect.w)
//	{
//		force = App->entity_manager->player_entity->speed*dt;
//		return true;
//
//	}
//
//	else
//	{
//		return false;
//	}
//}
//
//bool Collider::CheckCollisionBackward(const SDL_Rect& r, float& force, float dt)
//{
//	if (r.y + r.h < rect.y + rect.h && r.y + r.h > rect.y && r.x >= rect.x + rect.w && r.x > rect.x)
//	{
//		force = App->entity->speed.x*dt;
//		return true;
//	}
//
//	else
//	{
//		return false;
//	}
//}