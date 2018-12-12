#include "j1App.h"
#include "j1Render.h"
#include "Window.h"
#include "p2List.h"
#include "j1GUIManager.h"

// window coords {16, 528, 457, 485 }
Window::Window(int x, int y, WidgetType type, float scalex, float scaley, bool show, SDL_Rect rec) : Widgets(x, y, type)
{
	this->rec = rec;
	this->tex = App->gui->GetGuiAtlas();
	this->show = show;

	pos.x = x;
	pos.y = y;

	scale.x = scalex;
	scale.y = scaley;
}

Window::~Window()
{
}

void Window::LinkWidgets(Widgets* widget)
{
	linked_widgets.add(widget);
}

void Window::Draw()
{
	if (show)
	{
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x, pos.y, scale.x, scale.y, false, &rec, NULL);
	}

}

void Window::Move()
{
	
}