#include "Text.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Window.h"
#include "j1Fonts.h"
#include "j1GUIManager.h"


Text::Text(int x, int y, WidgetType type, bool show, const char* text, int font) :Widgets(x, y, type)
{
	if (text != nullptr)
	{
		this->text = text;		
		tex = App->font->Print(this->text, { 255, 255, 255 }, App->gui->fonts[font]);	
	}

	this->show = show;
	this->font = font;
}


Text::~Text()
{

}

void Text::Draw()
{
	if(show)
		App->render->Blit(tex, pos.x - App->render->camera.x, pos.y - App->render->camera.y , 1.0f, 1.0f, false);
	
}

void Text::EditText(char* newText)
{
		text = newText;
		tex = App->font->Print(text, { 255,255,255 }, App->gui->fonts[font]);
			
	
}