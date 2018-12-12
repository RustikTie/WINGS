#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Widgets.h"
#include "p2List.h"


class Window : public Widgets
{
public:
	Window(int x, int y, WidgetType type, float scalex, float scaley, bool show, SDL_Rect rec);

	void LinkWidgets(Widgets* widget);
	void Draw();
	void Move();
	~Window();

private:
	SDL_Rect rec;
	SDL_Texture* tex = nullptr;
	p2List<Widgets*> linked_widgets;
};

#endif // !__WINDOW_H__