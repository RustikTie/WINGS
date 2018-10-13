#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "j1Module.h"
#include "Entity.h"
#include "j1Map.h"
#include "p2List.h"
#include "p2Point.h"
#include "Player.h"

#define MAX_ENEMIES 1000
#define SCREEN_SIZE 1
#define SCREEN_WIDTH 6400
#define SCREEN_HEIGHT 520

class Player;

enum ENTITY_TYPE
{
	NO_TYPE,
	PLAYER,
};

class Entity;

struct EntityInfo
{
	ENTITY_TYPE type = ENTITY_TYPE::NO_TYPE;
	int x, y;
};


class j1EntityManager : public j1Module
{
public:
	j1EntityManager();
	~j1EntityManager();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	//void EraseEnemies();

	void SpawnEntity(const EntityInfo& info);

	pugi::xml_document config_file;
	pugi::xml_node entity_config;

	EntityInfo			playerInfo;
	EntityInfo			queue[MAX_ENEMIES];
	Entity*				entities[MAX_ENEMIES];
	Player*				player_entity =	nullptr;

private:
	SDL_Texture*		player_sprite = nullptr;
};

#endif