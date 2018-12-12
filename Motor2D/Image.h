#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Widgets.h"

class Image : public Widgets
{
public:
	Image(int x, int y, WidgetType type, bool show, SDL_Rect rec, float scale);
	~Image();
	void Draw();
private:
	SDL_Rect rec;
	float scale;
};

#endif // !__IMAGE_H__
