#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 1000

#include "j1Module.h"
#include "p2Log.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )


enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_GROUND,
	COLLIDER_PLAYER,
	COLLIDER_ENEMY,
	COLLIDER_PICK_UP,
	COLLIDER_BLOCKER,
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	j1Module* callback = nullptr;
	int col_offset = 0;
	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, j1Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
	void SetCollisionOffset(const SDL_Rect& r, int speed);
	//bool Collider::CheckCollisionDownwards(const SDL_Rect& r, float& gravity, float dt);
	//bool Collider::CheckCollisionBackward(const SDL_Rect& r, float& force, float dt);
	//bool Collider::CheckCollisionForward(const SDL_Rect& r, float& force, float dt);

};

class j1Collisions : public j1Module
{
public:

	j1Collisions();
	~j1Collisions();

	bool Awake();
	bool PreUpdate();
	bool Update(float dt);
	//update_status PostUpdate();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback = nullptr);
	bool EraseCollider(Collider* collider);
	void DebugDraw();

	bool checkColisionList(Collider* enemCollider);
	void Erase_Non_Player_Colliders();



private:
	Collider * colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;

};

#endif // __ModuleCollision_H__