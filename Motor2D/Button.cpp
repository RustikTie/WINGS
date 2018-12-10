#include "Button.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Window.h"
#include "j1Fonts.h"
#include "j1GUIManager.h"

Button::Button(int x, int y, WidgetType type, ButtonType btype, bool show, SDL_Rect rec, const char* text) : Widgets(x, y, type)
{
	this->type = btype;
	texture_rect = &rec;
	ButtonBox = App->gui->GetGuiAtlas();
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

		debug_rect = { rect_x, rect_y, (int)(tex_width*0.5f), (int)(tex_height*0.5f) };

		App->render->Blit(ButtonBox, pos.x, pos.y, 0.5f, 0.5f, false, texture_rect);
		App->render->Blit(ButtonText, pos.x + (tex_width / 6), pos.y + (tex_height / 7), 1, 1, false);
		if (debug == true)
		{
			App->render->DrawQuad(debug_rect, 0, 255, 0, 50);
		}
	}
}