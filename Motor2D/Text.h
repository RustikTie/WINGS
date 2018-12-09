#ifndef __TEXT_H__
#define __TEXT_H__

#include "Widgets.h"
#include "j1Fonts.h"


class Text : public Widgets
{
public:
	Text(int x, int y, WidgetType type, bool show, const char* text, int font);
	~Text();

	void Draw();
	void EditText(char* text);

private:

	const char* text = nullptr;
	SDL_Texture* tex = nullptr;
	int font;
};

#endif // !__TEXT_H__