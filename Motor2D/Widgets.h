#ifndef __WIDGETS__H
#define __WIDGETS__H

#include "j1GUIManager.h"
#include "SDL/include/SDL.h"
#include "p2Point.h"



class Widgets : public j1GUIManager
{
public:
	Widgets(int x, int y, WidgetType type);
	~Widgets();

	virtual void Draw() {}

public:
	iPoint pos;
	WidgetType type;
	UIEvents event_type;

	SDL_Rect* texture_rect;
	SDL_Rect debug_rect;
	fPoint scale;

	uint tex_width;
	uint tex_height;

	int rect_x;
	int rect_y;

	bool mouse_in = false;
	bool mouse_out = false;

	bool debug = false;
	bool show = false;
};

#endif __WIDGETS__H
