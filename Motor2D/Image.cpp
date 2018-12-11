#include "Image.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1GUIManager.h"


Image::Image(int x, int y, WidgetType type, bool show, SDL_Rect rec) :Widgets(x, y, type)
{
	this->rec = rec;
	this->show = show;
}


Image::~Image()
{
}

void Image::Draw()
{
	App->render->Blit(App->gui->GetGuiAtlas(), pos.x, pos.y, 1, 1, false, &rec);
}
