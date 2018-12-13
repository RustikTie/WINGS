#ifndef __SLIDER_H__
#define __SLIDER_H__

#include "Widgets.h" 

class Slider : public Widgets
{
public:
	Slider(int x, int y, WidgetType type, SDL_Rect rect);
	~Slider();

	void Draw();

	void updateValue(float value);
	float getValue();

private:
	float value;
	SDL_Rect rect;
	
};

#endif __SLIDER_H__
