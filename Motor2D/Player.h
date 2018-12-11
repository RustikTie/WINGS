#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Animation.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1EntityManager.h"

class Player : public Entity
{
public:
	Player(int x, int y);
	~Player();

	void SetPos(float x, float y) {
		pos.x = x;
		pos.y = y;
	}

	bool Start();

	bool Awake(pugi::xml_node&);

	void MoveEntity(float dt);

	void Jump_Glide(float dt);

	void Draw(float dt);

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

public:

	bool				map1 = true;
	bool				map2 = false;

	float			speed;
	float			acceleration;
	float			deceleration;
	float			gravity;
	float			jump_height;
	float			jump_speed;
	float			max_height;
	float			death_border;
	int				lives;

	bool			jumping = false;
	bool			gliding = false;
	bool			godmode = false;
	bool			falling = true;
	bool			contact = false;

	SDL_Texture*	graphics = nullptr;

	Animation*		current_anim = nullptr;
	Animation		idle;
	Animation		walk;

	uint walk_fx;
	uint jump_fx;
	uint glide_fx;
	uint death_fx;
	
	//to add through xml
	SDL_Rect life = { 0, 919, 53, 45 };
	SDL_Rect empty = { 0, 872, 53, 45 };
	SDL_Rect half = { 0, 825, 53, 45 };
	SDL_Rect character = { 0, 969, 53, 47 };

private:
	
	float			old_grav = 0;
	
};

#endif
