#ifndef __GUI_MANAGER__H
#define __GUI_MANAGER__H

#include "p2List.h"
#include "p2Log.h"
#include "j1Module.h"
#include "p2DynArray.h"

enum UIEvents
{
	MOUSE_ENTER,
	MOUSE_EXIT,
	MOUSE_DOWN,
	MOUSE_UP
};

class Widgets;
enum WidgetType;
struct SDL_Texture;
struct SDL_Rect;
struct _TTF_Font;

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

	//Widgets* AddBackground(int x, int y, ElementType type, bool show, SDL_Rect rec);
	Widgets* AddButton(int x, int y, WidgetType type, bool show, SDL_Rect* rec, const char* text = nullptr);
	Widgets* AddText(int x, int y, WidgetType type, bool show, const char* text, int font);
	Widgets* AddWindow(int x, int y, WidgetType type, bool show, SDL_Rect rec);
	Widgets* AddImage(int x, int y, WidgetType type, bool show, SDL_Rect rec);

public:

	bool cleaning = false;

	SDL_Texture* GetAtlas() const;
	SDL_Texture* GetBackground() const;
	SDL_Texture* GetGuiAtlas() const;

	p2List<Widgets*> widgets;
	p2DynArray<_TTF_Font*> fonts;

	SDL_Texture* button = nullptr;
	SDL_Texture* box = nullptr;
	_TTF_Font* font = nullptr;
	_TTF_Font* credits_font = nullptr;

private:

	SDL_Texture * background = nullptr;
	SDL_Texture* guiAtlas = nullptr;
	SDL_Texture* atlas;
	p2SString atlas_file_name;
};


#endif //__GUI_MANAGER__H