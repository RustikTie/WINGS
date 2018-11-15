#ifndef __MUSHROOM_H__
#define __MUSHROOM_H__

#include "Entity.h"
#include "Animation.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1EntityManager.h"

class Mushroom : public Entity
{
public:
	Mushroom(int x, int y);
	~Mushroom();

	bool Awake(pugi::xml_node&);
	void MoveEntity(float dt);
	void Draw(float dt);

private:
	Animation		idle;
	Animation		walk;

	int				counter = 0;

	bool			move = false;
	bool			attack = false;

	fPoint			position;
	float			speed;
	float			alert_radius;
};

#endif

