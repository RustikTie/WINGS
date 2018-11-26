#ifndef __WIDGETS__H
#define __WIDGETS__H

#include "j1GUIManager.h"
#include "SDL/include/SDL.h"
#include "p2Point.h"

enum ElementType
{
	IMAGE,
	WINDOW,
	BUTTON,
	TEXT,
	NOTYPE,
};

class Widgets : public j1GUIManager
{
public:
	Widgets(int x, int y, ElementType type);
	~Widgets();

	virtual void Draw() {}

private:
	iPoint pos;
	ElementType type;
};

#endif __WIDGETS__H
