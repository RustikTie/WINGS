#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "Widgets.h"

class Background : public Widgets
{
public:
	Background(int x, int y, WidgetType type, bool show, SDL_Rect rec);
	~Background();
	void Draw();
private:
	SDL_Rect rec;
};

#endif // !__BACKGROUND_H__