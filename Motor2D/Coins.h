#ifndef __COINS_H__
#define __COINS_H__

#include "Entity.h"
#include "Animation.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1EntityManager.h"

class Coins : public Entity
{
public:
	Coins(int x, int y);
	bool Awake(pugi::xml_node&);
	void Draw(float dt);
	void OnCollision();
	~Coins();

private:
	Animation			idle;
	Animation			explosion;
	SDL_Rect			rec;
	bool				grabbed = false;
	bool				alive = true;
	int					score = 1000;
	int					coinsGrabbed = 0;

};

#endif // !__COINS_H__