#ifndef __TIMER_H__
#define __TIMER_H__

#include "Widgets.h"
#include "Text.h"
#include "j1Timer.h"

struct SDL_Rect;

class Timer : public Widgets
{
public:
	Timer(int x, int y, WidgetType type, bool show, int font, SDL_Rect rect);
	~Timer();

	void Draw();
	void setTimer(int value);

private:

	bool show;
	int last_time = 0;

	int font = 0;
	j1Timer currTime;
	int sec = 0;
	int min = 0;
	int startTime = 0;
	SDL_Rect rect;
	Widgets* timerText;
	char timer[100];
	SDL_Texture* time_texture = nullptr;
};

#endif