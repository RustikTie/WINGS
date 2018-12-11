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
	App->render->Blit(App->gui->GetBackground(), pos.x, pos.y, 1, 1, false, &rec);
}