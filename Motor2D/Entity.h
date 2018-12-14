#ifndef __ENTITY_H__
#define __ENTITY_H__


#include "j1Module.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "Animation.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Collisions.h"

struct SDL_Texture;

enum ENTITY_TYPE;

class Entity
{
protected:
	Animation * animation = nullptr;

public:
	Entity(int x, int y);
	~Entity();

	const Collider* GetCollider() const;

	virtual bool Awake(pugi::xml_node&);

	virtual void Draw(float dt);

	virtual void OnCollision();
	//bool LoadEnemyLayer(pugi::xml_node& node, EnemyLayer* layer);
	virtual void MoveEntity(float dt) {};

	virtual bool Load(pugi::xml_node&) { return false; };
	virtual bool Save(pugi::xml_node&) const { return false; };

public:
	ENTITY_TYPE		type;

	//SDL_Texture * sprites = nullptr;

	fPoint			pos = { 0.0f,0.0f };
	fPoint			collider_pos = { 0.0f,0.0f };
	fPoint			original_pos = { 0.0f,0.0f };
	float			speed = 0;
	float			gravity = 0;
	fPoint			initial_pos = { 0.0f,0.0f };

	Collider* collider = nullptr;
	Collider* death_collider = nullptr;
	p2DynArray<iPoint> path;

	int x_scale;
	int y_scale;

	bool flip;
};

#endif // !_ENTITY_H_