#ifndef __GUI_MANAGER__H
#define __GUI_MANAGER__H

#include "j1Module.h"
#include "p2List.h"

class Widgets;
struct SDL_Texture;
struct SDL_Rect;
struct _TTF_Font;

enum ElementType
{
	IMAGE,
	WINDOW,
	BUTTON,
	TEXT,
	NOTYPE,
};

enum ButtonType
{
	HOME,
	BACK,
	EXIT,
};
class j1GUIManager : public j1Module
{
public:


	j1GUIManager();
	virtual ~j1GUIManager();
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool PostUpdate();
	bool CleanUp();

	SDL_Texture* GetAtlas() const;

	Widgets* CreateButton(int x, int y, ElementType _type, ButtonType type, SDL_Rect* rec);

private:

	p2List<Widgets*> widgets;
	SDL_Texture* atlas = nullptr;
	p2SString atlas_name;

};

#endif //__GUI_MANAGER__H