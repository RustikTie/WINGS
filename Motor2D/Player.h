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

	bool Start();

	bool Awake(pugi::xml_node&);

	float			speed;
	float			acceleration;
	float			deceleration;
	float			gravity;
	float			jump_height;
	float			jump_speed;


private:
	
	
};

#endif
