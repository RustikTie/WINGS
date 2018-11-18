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
	
	//App->map->Load("iso.tmx");
	if (level1)
	{
		App->map->Load("map_test.tmx");
		App->entitymanager->Start();
		App->entitymanager->AddEnemy(MUSHROOM, 3000, 300);
		App->entitymanager->AddEnemy(BEETLE, 2500, 1200);
		App->entitymanager->AddEnemy(MUSHROOM, 6000, 200);
		
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

			start = false;
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

	App->map->Draw();

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					map_coordinates.x, map_coordinates.y);

	App->win->SetTitle(title.GetString());

	if (App->entitymanager->player_entity->pos.x >= 13500.f)

	{
		level2 = true;
		App->map->CleanUp();
		App->entitymanager->CleanUp();
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
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Scene::ChangeMap(float x, float y)
{
	if (level2)
	{
		App->map->CleanUp();
		App->entitymanager->CleanUp();
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