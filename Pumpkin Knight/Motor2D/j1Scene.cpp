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
//#include "SDL_mixer.h"

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

	Mix_VolumeMusic(volume);

	//rect_credits = { 1256, 3151, 365, 185 };

	transition = App->tex->Load("gui/transition.png");

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	rect_window = { 1187, 0, 1113, 848 };

	idle = { 102, 3151, 365, 185 };
	hover = { 484, 3151, 365, 185 };
	click = { 868, 3151, 365, 185 };

	plus_idle = { 377, 3558, 183, 184 };
	plus_hover = { 574, 3558, 183, 184 };
	plus_click = { 771, 3558, 183, 184 };

	minus_idle = { 1366, 3558, 183, 184 };
	minus_hover = { 1562, 3558, 183, 184 };
	minus_click = { 1759, 3558, 183, 184 };

	if (start)
	{
		//if (previousScene == CREDITS || previousScene == OPTIONS)
		//{
		//	//App->gui->CleanUp();
		//	App->gui->AddBackground(0, 0, BACKGROUND, { 0,0,1024,768 });

		//	Continue = App->gui->AddButton(400, 50, BUTTON, true, &idle, "CONTINUE");
		//	QuitButton = App->gui->AddButton(400, 450, BUTTON, true, &idle, "QUIT");
		//	StartButton = App->gui->AddButton(400, 150, BUTTON, true, &idle, "START");
		//	Options = App->gui->AddButton(400, 250, BUTTON, true, &idle, "OPTIONS");
		//	Credits = App->gui->AddButton(400, 350, BUTTON, true, &idle, "CREDITS");


		//}
		
			App->map->CleanUp();
			//App->gui->CleanUp();
			App->entity_manager->CleanUp();
			App->collisions->Erase_Non_Player_Colliders();
			App->render->camera.x = 0;
			App->render->camera.y = 0;
			App->gui->AddBackground(0, 0, BACKGROUND, true, { 0,0,1024,768 });

			Continue = App->gui->AddButton(400, 50, BUTTON, true, &idle, "CONTINUE");
			QuitButton = App->gui->AddButton(400, 450, BUTTON, true, &idle, "QUIT");
			StartButton = App->gui->AddButton(400, 150, BUTTON, true, &idle, "START");
			Options = App->gui->AddButton(400, 250, BUTTON, true, &idle, "OPTIONS");
			Credits = App->gui->AddButton(400, 350, BUTTON, true, &idle, "CREDITS");
			Menu_Credits = App->gui->AddButton(0, 0, BUTTON, false, &idle, "BACK");
			Menu_Options = App->gui->AddButton(0, 0, BUTTON, false, &idle, "BACK");
			BigWindow = App->gui->AddWindow(200, 180, WINDOW, false, rect_window);
			Plus = App->gui->AddButton(370, 230, BUTTON, false, &plus_idle);
			Minus = App->gui->AddButton(250, 230, BUTTON, false, &minus_idle);
			CreditText = App->gui->AddText(250, 230, TEXT, false, "test");

			App->audio->PlayMusic("audio/music/Spooky Scary Skeletons.ogg");
		
		
		previousScene = MENU;

	}

	//if (credits)
	//{
	//	if (previousScene == MENU)
	//	{
	//		//App->gui->CleanUp();
	//		App->render->camera.x = 0;
	//		App->render->camera.y = 0;

	//		App->gui->AddBackground(0, 0, BACKGROUND, { 0,0,1024,768 });
	//		
	//		BigWindow = App->gui->AddWindow(200, 180, WINDOW, rect_window);
	//		CreditText = App->gui->AddText(250, 230, TEXT, "test");
	//		Menu_Credits = App->gui->AddButton(0, 0, BUTTON, &idle, "BACK");
	//	}
	//	//App->map->CleanUp();
	//	//App->entity_manager->CleanUp();
	//	//App->collisions->Erase_Non_Player_Colliders();
	//	
	//	previousScene = CREDITS;
	//}

	//if (options)
	//{
	//	if (previousScene == MENU)
	//	{
	//		//App->gui->CleanUp();
	//		App->render->camera.x = 0;
	//		App->render->camera.y = 0;

	//		App->gui->AddBackground(0, 0, BACKGROUND, { 0,0,1024,768 });
	//		rect_window = { 1187, 0, 1113, 848 };
	//		BigWindow = App->gui->AddWindow(200, 180, WINDOW, rect_window);
	//		Menu_Options = App->gui->AddButton(0, 0, BUTTON, &idle, "BACK");
	//		Plus = App->gui->AddButton(370, 230, BUTTON, &plus_idle);
	//		Minus = App->gui->AddButton(250, 230, BUTTON, &minus_idle);
	//	}
	//	//App->map->CleanUp();
	//	//App->entity_manager->CleanUp();
	//	//App->collisions->Erase_Non_Player_Colliders();

	//}

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
		//App->entity_manager->AddEnemy(WOLF, 1300, 0);
		//App->entity_manager->AddEnemy(BAT, 500, 100);
		//App->entity_manager->AddEnemy(WOLF, 5000, 0);
		App->entity_manager->AddEnemy(CANDY_PINK, 600, 675);
		App->entity_manager->AddEnemy(CANDY_ORANGE, 600, 600);
		App->entity_manager->AddEnemy(CANDY_PINK, 600, 550);
		App->entity_manager->AddEnemy(CANDY_PINK, 500, 675);
		App->entity_manager->AddEnemy(CANDY_BLUE, 750, 675);

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

	if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_REPEAT)
	{
		volume -= 1;
		Mix_VolumeMusic(volume);
	}
	if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_REPEAT)
	{
		volume += 1;
		Mix_VolumeMusic(volume);
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
	{
		App->SaveGame();
		maycontinue = true;
	}
	
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
		if (element == Continue || QuitButton || StartButton || Options || Credits || Menu_Options || Menu_Credits)
		{
			element->texture_rect = &hover;
		}
		if (element == Plus)
		{
			element->texture_rect = &plus_hover;
		}
		if (element == Minus)
		{
			element->texture_rect = &minus_hover;
		}
		break;

	case MOUSE_EXIT:
		if (element == Continue || QuitButton || StartButton || Options || Credits || Menu_Options || Menu_Credits)
		{
			element->texture_rect = &idle;
		}
		if (element == Plus)
		{
			element->texture_rect = &plus_idle;
		}
		if (element == Minus)
		{
			element->texture_rect = &minus_idle;
		}
		break;

	case MOUSE_DOWN:
		if (element == Continue || QuitButton || StartButton || Options || Credits || Menu_Options || Menu_Credits )
		{
			element->texture_rect = &click;
		}
		if (element == Plus)
		{
			element->texture_rect = &plus_click;
		}
		if (element == Minus)
		{
			element->texture_rect = &minus_click;
		}
		break;

	case MOUSE_UP:

		if (element == StartButton && options==false)
		{
			App->gui->cleaning = true;
			start = false;
			level1 = true;
		}
		if (element == Menu_Credits && start==false)
		{
			App->gui->cleaning = true;
			credits = false;
			start = true;
			previousScene = CREDITS;
		}
		if (element == Menu_Options && start == false)
		{
			App->gui->cleaning = true;
			options = false;
			start = true;
			previousScene = OPTIONS;
		}
		if (element == QuitButton)
		{
			LOG("CY@");
			exit = false;
		}
		if (element == Options)
		{
			BigWindow->show = true;
			Plus->show = true;
			Minus->show = true;
			Menu_Options->show = true;
			Continue->show = false;
			StartButton->show = false;
			Options->show = false;
			Credits->show = false;
			QuitButton->show = false;
		}
		if (element == Credits)
		{
			App->gui->cleaning = true;
			credits = true;
			options = false;
			start = false;
			level1 = false;
			level2 = false;
		}
		if (element == Continue && maycontinue == true)
		{
			App->LoadGame();
		}
		if (element == Plus)
		{
			volume += 10;
			Mix_VolumeMusic(volume);
		}
		if (element == Minus)
		{			
			volume -= 10;
 			Mix_VolumeMusic(volume);
		}
		break;
	
	default:
		break;
	}

	return true;
}

void j1Scene::Transition()
{

}
