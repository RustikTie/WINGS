#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class Widgets;
enum SCENE
{
	MENU,
	LVL1,
	LVL2,
	CREDITS,
	OPTIONS,
};
class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool MouseEvents(Widgets* widget);

	void ChangeMap(float x, float y);

	bool			start =	true;
	bool			level1 = false;
	bool			level2 = false;
	bool			menu = true;

	int				map = 0;
	int				volume = 50;

	bool maycontinue = false;

private:
};

#endif // __j1SCENE_H__