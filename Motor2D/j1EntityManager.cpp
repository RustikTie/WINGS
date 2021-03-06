#include "j1EntityManager.h"
#include "Entity.h"
#include "Player.h"
#include "Mushroom.h"
#include "Beetle.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1Textures.h"
#include "Coins.h"
#include "Brofiler\Brofiler.h"

#define SPAWN_MARGIN 100

j1EntityManager::j1EntityManager()
{
	name.create("entities");
}

bool j1EntityManager::Awake(pugi::xml_node& config)
{
	config_file.load_file("config.xml");
	entity_config = config_file.child("config").child("entities");
	initial_pos.x = entity_config.child("player").child("position").attribute("x").as_float();
	initial_pos.y = entity_config.child("player").child("position").attribute("y").as_float();

	return true;
}

j1EntityManager::~j1EntityManager()
{

}

bool j1EntityManager::Start()
{
	LOG("loading entities");

	entityAtlas = App->tex->Load("textures/entities.png");

	if (App->scene->menu == false)
	{
		if (player_entity == nullptr)
		{
			player_entity = new Player(initial_pos.x, initial_pos.y);
			player_entity->Awake(entity_config);
			player_entity->Start();
		}
		else
		{
			player_entity->Start();
		}
	}

	return true;
}

bool j1EntityManager::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdate EntityManager", Profiler::Color::Yellow)

		// check camera position to decide what to spawn
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (queue[i].type != ENTITY_TYPE::NO_TYPE)
			{
				if (queue[i].y * SCREEN_SIZE > App->render->camera.y - SPAWN_MARGIN)
				{

					LOG("Spawning enemy at %d", queue[i].y* SCREEN_SIZE);
					SpawnEntity(queue[i]);
					queue[i].type = ENTITY_TYPE::NO_TYPE;

				}
			}
		}



	return true;
}

// Called before render is available
bool j1EntityManager::Update(float dt)
{
	BROFILER_CATEGORY("PreUpdate EntityManager", Profiler::Color::Green)

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			entities[i]->MoveEntity(dt);
			entities[i]->Draw(dt);
		}

		
	}
	if (player_entity != nullptr)
	{
		player_entity->MoveEntity(dt);

	}
	if (player_entity != nullptr)
	{
		player_entity->Draw(dt);
		player_entity->Jump_Glide(dt);
	}
		

	return true;
}

bool j1EntityManager::PostUpdate()
{
	BROFILER_CATEGORY("PreUpdate EntityManager", Profiler::Color::Blue)

	return true;
}

// Called before quitting
bool j1EntityManager::CleanUp()
{
	LOG("Freeing all enemies");

	//App->tex->UnLoad(App->entity->sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
		if (queue[i].type != NO_TYPE)
		{
			queue[i].type = NO_TYPE;
		}
	}

	delete player_entity;
	player_entity = nullptr;

	return true;
}

bool j1EntityManager::AddEnemy(ENTITY_TYPE type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENTITY_TYPE::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;

			ret = true;
			break;
		}
	}

	return ret;
}


void j1EntityManager::SpawnEntity(const EntityInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; entities[i] != nullptr && i < MAX_ENEMIES; ++i);
	
	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		
		case ENTITY_TYPE::PLAYER:
			entities[i] = new Player(info.x, info.y);
			break;
		case ENTITY_TYPE::MUSHROOM:
			entities[i] = new Mushroom(info.x, info.y);
			entities[i]->Awake(entity_config);
			break;
		case ENTITY_TYPE::BEETLE:
			entities[i] = new Beetle(info.x, info.y);
			entities[i]->Awake(entity_config);
			break;
		case ENTITY_TYPE::COIN:
			entities[i] = new Coins(info.x, info.y);
			coins.add(entities[i]);

			break;
		}
	}
}

bool j1EntityManager::Load(pugi::xml_node& data)
{
	if (player_entity != nullptr)
	{
		player_entity->Load(data);
	}

	pugi::xml_node mushroomnode = data.child("mushroom").first_child();
	pugi::xml_node beetlenode = data.child("beetle").first_child();
	pugi::xml_node coinnode = data.child("coin").first_child();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			if (entities[i]->type == MUSHROOM)
			{
				entities[i]->Load(mushroomnode);
				mushroomnode = mushroomnode.next_sibling();
			}
			if (entities[i]->type == BEETLE)
			{
				entities[i]->Load(beetlenode);
				beetlenode = beetlenode.next_sibling();
			}
			/*if (entities[i]->type == COIN)
			{
				entities[i]->Load(coinnode);
				coinnode = coinnode.next_sibling();
			}*/
		}
	}
	

	return true;
}

bool j1EntityManager::Save(pugi::xml_node& data) const
{
	if (player_entity != nullptr)
	{
		player_entity->Save(data);
	}

	pugi::xml_node mushroomnode = data.append_child("mushroom");
	pugi::xml_node beetlenode = data.append_child("beetle");
	pugi::xml_node coinnode = data.append_child("coin");


	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			if (entities[i]->type == MUSHROOM)
			{
				entities[i]->Save(mushroomnode);
			}
			if (entities[i]->type == BEETLE)
			{
				entities[i]->Save(beetlenode);
			}
			/*if (entities[i]->type == COIN)
			{
				entities[i]->Save(coinnode);
			}*/
		}
	}

	return true;
}


SDL_Texture* j1EntityManager::GetEntityAtlas() const
{
	return entityAtlas;
}