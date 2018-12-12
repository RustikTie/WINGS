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
}


Image::~Image()
{
}

void Image::Draw()
{
	App->render->Blit(App->gui->GetGuiAtlas(), pos.x - App->render->camera.x, pos.y - App->render->camera.y, scale, scale, false, &rec);
}
