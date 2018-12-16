#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "Animation.h"
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
	bool Awake(pugi::xml_node&);

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

	bool CheckSaveFile();

	bool			start =	true;
	bool			level1 = false;
	bool			level2 = false;
	bool			menu = true;

	int				map = 0;
	int				volume = 50;

	bool maycontinue = false;

private:
	Widgets*		Background = nullptr;
	Widgets*		Continue = nullptr;
	Widgets*		StartButton = nullptr;
	Widgets*		QuitButton = nullptr;
	Widgets*		Options = nullptr;
	Widgets*		Credits = nullptr;
	Widgets*		Logo = nullptr;
	Widgets*		OptionWindow = nullptr;
	Widgets*		CreditsWindow = nullptr;
	Widgets*		Menu_Credits = nullptr;
	Widgets*		Menu_Options = nullptr;
	Widgets*		WebButton = nullptr;
	Widgets*		OptionsTitle = nullptr;
	Widgets*		CreditTitle = nullptr;
	Widgets*		CreditText = nullptr;
	Widgets*		CreditText1 = nullptr;
	Widgets*		CreditText2 = nullptr;
	Widgets*		CreditText3 = nullptr;
	Widgets*		CreditText4 = nullptr;
	Widgets*		CreditText5 = nullptr;
	Widgets*		CreditText6 = nullptr;
	Widgets*		CreditText7 = nullptr;
	Widgets*		CreditText8 = nullptr;
	Widgets*		CreditText9 = nullptr;
	Widgets*		CreditText10 = nullptr;
	Widgets*		CreditText11 = nullptr;
	Widgets*		CreditText12 = nullptr;
	Widgets*		CreditText13 = nullptr;
	Widgets*		CreditText14 = nullptr;
	Widgets*		Plus = nullptr;
	Widgets*		Minus = nullptr;
	Widgets*		FXPlus = nullptr;
	Widgets*		FXMinus = nullptr;
	Widgets*		MusicVol = nullptr;
	Widgets*		FXVol = nullptr;

	Widgets*		PauseWindow = nullptr;
	Widgets*		PauseToMenu = nullptr;
	Widgets*		Resume = nullptr;
	Widgets*		PausePlus = nullptr;
	Widgets*		PauseMinus = nullptr;

	Widgets*		OptionsVol = nullptr;
	Widgets*		OptionsSFX = nullptr;
	Widgets*		PauseVol = nullptr;
	Widgets*		PauseSFX = nullptr;

	char			credits_title[100];
	char			credits_1[100];
	char			credits_2[100];
	char			credits_3[100];
	char			credits_4[100];
	char			credits_5[100];
	char			credits_6[100];
	char			credits_7[100];
	char			credits_8[100];
	char			credits_9[100];
	char			credits_10[100];
	char			credits_11[100];
	char			credits_12[100];
	char			credits_13[100];

	SDL_Rect		rect_window;
	SDL_Rect		rect_score;
	SDL_Rect		bg_rect = { 351, 551, 358, 56 };
	SDL_Rect		bar_rect = { 351, 633, 358,56 };
	SDL_Rect		slider_rect = { 416, 96, 75, 79 };

	SDL_Rect		hover;
	SDL_Rect		idle;
	SDL_Rect		click;
	SDL_Rect		locked;

	p2List<Widgets*> MenuButtons;
	p2List<Widgets*> OptionsWidgets;
	p2List<Widgets*> CreditsWidgets;
	p2List<Widgets*> PauseMenu;

	Animation		SlimeGuy;
	Animation*		current_anim = nullptr;
	SDL_Texture*	sprites = nullptr;

private:
	int				button_click;
	bool			Quit = true;
	p2SString		load_game;
	bool			saved_game = false;
	int				player_score = 0;
	int				player_coins = 0;
};

#endif // __j1SCENE_H__