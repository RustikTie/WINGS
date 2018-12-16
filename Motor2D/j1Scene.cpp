#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Collisions.h"
#include "j1Scene.h"
#include "j1EntityManager.h"
#include "Entity.h"
#include "Player.h"
#include "j1GUIManager.h"
#include "Widgets.h"
#include "Animation.h"


j1Scene::j1Scene() : j1Module()
{
	name.create("scene");

	SlimeGuy.PushBack({ 67, 196, 66, 92 });
	SlimeGuy.PushBack({ 0, 196, 66, 92 });
	SlimeGuy.loop = true;
	SlimeGuy.speed = 2.f;

}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	button_click = App->audio->LoadFx("audio/fx/ButtonClick.wav");

	Mix_VolumeMusic(volume);
	Mix_Volume(-1, volume);
	sprintf_s(credits_title, "CREDITS");
	

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
	locked = { 566, 0, 175, 79 };
	App->pause_game = false;
	//App->map->Load("iso.tmx");
	
	sprites = App->tex->Load("textures/p1_spritesheet.png");
	SlimeGuy.Reset();
	current_anim = &SlimeGuy;

	App->map->CleanUp();
	App->entitymanager->CleanUp();
		
	MenuButtons.add(Background = App->gui->AddBackground(0, 0, BACKGROUND, true, { 0,0,1024,768 }));
	MenuButtons.add(StartButton = App->gui->AddButton(100, 100, BUTTON, MAIN, 1, true, &idle, "Play"));
	MenuButtons.add(Options = App->gui->AddButton(100, 300, BUTTON, MAIN, 1, true, &idle, "Settings"));
	MenuButtons.add(Credits = App->gui->AddButton(100, 400, BUTTON, MAIN, 1, true, &idle, "Credits"));
	MenuButtons.add(QuitButton = App->gui->AddButton(100, 500, BUTTON, MAIN, 1, true, &idle, "Exit"));
	MenuButtons.add(Logo = App->gui->AddImage(310, 220, IMAGE, true, {127,1135,357,248 }, 1.f));
;
	pugi::xml_document data;
	pugi::xml_parse_result result = data.load_file(load_game.GetString());

	if (CheckSaveFile())
	{
		MenuButtons.add(Continue = App->gui->AddButton(100, 200, BUTTON, MAIN, 1, true, &idle, "Continue"));
		saved_game = true;
	}
	else
	{
		MenuButtons.add(Continue = App->gui->AddButton(100, 200, BUTTON, MAIN, 1, true, &locked, "Continue"));
	}

	OptionsWidgets.add(Background = App->gui->AddBackground(0, 0, BACKGROUND, false, { 0,0,1024,768 }));
	OptionsWidgets.add(OptionWindow = App->gui->AddWindow(66, 80, WINDOW, 2, 1, false, rect_window));
	OptionsWidgets.add(Menu_Options = App->gui->AddButton(0, 0, BUTTON, BACK, 1, false, &idle, "BACK"));
	OptionsWidgets.add(Credits = App->gui->AddText(66, 80, TEXT, false, credits_title, 0));
	OptionsWidgets.add(OptionsSFX = App->gui->AddSlider(66,80, SLIDER, bg_rect,bar_rect,&slider_rect, false));
	OptionsWidgets.add(OptionsVol = App->gui->AddSlider(66, 200, SLIDER, bg_rect, bar_rect, &slider_rect, false));

	CreditsWidgets.add(Background = App->gui->AddBackground(0, 0, BACKGROUND, false, { 0,0,1024,768 }));
	CreditsWidgets.add(CreditsWindow = App->gui->AddWindow(66, 80, WINDOW, 2, 1, false, rect_window));
	CreditsWidgets.add(Menu_Credits = App->gui->AddButton(0, 0, BUTTON, BACK, 1, false, &idle, "BACK"));
	CreditsWidgets.add(WebButton = App->gui->AddButton(430, 550, BUTTON, BACK, 1, false, &idle, "Website"));

	PauseMenu.add(PauseWindow = App->gui->AddWindow(500, 80, WINDOW, 1, 1, false, rect_window));
	PauseMenu.add(Resume = App->gui->AddButton(630, 220, BUTTON, BACK, 1, false, &idle, "Resume"));
	PauseMenu.add(PauseToMenu = App->gui->AddButton(630, 320, BUTTON, BACK, 1, false, &idle, "Menu"));
	PauseMenu.add(PauseSFX = App->gui->AddSlider(66, 80, SLIDER, bg_rect, bar_rect, &slider_rect, false));
	PauseMenu.add(PauseVol = App->gui->AddSlider(66, 200, SLIDER, bg_rect, bar_rect, &slider_rect, false));

	if (level1)
	{
		App->map->Load("map_test.tmx");
		App->entitymanager->Start();
	
		App->entitymanager->AddEnemy(COIN, 2500, 900);
		App->entitymanager->AddEnemy(COIN, 3000, 1300);
		App->entitymanager->AddEnemy(COIN, 5800, 820);
		App->entitymanager->AddEnemy(COIN, 7600, 1000);
		App->entitymanager->AddEnemy(COIN, 7800, 1100);
		App->entitymanager->AddEnemy(COIN, 8000, 1200);
		App->entitymanager->AddEnemy(COIN, 8200, 1400);
		App->entitymanager->AddEnemy(COIN, 11000, 400);
		
		App->entitymanager->AddEnemy(MUSHROOM, 3000, 100);
		App->entitymanager->AddEnemy(BEETLE, 2500, 700);
		App->entitymanager->AddEnemy(MUSHROOM, 6000, 100);
		App->entitymanager->AddEnemy(BEETLE, 6700, 1800);
		App->entitymanager->AddEnemy(MUSHROOM, 10000, 200);
		App->gui->AddTimer(App->win->GetWidth()/2, 24, TIMER, true, 0, idle);
		App->audio->PlayMusic("audio/music/BGM.ogg");



	}
	if (level2)
	{
		player_score = App->entitymanager->player_entity->score;
		App->map->CleanUp();
		App->entitymanager->CleanUp();
		App->collisions->Erase_Non_Player_Colliders();
		App->map->Load("Map_2.tmx");
		App->entitymanager->Start();
		App->entitymanager->player_entity->score = player_score;
		App->audio->Start();
		App->map->Load("level2_v2.tmx");

		App->audio->PlayMusic("audio/music/BGM.ogg");


		App->entitymanager->AddEnemy(COIN, 200 + App->entitymanager->player_entity->pos.x , App->entitymanager->player_entity->pos.y);
	}
	
	
	if(menu)
		App->audio->PlayMusic("audio/music/MBGM.ogg");

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
		&& App->entitymanager->player_entity->pos.x >= 13500.f && level1)

	{
		menu = false;
		level2 = true;
		App->map->CleanUp();
		player_score = App->entitymanager->player_entity->score;
		player_coins = App->entitymanager->player_entity->coins_grabbed;
		App->entitymanager->CleanUp();
		App->entitymanager->Start();
		App->collisions->Erase_Non_Player_Colliders();
		App->entitymanager->player_entity->SetPos(500, 1000);
		App->entitymanager->player_entity->score = player_score;
		App->entitymanager->player_entity->coins_grabbed = player_coins;
		level1 = false;
		Start();

		for (int i = 0; i < MenuButtons.count(); ++i)
		{
			MenuButtons[i]->show = false;
		}
	}

	if (App->entitymanager->player_entity != nullptr
		&& App->entitymanager->player_entity->pos.x >= 13500.f && level2)

	{
		menu = true;
		level1 = false;
		level2 = false;

		App->map->CleanUp();
		App->entitymanager->CleanUp();
		App->collisions->Erase_Non_Player_Colliders();
		Start();
	}

	
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	if (menu)
	{
		App->render->Blit(sprites, 700 - App->render->camera.x, 300 - App->render->camera.y, 3, 3, true, &(current_anim->GetCurrentFrame()));
	}


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

			if (widget == Continue && !saved_game)
			{			
			}
			else
			{
				widget->texture_rect = &hover;
				if (widget->show)
				{
					App->audio->PlayFx(button_click);
				}
			}
			
		}

		break;

	case MOUSE_EXIT:
		if (widget->type == BUTTON)
		{
			if (widget == Continue && !saved_game)
			{
			}
			else
				widget->texture_rect = &idle;
		}
		break;

	case MOUSE_DOWN:
		if (widget->type == BUTTON)
		{
			if (widget == Continue && !saved_game)
			{
			}			
			else
			{
				widget->texture_rect = &hover;
				if (widget->show)
				{
					App->audio->PlayFx(button_click);
				}

			}
		}
		if (widget->type == SLIDER)
		{
			int x, y;
			App->input->GetMousePosition(x, y);
			widget->updateValue(x);
			if(widget == OptionsSFX || widget == PauseSFX)
			{
				Mix_Volume(-1, widget->getValue());
			}
			if (widget == OptionsVol || widget == PauseVol)
			{
				Mix_VolumeMusic(widget->getValue());
			}
		}
		
		break;

	case MOUSE_UP:
		if (widget->type == BUTTON)
		{
			if (widget == Continue && !saved_game)
			{
			}
			else
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

		if (widget == Continue && widget->show)
		{
			if (CheckSaveFile())
			{
				menu = false;
				level1 = true;
				Start();
				for (int i = 0; i < MenuButtons.count(); ++i)
				{
					MenuButtons[i]->show = false;
				}
				App->LoadGame();
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

		if (widget == WebButton && widget->show)
		{
			ShellExecuteA(NULL, "open", "https://rustiktie.github.io/WINGS/", NULL, NULL, SW_SHOWNORMAL);
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
			App->collisions->Erase_Non_Player_Colliders();
			Start();

			/*for (int i = 0; i < MenuButtons.count(); ++i)
			{
				MenuButtons[i]->show = true;
			}*/
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

bool j1Scene::CheckSaveFile()
{
	bool ret = false;

	pugi::xml_document data;

	pugi::xml_parse_result result = data.load_file(App->load_game.GetString());

	if (result != NULL)
	{
		ret = true;
	}
	else
	{
		ret = false;
	}

	return ret;
}



