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
#include "j1Player.h"
#include "j1Pathfinding.h"
#include "j1EntityManager.h"
#include "Brofiler\Brofiler.h"

using namespace pugi;

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	level1 = true;
	level2 = false;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	if (level1) 
	{
		App->map->Load("level1_v4.tmx");
		//App->entity_manager->AddEnemy(WOLF, 1100, 0);
		//App->entity_manager->AddEnemy(WOLF, 500, 0);
		/*App->entity_manager->AddEnemy(WOLF, 200, 100);
		App->entity_manager->AddEnemy(WOLF, 400, 100);
		App->entity_manager->AddEnemy(WOLF, 300, 100);*/
		/*App->entity_manager->AddEnemy(BAT, 300, 200);
		App->entity_manager->AddEnemy(BAT, 400, 200);
		App->entity_manager->AddEnemy(BAT, 500, 200);*/
	}

	if (level2)
	{
		App->map->Load("level2_v2.tmx");
	}
	
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdate Scene", Profiler::Color::Yellow)

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("Update Scene", Profiler::Color::Green)

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 200.0f * dt;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 200.0f * dt;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 200.0f * dt;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 200.0f * dt;

	if (App->input->GetKey(SDL_SCANCODE_F1)) 
	{
		if (level1 == false) 
		{
			App->map->CleanUp();
			App->entity_manager->CleanUp();
			App->collisions->Erase_Non_Player_Colliders();
			App->map->Load("level1_v4.tmx");
			App->player->SetPos(100, 200);
			level1 = true;
		}
		else
		{
			App->player->SetPos(100, 250);
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_F2))
	{
		App->player->SetPos(100, 250);
	}
	if (App->input->GetKey(SDL_SCANCODE_F5))
		App->SaveGame();
	
	if (App->input->GetKey(SDL_SCANCODE_F6))
		App->LoadGame();

	//CHANGE LEVEL
	if (App->player->getX() >= 6200.f && level1 == true) 

	{
		level2 = true;
		App->map->CleanUp();
		App->entity_manager->CleanUp();
		App->collisions->Erase_Non_Player_Colliders();
		App->map->Load("level2_v2.tmx");
		App->player->SetPos(100, 250);
		level1 = false;
	}

	//App->render->Blit(img, 0, 0);
	App->map->Draw();

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdate Scene", Profiler::Color::Blue)

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


