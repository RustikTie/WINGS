#include "j1App.h"
#include "j1Render.h"
#include "Window.h"
#include "p2List.h"
#include "j1GUIManager.h"

// window coords {16, 528, 457, 485 }
Window::Window(int x, int y, WidgetType type, bool show, SDL_Rect rec) : Widgets(x, y, type)
{
	
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
	

}

void Window::Move()
{
	
}