#ifndef __SLIDER_H__
#define __SLIDER_H__

#include "Widgets.h" 

class Slider : public Widgets
{
public:
	Slider(int x, int y, WidgetType type, SDL_Rect bg_rect, SDL_Rect bar_rect, SDL_Rect* slider_rect, bool show);
	~Slider();

	void Draw();

	void updateValue(int value);
	int getValue();

private:
	int mouse_pos = 0;
	int value = 100;
	SDL_Rect bg_rect;
	SDL_Rect bar_rect;
	SDL_Rect* slider_rect = nullptr;
	int real_width;
	int last_mouse_pos = 0;
	bool show;
};

#endif __SLIDER_H__
