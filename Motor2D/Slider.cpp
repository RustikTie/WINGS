#include "Slider.h"
#include "Widgets.h"
#include "j1GUIManager.h"
#include "j1App.h"
#include "j1Render.h"



Slider::Slider(int x, int y, WidgetType type, SDL_Rect bg_rect, SDL_Rect bar_rect, SDL_Rect* slider_rect, bool show):Widgets(x,y,type)
{
	this->bg_rect = bg_rect;
	this->bar_rect = bar_rect;
	this->slider_rect = slider_rect;
	int real_width = bar_rect.w;
	rect_x = slider_rect->x;
	rect_y = slider_rect->y;
	tex_width = slider_rect->w;
	tex_height = slider_rect->h;
}


Slider::~Slider()
{
}

void Slider::Draw()
{
	App->render->Blit(App->gui->GetGuiAtlas(), pos.x, pos.y, 1,1,false, &bg_rect);
	App->render->Blit(App->gui->GetGuiAtlas(), pos.x, pos.y, 1, 1, false, &bar_rect);
	App->render->Blit(App->gui->GetGuiAtlas(), pos.x, pos.y, 1, 1, false, slider_rect);

}

void Slider::updateValue(int mouse_pos)
{
	this->mouse_pos = mouse_pos;
	bar_rect.w = real_width - mouse_pos;
	value = (bar_rect.w * 100) / real_width;
	slider_rect->x = (slider_rect->x*mouse_pos) / last_mouse_pos;
	last_mouse_pos = mouse_pos;
}

int Slider::getValue()
{
	return value;
}