#include "Slider.h"
#include "Widgets.h"
#include "j1GUIManager.h"
#include "j1App.h"
#include "j1Render.h"



Slider::Slider(int x, int y, WidgetType type, SDL_Rect rect):Widgets(x,y,type)
{
	this->rect = rect;
}


Slider::~Slider()
{
}

void Slider::Draw()
{

}

void Slider::updateValue(float value)
{
	this->value = value;
}

float Slider::getValue()
{
	return value;
}