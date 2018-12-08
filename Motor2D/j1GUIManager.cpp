#include "j1App.h"
#include "j1GUIManager.h"
#include "Brofiler\Brofiler.h"



j1GUIManager::j1GUIManager()
{
}


j1GUIManager::~j1GUIManager()
{
}

bool j1GUIManager::Awake(pugi::xml_node&)
{
	return true;
}

bool j1GUIManager::Start()
{
	return true;
}

bool j1GUIManager::PreUpdate() 
{
	BROFILER_CATEGORY("PreUpdate GUI", Profiler::Color::Yellow)
	return true;
}

bool j1GUIManager::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdate GUI", Profiler::Color::Blue)
	return true;

}

bool j1GUIManager::CleanUp()
{
	return true;
}