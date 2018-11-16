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

	bool			jumping = false;
	bool			gliding = false;
	bool			godmode = false;
	bool			falling = true;
	bool			contact = false;

	SDL_Texture*	graphics = nullptr;

	Animation*		current_anim = nullptr;
	Animation		idle;
	Animation		walk;
private:
	
	float			old_grav = 0;
	
};

#endif
