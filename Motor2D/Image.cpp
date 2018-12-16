#include "Image.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1GUIManager.h"
#include "j1EntityManager.h"


Image::Image(int x, int y, WidgetType type, bool show, SDL_Rect rec, float scale) :Widgets(x, y, type)
{
	this->rec = rec;
	this->show = show;
	this->scale = scale;

	pos.x = x;
	pos.y = y;
}


Image::~Image()
{
}

void Image::Draw()
{
	if (show)
	{
		App->render->Blit(App->gui->logo, pos.x - App->render->camera.x, pos.y - App->render->camera.y, scale, scale, false, &rec);
	}
}
