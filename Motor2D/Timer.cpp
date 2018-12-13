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
	sprintf_s(timer, "%i:%i", min, sec);
	timerText = App->gui->AddText(x,y,TEXT,true,timer, font);
}


Timer::~Timer()
{

}

void Timer::Draw()
{
	int curr_time = currTime.ReadSec() - startTime;
	sec += curr_time - last_time;

	if(sec >= 60)
	{
		min += 1;
		sec -= 60;
	}
	last_time = curr_time;

	sprintf_s(timer, "%i:%i", min, sec);
	timerText->EditText(timer);

}

void Timer::setTimer(int value)
{
	
}