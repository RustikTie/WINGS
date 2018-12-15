#ifndef __MUSHROOM_H__
#define __MUSHROOM_H__

#include "Entity.h"
#include "Animation.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1EntityManager.h"
#include "j1Pathfinding.h"
#include "j1Scene.h"

class Mushroom : public Entity
{
public:
	Mushroom(int x, int y);
	~Mushroom();

	bool Awake(pugi::xml_node&);
	void MoveEntity(float dt);
	void Draw(float dt);
	void OnCollision();
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

private:
	Animation		idle;
	Animation		walk;

	int				counter = 0;

	bool			move = false;
	bool			attack = false;
	bool			alive = true;
	fPoint			position;
	float			alert_radius;
};

#endif

