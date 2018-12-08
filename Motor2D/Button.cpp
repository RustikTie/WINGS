#include "Button.h"
#include "j1App.h"
#include "j1Render.h"

Button::Button(int x, int y, ElementType _type, ButtonType type, SDL_Rect* rec):Widgets(x,y, _type)
{
	texture_rec = rec;
	this->type = type;
}


Button::~Button()
{
}


void Button::Draw()
{
	App->render->Blit(GetAtlas(), pos.x, pos.y, 1, 1, false, texture_rec);
}
