#include "Button.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Window.h"
#include "j1Fonts.h"
#include "j1GUIManager.h"

Button::Button(int x, int y, WidgetType type, ButtonType btype, float scale, bool show, SDL_Rect* rec, const char* text) : Widgets(x, y, type)
{
	this->type = btype;
	ButtonBox = App->gui->GetGuiAtlas();

	if (text != nullptr)
	{
		ButtonText = App->font->Print(text, { 255, 255, 255 }, App->gui->fonts[0]);
	}

	blit_scale = scale;

	texture_rect = rec;
	tex_width = rec->w*scale;
	tex_height = rec->h*scale;

	this->show = show;
}


Button::~Button()
{

}

void Button::Draw()
{
	if (show)
	{
		int rect_x = pos.x - App->render->camera.x;
		int rect_y = pos.y - App->render->camera.y;

		debug_rect = { rect_x, rect_y, (int)(tex_width), (int)(tex_height) };

		App->render->Blit(ButtonBox, pos.x, pos.y, blit_scale, blit_scale, false, texture_rect);
		App->render->Blit(ButtonText, pos.x + (tex_width / 6), pos.y + (tex_height / 7), 1, 1, false);
		if (debug == true)
		{
			App->render->DrawQuad(debug_rect, 0, 255, 0, 50);
		}
	}
}