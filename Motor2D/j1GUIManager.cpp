#include "j1App.h"
#include "j1GUIManager.h"
#include "j1Textures.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "Brofiler\Brofiler.h"
#include "Widgets.h"
#include "Button.h"

j1GUIManager::j1GUIManager()
{
	name.create("gui");
}


j1GUIManager::~j1GUIManager()
{
}

bool j1GUIManager::Awake(pugi::xml_node& config)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_name = config.child("atlas").attribute("file").as_string("");
	atlas = App->tex->Load(atlas_name.GetString());

	return ret;
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
	LOG("Freeing GUI");

	p2List_item<Widgets*>* item;
	item = widgets.start;

	while (item != nullptr)
	{
		RELEASE(item->data);
		item = item->next;
	}

	widgets.clear();

	return true;
	return true;
}


SDL_Texture* j1GUIManager::GetAtlas()const
{
	return atlas;
}

Widgets* j1GUIManager::CreateButton(int x, int y, ElementType _type, ButtonType type, SDL_Rect* rec)
{
	Widgets* elem = new Button(x, y, _type, type, rec);
	widgets.add(elem);

	return elem;
}