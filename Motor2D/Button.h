#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Widgets.h"
#include "Animation.h"



class Button : public Widgets
{
public:
	Button(int x, int y, ElementType _type, ButtonType type, SDL_Rect* rec);
	~Button();

	void Draw();

private:

	SDL_Rect* texture_rec;
	ButtonType type;
};

#endif // !__BUTTON_H__