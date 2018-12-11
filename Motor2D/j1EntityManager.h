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
	MUSHROOM,
	BEETLE,
	PLAYER,
	COIN,
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

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	fPoint				initial_pos = { 0.0f, 0.0f };

	//void EraseEnemies();

	void SpawnEntity(const EntityInfo& info);

	bool AddEnemy(ENTITY_TYPE type, int x, int y);

	SDL_Texture* GetEntityAtlas() const;

	pugi::xml_document config_file;
	pugi::xml_node entity_config;

	EntityInfo			playerInfo;
	EntityInfo			queue[MAX_ENEMIES];
	Entity*				entities[MAX_ENEMIES];
	Player*				player_entity =	nullptr;

	p2List<Entity*>		coins;
private:
	SDL_Texture * entityAtlas = nullptr;
};

#endif