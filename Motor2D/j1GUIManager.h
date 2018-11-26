#ifndef __GUI_MANAGER__H
#define __GUI_MANAGER__H

#include "j1Module.h"


class j1GUIManager : public j1Module
{
public:


	j1GUIManager();
	virtual ~j1GUIManager();
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool PostUpdate();
	bool CleanUp();

};

#endif //__GUI_MANAGER__H