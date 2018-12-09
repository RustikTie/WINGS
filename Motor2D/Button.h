#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Widgets.h"

class Button : public Widgets
{
public:
	Button(int x, int y, WidgetType types, bool show, SDL_Rect* rec, const char* text);
	~Button();

	void Draw();
	//bool Highlight();

private:
	const char* buttontext = nullptr;
	SDL_Texture* ButtonBox = nullptr;
	SDL_Texture* ButtonText = nullptr;

};


#endif // !__BUTTON_H__