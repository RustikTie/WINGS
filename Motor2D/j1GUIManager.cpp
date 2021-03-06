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
#include "Background.h"
#include "Button.h"
#include "Text.h"
#include "Window.h"
#include "Image.h"
#include "Slider.h"
#include "Timer.h"
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
	background = App->tex->Load("textures/background.png");
	logo = App->tex->Load("textures/slime_guy.png");

	fonts.PushBack(App->font->Load("fonts/SFSlapstickComic.ttf", 30));
	
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

Widgets* j1GUIManager::AddBackground(int x, int y, WidgetType type, bool show, SDL_Rect rec)
{
	Widgets* widget = new Background(x, y, type, show, rec);
	widgets.add(widget);

	return widget;
}


Widgets* j1GUIManager::AddText(int x, int y, WidgetType type, bool show, const char* text, int font)
{
	Widgets* widget = new Text(x, y, type, show, text, font);
	widgets.add(widget);

	return widget;
}

Widgets* j1GUIManager::AddWindow(int x, int y, WidgetType type, float scale_x, float scale_y, bool show, SDL_Rect rec)
{
	Widgets* widget = new Window(x, y, type, scale_x, scale_y, show, rec);
	widgets.add(widget);

	return widget;
}

Widgets* j1GUIManager::AddImage(int x, int y, WidgetType type, bool show, SDL_Rect rec, float scale)
{
	Widgets* widget = new Image(x, y, type, show, rec, scale);
	widgets.add(widget);

	return widget;
}


Widgets* j1GUIManager::AddButton(int x, int y, WidgetType type, ButtonType btype, float scale, bool show, SDL_Rect* rec, const char* text)
{
	Widgets* widget = new Button(x, y, type, btype, scale, show, rec, text);
	widgets.add(widget);
	return widget;
}

Widgets* j1GUIManager::AddSlider(int x, int y, WidgetType type, SDL_Rect bg_rect, SDL_Rect bar_rect, SDL_Rect* slider_rect, bool show)
{
	Widgets* widget = new Slider(x, y, type, bg_rect, bar_rect, slider_rect, show);
	widgets.add(widget);
	return widget;
}

Widgets* j1GUIManager::AddTimer(int x, int y,  WidgetType type, bool show, int font, SDL_Rect rect)
{
	Widgets* widget = new Timer(x, y, type, show, font, rect);
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
	
	if (widget->type == BUTTON || widget->type == SLIDER)
	{
		int x, y;
		App->input->GetMousePosition(x, y);

		int posx = widget->rect_x + App->render->camera.x;
		int posy = widget->rect_y + App->render->camera.y;

		if (x > posx && x < posx + widget->tex_width
			&& y > posy && y < posy + widget->tex_height)
		{
			ret = true;
		}
	}

	return ret;
}