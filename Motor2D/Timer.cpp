#include "Timer.h"
#include "p2SString.h"
#include "j1App.h"
#include "j1GUIManager.h"
#include "j1Render.h"
#include "Text.h"



Timer::Timer(int x, int y, WidgetType type, bool show,  int font, SDL_Rect rect) :Widgets(x, y, type)
{
	startTime = currTime.ReadSec();
	this->font = font;
	this->rect = rect;
	this->show = show;

	App->gui->AddImage(x-40, 10, IMAGE, true, timer_rect, 1.f);

	sprintf_s(timer, "%i:%i", min, sec);
	timerText = App->gui->AddText(x,y,TEXT,true,timer, font);
}


Timer::~Timer()
{

}

void Timer::Draw()
{
	/*int curr_time;
	int offset_time;*/

	if (!App->pause_game)
	{
		curr_time = currTime.ReadSec() - startTime - offset_time;
		sec += curr_time - last_time;

		if (sec >= 60)
		{
			min += 1;
			sec -= 60;
		}
		last_time = curr_time;

		sprintf_s(timer, "%i:%i", min, sec);
		timerText->EditText(timer);
	}
	else
	{
		offset_time = currTime.ReadSec() - startTime - curr_time;
	}
}

void Timer::setTimer(int value)
{
	sec = value;
	while (sec >= 60)
	{
		min += 1;
		sec -= 60;
	}
}