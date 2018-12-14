#include "Background.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1GUIManager.h"


Background::Background(int x, int y, WidgetType type, bool show, SDL_Rect rec) :Widgets(x, y, type)
{
	this->rec = rec;
	this->show = show;
}


Background::~Background()
{
}

void Background::Draw()
{
	if (show)
	{
		rect_x = pos.x - App->render->camera.x;
		rect_y = pos.y - App->render->camera.y;

		App->render->Blit(App->gui->GetBackground(), rect_x, rect_y, 1, 1, false, &rec);
	}
}