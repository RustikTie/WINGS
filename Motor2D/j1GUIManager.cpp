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
	name.create("gui");
}


j1GUIManager::~j1GUIManager()
{
}

bool j1GUIManager::Awake(pugi::xml_node& config)
{
	LOG("Loading GUI atlas");

	atlas_file_name = config.child("atlas").attribute("file").as_string("");
	return true;
}

bool j1GUIManager::Start()
{

	guiAtlas = App->tex->Load(atlas_file_name.GetString());
	
	font = App->font->Load("fonts/SF Slapstick Comic.tff", 30);

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

		p2List_item<Widgets*>* widget = widgets.start;
	p2List_item<Widgets*>* debug_element = widgets.start;

	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
	{
		while (widget != nullptr)
		{
			if (widget->data->debug == false)
			{
				widget->data->debug = true;
			}
			else
			{
				widget->data->debug = false;
			}
			widget = widget->next;
		}
	}

	while (widget != NULL)
	{
		widget->data->Draw();
		if (MouseCollision(widget->data))
		{
			if (widget->data->mouse_in == false)
			{
				widget->data->mouse_in = true;
				widget->data->mouse_out = false;
				widget->data->event_type = MOUSE_ENTER;
				App->scene->MouseEvents(widget->data);
			}

			if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
			{
				widget->data->event_type = MOUSE_DOWN;
				App->scene->MouseEvents(widget->data);
			}

			if (App->input->GetMouseButtonDown(1) == KEY_UP)
			{
				widget->data->event_type = MOUSE_UP;
				App->scene->MouseEvents(widget->data);
			}
		}

		if (!MouseCollision(widget->data) && widget->data->mouse_in)
		{
			widget->data->mouse_in = false;
			widget->data->mouse_out = true;
			widget->data->event_type = MOUSE_EXIT;
			App->scene->MouseEvents(widget->data);
		}

		widget = widget->next;
	}



	if (cleaning)
	{
		cleaning = false;
		CleanUp();
		App->scene->Start();
		if (App->scene->maycontinue)
		{
			App->LoadGame();
		}
	}

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
}

//Widgets* j1GUIManager::AddBackground(int x, int y, ElementType type, bool show, SDL_Rect rec)
//{
//	
//
//}


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


Widgets* j1GUIManager::AddButton(int x, int y, WidgetType type, ButtonType btype, bool show, SDL_Rect rec, const char* text)
{
	Widgets* widget = new Button(x, y, type, btype, show, rec, text);
	widgets.add(widget);
	return widget;
}


SDL_Texture* j1GUIManager::GetBackground() const
{
	return background;
}

SDL_Texture* j1GUIManager::GetGuiAtlas() const
{
	return guiAtlas;
}

bool j1GUIManager::MouseCollision(Widgets* widget)
{
	bool ret = false;
	if (widget->type == BUTTON)
	{
		int x, y;
		App->input->GetMousePosition(x, y);

		int posx = widget->pos.x + App->render->camera.x;
		int posy = widget->pos.y + App->render->camera.y;

		if (x > posx && x < posx + widget->tex_width*0.5f
			&& y > posy && y < posy + widget->tex_height*0.5f)
		{
			ret = true;
		}
	}
	return ret;
}