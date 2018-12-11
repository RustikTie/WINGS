#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "p2List.h"

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
	Widgets* Background = nullptr;
	Widgets* Continue = nullptr;
	Widgets* StartButton = nullptr;
	Widgets* QuitButton = nullptr;
	Widgets* Options = nullptr;
	Widgets* Credits = nullptr;
	Widgets* BigWindow = nullptr;
	Widgets* Menu_Credits = nullptr;
	Widgets* Menu_Options = nullptr;
	Widgets* OptionsTitle = nullptr;
	Widgets* CreditTitle = nullptr;
	Widgets* CreditText = nullptr;
	Widgets* CreditText1 = nullptr;
	Widgets* CreditText2 = nullptr;
	Widgets* CreditText3 = nullptr;
	Widgets* CreditText4 = nullptr;
	Widgets* CreditText5 = nullptr;
	Widgets* CreditText6 = nullptr;
	Widgets* CreditText7 = nullptr;
	Widgets* CreditText8 = nullptr;
	Widgets* CreditText9 = nullptr;
	Widgets* CreditText10 = nullptr;
	Widgets* CreditText11 = nullptr;
	Widgets* CreditText12 = nullptr;
	Widgets* CreditText13 = nullptr;
	Widgets* CreditText14 = nullptr;
	Widgets* Plus = nullptr;
	Widgets* Minus = nullptr;
	Widgets* FXPlus = nullptr;
	Widgets* FXMinus = nullptr;
	Widgets* MusicVol = nullptr;
	Widgets* FXVol = nullptr;

	SDL_Rect rect_window;

	SDL_Rect hover;
	SDL_Rect idle;
	SDL_Rect click;

	p2List<Widgets*> MenuButtons;

private:
	bool			Quit = true;
};

#endif // __j1SCENE_H__