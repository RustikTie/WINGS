#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1EntityManager.h"
#include "j1GUIManager.h"
#include "Widgets.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	Mix_VolumeMusic(volume);
	Mix_Volume(-1, volume);

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	rect_window = { 798, 0, 451, 630 };
	rect_score = { 132, 961, 311, 111 };
	idle = { 4, 0, 175, 79 };
	hover = { 191, 0, 175, 79 };
	click = { 378, 0, 175, 79 };

	App->pause_game = false;
	//App->map->Load("iso.tmx");
	

	App->map->CleanUp();
	App->entitymanager->CleanUp();
		

	MenuButtons.add(Background = App->gui->AddBackground(0, 0, BACKGROUND, true, { 0,0,1024,768 }));
	MenuButtons.add(StartButton = App->gui->AddButton(100, 100, BUTTON, MAIN, 1, true, &idle, "Play"));
	MenuButtons.add(Continue = App->gui->AddButton(100, 200, BUTTON, MAIN, 1, true, &idle, "Continue"));
	MenuButtons.add(Options = App->gui->AddButton(100, 300, BUTTON, MAIN, 1, true, &idle, "Settings"));
	MenuButtons.add(Credits = App->gui->AddButton(100, 400, BUTTON, MAIN, 1, true, &idle, "Credits"));
	MenuButtons.add(QuitButton = App->gui->AddButton(100, 500, BUTTON, MAIN, 1, true, &idle, "Exit"));
	
	OptionsWidgets.add(Background = App->gui->AddBackground(0, 0, BACKGROUND, false, { 0,0,1024,768 }));
	OptionsWidgets.add(OptionWindow = App->gui->AddWindow(66, 80, WINDOW, 2, 1, false, rect_window));
	OptionsWidgets.add(Menu_Options = App->gui->AddButton(0, 0, BUTTON, BACK, 1, false, &idle, "BACK"));

	CreditsWidgets.add(Background = App->gui->AddBackground(0, 0, BACKGROUND, false, { 0,0,1024,768 }));
	CreditsWidgets.add(CreditsWindow = App->gui->AddWindow(66, 80, WINDOW, 2, 1, false, rect_window));
	CreditsWidgets.add(Menu_Credits = App->gui->AddButton(0, 0, BUTTON, BACK, 1, false, &idle, "BACK"));

	//App->gui->AddTimer(200, 100, TIMER, true, 0, idle);

	PauseMenu.add(PauseWindow = App->gui->AddWindow(500, 80, WINDOW, 1, 1, false, rect_window));
	PauseMenu.add(Resume = App->gui->AddButton(630, 220, BUTTON, BACK, 1, false, &idle, "Resume"));
	PauseMenu.add(PauseToMenu = App->gui->AddButton(630, 320, BUTTON, BACK, 1, false, &idle, "Menu"));
		
	if (level1)
	{
		App->map->Load("map_test.tmx");
		App->entitymanager->Start();
		App->entitymanager->AddEnemy(MUSHROOM, 3000, 100);
		App->entitymanager->AddEnemy(COIN, 2500, 900);

		App->entitymanager->AddEnemy(BEETLE, 2500, 700);
		App->entitymanager->AddEnemy(MUSHROOM, 6000, 100);
		App->entitymanager->AddEnemy(BEETLE, 6700, 1800);
		App->entitymanager->AddEnemy(MUSHROOM, 10000, 200);

		//App->gui->AddText();

	}
	if (level2)
	{
		App->map->CleanUp();
		App->entitymanager->CleanUp();
		App->entitymanager->Start();
		App->map->Load("level2_v2.tmx");

		
	}
	
	
	App->audio->PlayMusic("audio/music/BGM.ogg");

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_REPEAT)
	{
		volume -= 5;
		Mix_VolumeMusic(volume);
	}
	if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_REPEAT)
	{
		volume += 5;
		Mix_VolumeMusic(volume);
	}
	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();

	if(App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 1;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 1;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 1;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 1;

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		if (level1 == false)
		{

			menu = false;
			App->map->CleanUp();
			App->entitymanager->CleanUp();
			App->collisions->Erase_Non_Player_Colliders();
			level2 = false;
			level1 = true;
			Start();
		}

		else
		{
			App->entitymanager->player_entity->SetPos(500, 500);
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		App->entitymanager->player_entity->SetPos(500, 1000);
	}

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && !menu)
	{
		if (App->pause_game)
		{
			App->pause_game = false;

			for (int i = 0; i < PauseMenu.count(); ++i)
			{
				PauseMenu[i]->show = false;
			}
		}
		else
		{
			App->pause_game = true;

			for (int i = 0; i < PauseMenu.count(); ++i)
			{
				PauseMenu[i]->show = true;
			}
		}

	}

	App->map->Draw();

	int x, y;


	if (App->entitymanager->player_entity != nullptr 
		&& App->entitymanager->player_entity->pos.x >= 13500.f )

	{
		level2 = true;
		App->map->CleanUp();
		App->entitymanager->CleanUp();
		App->entitymanager->Start();
		App->collisions->Erase_Non_Player_Colliders();
		App->map->Load("Map_2.tmx");
		App->entitymanager->player_entity->SetPos(500, 1000);
		level1 = false;
	}

	
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{

	return Quit;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool j1Scene::MouseEvents(Widgets* widget)
{
	switch (widget->event_type)
	{
	case MOUSE_ENTER:
		if (widget->type == BUTTON)
		{
			widget->texture_rect = &hover;
		}
		break;

	case MOUSE_EXIT:
		if (widget->type == BUTTON)
		{
			widget->texture_rect = &idle;
		}
		break;

	case MOUSE_DOWN:
		if (widget->type == BUTTON)
		{
			widget->texture_rect = &click;
		}
		break;

	case MOUSE_UP:
		if (widget->type == BUTTON)
		{
			widget->texture_rect = &idle;
		}
		//MainMenu
		if (widget == StartButton && widget->show)
		{
			menu = false;
			level1 = true;
			Start();
			for (int i = 0; i < MenuButtons.count(); ++i)
			{
				MenuButtons[i]->show = false;
			}
		}

		if (widget == Options && widget->show)
		{
			for (int i = 0; i < MenuButtons.count(); ++i)
			{
				MenuButtons[i]->show = false;
			}
			for (int i = 0; i < OptionsWidgets.count(); ++i)
			{
				OptionsWidgets[i]->show = true;
			}
		}

		if (widget == Credits && widget->show)
		{
			for (int i = 0; i < MenuButtons.count(); ++i)
			{
				MenuButtons[i]->show = false;
			}
			for (int i = 0; i < CreditsWidgets.count(); ++i)
			{
				CreditsWidgets[i]->show = true;
			}
		}

		if (widget == QuitButton && widget->show)
		{
			Quit = false;
		}
		//Setting Menu
		if (widget == Menu_Options && widget->show)
		{
			for (int i = 0; i < MenuButtons.count(); ++i)
			{
				MenuButtons[i]->show = true;
			}
			for (int i = 0; i < OptionsWidgets.count(); ++i)
			{
				OptionsWidgets[i]->show = false;
			}
		}
		//Credits Menu
		if (widget == Menu_Credits && widget->show)
		{
			for (int i = 0; i < MenuButtons.count(); ++i)
			{
				MenuButtons[i]->show = true;
			}
			for (int i = 0; i < CreditsWidgets.count(); ++i)
			{
				CreditsWidgets[i]->show = false;
			}
		}
		//Pause Menu
		if (widget == PauseToMenu && widget->show)
		{
			menu = true;
			level1 = false;
			level2 = false;

			App->map->CleanUp();
			App->entitymanager->CleanUp();

			for (int i = 0; i < MenuButtons.count(); ++i)
			{
				MenuButtons[i]->show = true;
			}
			for (int i = 0; i < PauseMenu.count(); ++i)
			{
				PauseMenu[i]->show = false;
			}
		}
		if (widget == Resume && widget->show)
		{
			App->pause_game = false;

			for (int i = 0; i < PauseMenu.count(); ++i)
			{
				PauseMenu[i]->show = false;
			}
		}
		break;
	default:
		break;
	}

	return true;
}

void j1Scene::ChangeMap(float x, float y)
{
	if (level2)
	{
		App->map->CleanUp();
		App->entitymanager->CleanUp();
		App->entitymanager->Start();
		App->entitymanager->player_entity->SetPos(x, y);
		level1 = false;
		App->collisions->Erase_Non_Player_Colliders();
		App->map->Load("Map_2.tmx");
		
	}

	else
	{
		App->map->CleanUp();
		App->entitymanager->player_entity->SetPos(x, y);
		App->entitymanager->CleanUp();
		App->entitymanager->Start();
		App->collisions->Erase_Non_Player_Colliders();
		App->map->Load("map_test.tmx");
	}
}

