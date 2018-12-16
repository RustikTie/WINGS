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
	real_width = bar_rect.w;
	rect_x = pos.x + bar_rect.w -20;
	rect_y = pos.y -10;
	tex_width = slider_rect->w;
	tex_height = slider_rect->h;
	this->show = show;
}


Slider::~Slider()
{
}

void Slider::Draw()
{
	if (show)
	{
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x, pos.y, 1, 1, false, &bg_rect);
		App->render->Blit(App->gui->GetGuiAtlas(), pos.x, pos.y, 1, 1, false, &bar_rect);
		App->render->Blit(App->gui->GetGuiAtlas(), rect_x,rect_y, 1, 1, false, slider_rect);
		debug_rect = { rect_x,rect_y, (int)(tex_width), (int)(tex_height) };
		if (debug == true)
		{
			App->render->DrawQuad(debug_rect, 0, 255, 0, 50);
		}
	}
}

void Slider::updateValue(float mouse_pos)
{
	this->mouse_pos = mouse_pos;

	if (mouse_pos != last_mouse_pos)
	{
		//this updates the bar length
		bar_rect.w = real_width -(pos.x + real_width - mouse_pos);
		//updates the value of the volume 100% regla de tres pim pam
		value = (bar_rect.w * 100) / real_width;
		//it works up to here, the following need to update  the x position of the slider
		// the slider pos x is different from the bars, so it is the variable rect_x
		// vars i have are mouse_pos, last_mouse_pos and real_width of the bar(not the slider)
		rect_x = pos.x + bar_rect.w - (rect_x + slider_rect->w - mouse_pos);
	}

	last_mouse_pos = mouse_pos;

}

int Slider::getValue()
{
	return value;
}