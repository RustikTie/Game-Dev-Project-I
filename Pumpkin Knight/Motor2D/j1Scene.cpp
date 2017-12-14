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
#include "j1Pathfinding.h"
#include "j1EntityManager.h"
#include "j1Gui.h"
#include "Element.h"
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
	start = true;
	level1 = false;
	level2 = false;
	credits = false;

	idle = { 102, 3151, 365, 185 };
	hover = { 484, 3151, 365, 185 };
	click = { 868, 3151, 365, 185 };
	rect_credits = { 1256, 3151, 365, 185 };

	transition = App->tex->Load("gui/transition.png");

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	if (start)
	{
		if (previousScene == CREDITS || previousScene == OPTIONS)
		{
			//App->gui->CleanUp();
			App->gui->AddBackground(0, 0, BACKGROUND, { 0,0,1024,768 });

			QuitButton = App->gui->AddButton(400, 400, BUTTON, idle, "QUIT");
			StartButton = App->gui->AddButton(400, 100, BUTTON, idle, "START");
			Options = App->gui->AddButton(400, 200, BUTTON, idle, "OPTIONS");
			Credits = App->gui->AddButton(400, 300, BUTTON, idle, "CREDITS");

		}
		else
		{
			App->map->CleanUp();
			//App->gui->CleanUp();
			App->entity_manager->CleanUp();
			App->collisions->Erase_Non_Player_Colliders();
			App->render->camera.x = 0;
			App->render->camera.y = 0;
			App->gui->AddBackground(0, 0, BACKGROUND, { 0,0,1024,768 });

			QuitButton = App->gui->AddButton(400, 400, BUTTON, idle, "QUIT");
			StartButton = App->gui->AddButton(400, 100, BUTTON, idle, "START");
			Options = App->gui->AddButton(400, 200, BUTTON, idle, "OPTIONS");
			Credits = App->gui->AddButton(400, 300, BUTTON, idle, "CREDITS");
			
			App->audio->PlayMusic("audio/music/Spooky Scary Skeletons.ogg");
		}
		
		previousScene = MENU;

	}

	if (credits)
	{
		if (previousScene == MENU)
		{
			//App->gui->CleanUp();
			App->render->camera.x = 0;
			App->render->camera.y = 0;

			App->gui->AddBackground(0, 0, BACKGROUND, { 0,0,1024,768 });
			rect_window = { 1187, 0, 1113, 848 };
			BigWindow = App->gui->AddWindow(200, 180, WINDOW, rect_window);
			CreditText = App->gui->AddText(250, 230, TEXT, "test");
			MainMenu = App->gui->AddButton(0, 0, BUTTON, idle, "BACK");
		}
		//App->map->CleanUp();
		//App->entity_manager->CleanUp();
		//App->collisions->Erase_Non_Player_Colliders();
		
		previousScene = CREDITS;
	}

	if (options)
	{
		if (previousScene == MENU)
		{
			//App->gui->CleanUp();
			App->render->camera.x = 0;
			App->render->camera.y = 0;

			App->gui->AddBackground(0, 0, BACKGROUND, { 0,0,1024,768 });
			rect_window = { 1187, 0, 1113, 848 };
			BigWindow = App->gui->AddWindow(200, 180, WINDOW, rect_window);
			MainMenu = App->gui->AddButton(0, 0, BUTTON, idle, "BACK");
		}
		//App->map->CleanUp();
		//App->entity_manager->CleanUp();
		//App->collisions->Erase_Non_Player_Colliders();

		previousScene = OPTIONS;
	}

	if (level1) 
	{
		//App->map->CleanUp();
		////App->gui->CleanUp();
		//App->entity_manager->CleanUp();
		//App->collisions->Erase_Non_Player_Colliders();
		App->render->camera.x = 500;
		App->render->camera.y = -180;
		App->map->Load("level1_v4.tmx");

		App->entity_manager->Start();
		/*App->entity_manager->AddEnemy(WOLF, 1300, 0);
		App->entity_manager->AddEnemy(BAT, 500, 100);
		App->entity_manager->AddEnemy(WOLF, 5000, 0);*/
		App->entity_manager->AddEnemy(CANDY, 600, 350);
		previousScene = LVL1;
		App->audio->PlayMusic("audio/music/Halloween.ogg");
	}


	if (level2)
	{
		App->map->CleanUp();
		App->gui->CleanUp();
		App->entity_manager->CleanUp();
		App->collisions->Erase_Non_Player_Colliders();

		App->map->Load("level2_v2.tmx");
		App->entity_manager->Start();
		App->entity_manager->AddEnemy(WOLF, 1000, 0);
		App->entity_manager->AddEnemy(BAT, 1300, 450);

		//if (App->entity_manager->player_entity == nullptr)
		//{
		//	App->entity_manager->player_entity = new Player(100, 200);
		//	App->entity_manager->player_entity->Awake(App->entity_manager->entity_config);
		//	App->entity_manager->player_entity->Start();
		//}

		App->audio->PlayMusic("audio/music/Halloween.ogg");
		previousScene = LVL2;

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
			start = false;
			App->map->CleanUp();
			App->gui->cleaning = true;
			App->entity_manager->CleanUp();
			App->collisions->Erase_Non_Player_Colliders();
			level2 = false;
			level1 = true;
			Start();
		}

		else
		{
			//App->entity_manager->player_entity->SetPos(100, 250);
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F2))
	{
		App->entity_manager->player_entity->SetPos(100, 250);
	}
	if (App->input->GetKey(SDL_SCANCODE_F5))
		App->SaveGame();
	
	if (App->input->GetKey(SDL_SCANCODE_F6))
		App->LoadGame();

	//CHANGE LEVEL
	if (level1)
	{
		if (App->entity_manager->player_entity->getX() >= 6200.f)

		{
			level2 = true;
			App->map->CleanUp();
			App->entity_manager->CleanUp();
			App->collisions->Erase_Non_Player_Colliders();
			App->map->Load("level2_v2.tmx");
			App->entity_manager->player_entity->SetPos(100, 250);
			level1 = false;
		}
		else if (App->entity_manager->player_entity->lives <= -1)
		{
			App->render->camera.x = 0;
			App->render->camera.y = 0;
			level1 = false;
			level2 = false;
			credits = false;
			start = true;
			Start();

		}
	}


	//App->render->Blit(img, 0, 0);
	App->map->Draw();
	

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdate Scene", Profiler::Color::Blue)

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		exit = false;

	return exit;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool j1Scene::MouseEvents(Element* element)
{
	switch (element->event_type)
	{
	case MOUSE_ENTER:
		element->texture_rect = hover;
		break;
	case MOUSE_EXIT:
		element->texture_rect = idle;
		break;
	case MOUSE_DOWN:
		if (element == StartButton)
		{

		}
		if (element == QuitButton)
		{
		}
		if (element == Options)
		{
		}
		if (element == Credits)
		{
		}
		element->texture_rect = click;

		break;
	case MOUSE_UP:

		if (element == StartButton)
		{
			App->gui->cleaning = true;
			start = false;
			level1 = true;
		}
		if (element == MainMenu)
		{
			credits = false;
			options = false;
			App->gui->cleaning = true;
			start = true;
			level1 = false;
			level2 = false;
		}
		if (element == QuitButton)
		{
			LOG("CY@");
			exit = false;
		}
		if (element == Options)
		{
			options = true;
			credits = false;
			start = false;
			App->gui->cleaning = true;
			level1 = false;
			level2 = false;
		}
		if (element == Credits)
		{
			credits = true;
			start = false;
			App->gui->cleaning = true;
			level1 = false;
			level2 = false;
			
		}	
		break;

	}

	return true;
}

void j1Scene::Transition()
{

}
