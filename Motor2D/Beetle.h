#ifndef __BEETLE_H__
#define __BEETLE_H__

#include "Entity.h"
#include "Animation.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1EntityManager.h"
#include "j1Pathfinding.h"
#include "j1Scene.h"

class Beetle : public Entity
{
public:
	Beetle(int x, int y);
	~Beetle();

	bool Awake(pugi::xml_node&);
	void MoveEntity(float dt);
	void Draw(float dt);
	void OnCollision();
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

private:
	Animation		idle;
	Animation		fly;

	uint			counter = 0;

	bool			move = false;
	bool			attack = false;
	bool			alive = true;

	fPoint			position;
	float			speed;
	float			alert_radius;
};

#endif

