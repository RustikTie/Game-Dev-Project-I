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
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->map->Load("level1_v4.tmx");

	
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

		if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
		{
			path.Clear();
			App->pathfinding->CreatePath({ 0,0 }, { 200, 200 });
			App->pathfinding->BackTracking({ 200, 200 }, path);
			LOG("PATH");
		}

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
		App->map->CleanUp();
		App->collisions->Erase_Non_Player_Colliders();
		App->map->Load("level2_v2.tmx");
		App->player->SetPos(100, 250);
		level1 = false;
	}

	//App->render->Blit(img, 0, 0);
	App->map->Draw();
	App->pathfinding->DrawPath(path);
	p2SString title("Pumpkin Knight");

	App->win->SetTitle(title.GetString());
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


