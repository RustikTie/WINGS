#include "j1App.h"
#include "j1GUIManager.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Scene.h"
#include "Widgets.h"
#include "Button.h"
#include "Text.h"
#include "Window.h"
#include "Image.h"
#include "Brofiler\Brofiler.h"



j1GUIManager::j1GUIManager()
{
}


j1GUIManager::~j1GUIManager()
{
}

bool j1GUIManager::Awake(pugi::xml_node&)
{
	return true;
}

bool j1GUIManager::Start()
{
	return true;
}

bool j1GUIManager::PreUpdate() 
{
	BROFILER_CATEGORY("PreUpdate GUI", Profiler::Color::Yellow)
	return true;
}

bool j1GUIManager::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdate GUI", Profiler::Color::Blue)
	return true;

}

bool j1GUIManager::CleanUp()
{
	return true;
}

Widgets* j1GUIManager::AddButton(int x, int y, WidgetType type, bool show, SDL_Rect* rec, const char* text)
{
	Widgets* widget = new Button(x, y, type, show, rec, text);
	widgets.add(widget);

	return widget;
}

Widgets* j1GUIManager::AddText(int x, int y, WidgetType type, bool show, const char* text, int font)
{
	Widgets* widget = new Text(x, y, type, show, text, font);
	widgets.add(widget);

	return widget;
}

Widgets* j1GUIManager::AddWindow(int x, int y, WidgetType type, bool show, SDL_Rect rec)
{
	Widgets* widget = new Window(x, y, type, show, rec);
	widgets.add(widget);

	return widget;
}

Widgets* j1GUIManager::AddImage(int x, int y, WidgetType type, bool show, SDL_Rect rec)
{
	Widgets* widget = new Image(x, y, type, show, rec);
	widgets.add(widget);

	return widget;
}

SDL_Texture* j1GUIManager::GetAtlas() const
{
	return atlas;
}

SDL_Texture* j1GUIManager::GetBackground() const
{
	return background;
}

SDL_Texture* j1GUIManager::GetGuiAtlas() const
{
	return guiAtlas;
}