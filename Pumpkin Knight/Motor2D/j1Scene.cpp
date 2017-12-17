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
#include "j1Fonts.h"
#include "Text.h"
#include "Image.h"
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

	button_click = App->audio->LoadFx("audio/fx/ButtonClick.wav");

	transition = App->tex->Load("gui/transition.png");

	Mix_VolumeMusic(volume);
	Mix_Volume(-1, volume);

	//rect_credits = { 1256, 3151, 365, 185 };
	

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
			Background = App->gui->AddBackground( 0, 0, BACKGROUND, true, { 0,0,1024,768 });

			Continue = App->gui->AddButton(400, 50, BUTTON, true, &idle, "CONTINUE");
			QuitButton = App->gui->AddButton(400, 450, BUTTON, true, &idle, "QUIT");
			StartButton = App->gui->AddButton(400, 150, BUTTON, true, &idle, "START");
			Options = App->gui->AddButton(400, 250, BUTTON, true, &idle, "OPTIONS");
			Credits = App->gui->AddButton(400, 350, BUTTON, true, &idle, "CREDITS");
			Menu_Credits = App->gui->AddButton(0, 0, BUTTON, false, &idle, "BACK");
			Menu_Options = App->gui->AddButton(0, 0, BUTTON, false, &idle, "BACK");
			BigWindow = App->gui->AddWindow(200, 180, WINDOW, false, rect_window);
			CreditTitle = App->gui->AddText(475, 120, TEXT, false, "CREDITS", 1);
			OptionsTitle = App->gui->AddText(475, 120, TEXT, false, "OPTIONS", 1);
			CreditText = App->gui->AddText(250, 230, TEXT, false, "Developed By:", 1);
			CreditText1 = App->gui->AddText(250, 250, TEXT, false, "Clara R. Garcia & Ivan Drofiak", 1);
			CreditText2 = App->gui->AddText(250, 270, TEXT, false, "Art By:", 1);
			CreditText3 = App->gui->AddText(250, 290, TEXT, false, "Skeleton: Jesse M/Twitter-@Jsf23Art", 1);
			CreditText4 = App->gui->AddText(250, 310, TEXT, false, "Wolf: William.Thompsonj", 1);
			CreditText5 = App->gui->AddText(250, 330, TEXT, false, "Bat: MoikMellah",1);
			CreditText6 = App->gui->AddText(250, 350, TEXT, false, "Candy: Iumimae",1);
			CreditText7 = App->gui->AddText(250, 370, TEXT, false, "Tileset: KIIRA",1);
			CreditText8 = App->gui->AddText(250, 390, TEXT, false, "Background: GameArt2D.com",1);
			CreditText9 = App->gui->AddText(250, 410, TEXT, false, "GUI: GameArt2D.com",1);
			CreditText10 = App->gui->AddText(250, 430, TEXT, false, "Music:",1);
			CreditText11 = App->gui->AddText(250, 450, TEXT, false, "Menu music: Spooky Scary Skeletons 8-bits",1);
			CreditText12 = App->gui->AddText(250, 470, TEXT, false, "Level music: This Is Halloween 8-bit",1);
			CreditText13 = App->gui->AddText(250, 490, TEXT, false, "Walk FX: Finnolia Productions Inc",1);
			MusicVol = App->gui->AddText(310, 220, TEXT, false, "Music Vol.",1);
			FXVol = App->gui->AddText(600, 220, TEXT, false, "SFX Vol.",1);
			Plus = App->gui->AddButton(370, 250, BUTTON, false, &plus_idle);
			Minus = App->gui->AddButton(250, 250, BUTTON, false, &minus_idle);
			FXPlus = App->gui->AddButton(650, 250, BUTTON, false, &plus_idle);
			FXMinus = App->gui->AddButton(530, 250, BUTTON, false, &minus_idle);

			App->audio->PlayMusic("audio/music/Spooky Scary Skeletons.ogg");	
		
		previousScene = MENU;

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
		//App->entity_manager->AddEnemy(WOLF, 1300, 0);
		//App->entity_manager->AddEnemy(BAT, 500, 100);
		//App->entity_manager->AddEnemy(WOLF, 5000, 0);
		App->entity_manager->AddEnemy(CANDY_PINK, 600, 675);
		App->entity_manager->AddEnemy(CANDY_ORANGE, 600, 600);
		App->entity_manager->AddEnemy(CANDY_PINK, 600, 550);
		App->entity_manager->AddEnemy(CANDY_PINK, 500, 675);
		App->entity_manager->AddEnemy(CANDY_BLUE, 750, 675);
		Score = App->gui->AddText(500, 220, TEXT, true, "SCORE",2);
		ScoreCount = App->gui->AddText(600, 220, TEXT, true, "100", 1);
		//Candies = App->gui->AddImage()
		CandyCount = App->gui->AddText(600, 320, TEXT, true, "0", 1);

		previousScene = LVL1;
		//score = App->font->Print("SCORE", { 255, 255,255 }, App->gui->font);

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
		Score = App->gui->AddText(500, 220, TEXT, true, "SCORE", 2);
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
		sprintf_s(currScore, 10, "%i", App->entity_manager->player_entity->score);
		ScoreCount->EditText(currScore);
		sprintf_s(currCandies, 10, "%i", App->entity_manager->player_entity->candiesGrabbed);
		CandyCount->EditText(currCandies);

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
			//App->render->camera.x = 0;
			//App->render->camera.y = 0;
			App->entity_manager->CleanUp();
			App->collisions->Erase_Non_Player_Colliders();
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
		if (element->show)
		{
			App->audio->PlayFx(button_click);
		}
		if (element == Continue || QuitButton || StartButton || Options || Credits || Menu_Options || Menu_Credits)
		{
			element->texture_rect = &hover;
		}
		if (element == Plus || element == FXPlus)
		{
			element->texture_rect = &plus_hover;
		}
		if (element == Minus || element == FXMinus)
		{
			element->texture_rect = &minus_hover;
		}
		break;

	case MOUSE_EXIT:
		if (element == Continue || QuitButton || StartButton || Options || Credits || Menu_Options || Menu_Credits)
		{
			element->texture_rect = &idle;
		}
		if (element == Plus || element == FXPlus)
		{
			element->texture_rect = &plus_idle;
		}
		if (element == Minus || element == FXMinus)
		{
			element->texture_rect = &minus_idle;
		}
		break;

	case MOUSE_DOWN:
		if (element->show)
		{
			App->audio->PlayFx(button_click);
		}
		if (element == Continue || QuitButton || StartButton || Options || Credits || Menu_Options || Menu_Credits )
		{
			element->texture_rect = &click;
		}
		if (element == Plus || element == FXPlus)
		{
			element->texture_rect = &plus_click;
		}
		if (element == Minus || element == FXMinus)
		{
			element->texture_rect = &minus_click;
		}
		break;

	case MOUSE_UP:

		if (element == Continue || QuitButton || StartButton || Options || Credits || Menu_Options || Menu_Credits)
		{
			element->texture_rect = &hover;
		}
		if (element == Plus || element == FXPlus)
		{
			element->texture_rect = &plus_hover;
		}
		if (element == Minus || element == FXMinus)
		{
			element->texture_rect = &minus_hover;
		}

		if (element == StartButton && element->show)
		{
			/*BigWindow->show = false;
			Plus->show = false;
			Minus->show = false;
			Menu_Options->show = false;
			Continue->show = false;
			StartButton->show = false;
			Options->show = false;
			Credits->show = false;
			QuitButton->show = false;*/
			App->gui->cleaning = true;
			start = false;
			level1 = true;
			start_counter = SDL_GetTicks();			
		}
		if (element == Menu_Credits && element->show)
		{
			BigWindow->show = false;
			Plus->show = false;
			Minus->show = false;
			Menu_Options->show = false;
			Continue->show = true;
			StartButton->show = true;
			Options->show = true;
			Credits->show = true;
			QuitButton->show = true;
			CreditText->show = false;
			CreditText1->show = false;
			CreditText2->show = false;
			CreditText3->show = false;
			CreditText4->show = false;
			CreditText5->show = false;
			CreditText6->show = false;
			CreditText7->show = false;
			CreditText8->show = false;
			CreditText9->show = false;
			CreditText10->show = false;
			CreditText11->show = false;
			CreditText12->show = false;
			CreditText13->show = false;
			CreditTitle->show = false;
			OptionsTitle->show = false;
			MusicVol->show = false;
			FXVol->show = false;
			FXPlus->show = false;
			FXMinus->show = false;
		}
		if (element == Menu_Options && element->show)
		{
			BigWindow->show = false;
			Plus->show = false;
			Minus->show = false;
			Menu_Options->show = false;
			Continue->show = true;
			StartButton->show = true;
			Options->show = true;
			Credits->show = true;
			QuitButton->show = true;
			CreditText->show = false;
			CreditText1->show = false;
			CreditText2->show = false;
			CreditText3->show = false;
			CreditText4->show = false;
			CreditText5->show = false;
			CreditText6->show = false;
			CreditText7->show = false;
			CreditText8->show = false;
			CreditText9->show = false;
			CreditText10->show = false;
			CreditText11->show = false;
			CreditText12->show = false;
			CreditText13->show = false;
			CreditTitle->show = false;
			OptionsTitle->show = false;
			MusicVol->show = false;
			FXVol->show = false;
			FXPlus->show = false;
			FXMinus->show = false;
		}
		if (element == QuitButton && element->show)
		{
			LOG("CY@");
			exit = false;
		}
		if (element == Options && element->show)
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
			CreditText->show = false;
			CreditText1->show = false;
			CreditText2->show = false;
			CreditText3->show = false;
			CreditText4->show = false;
			CreditText5->show = false;
			CreditText6->show = false;
			CreditText7->show = false;
			CreditText8->show = false;
			CreditText9->show = false;
			CreditText10->show = false;
			CreditText11->show = false;
			CreditText12->show = false;
			CreditText13->show = false;
			CreditTitle->show = false;
			OptionsTitle->show = true;
			MusicVol->show = true;
			FXVol->show = true;
			FXPlus->show = true;
			FXMinus->show = true;
		}
		if (element == Credits && element->show)
		{
			BigWindow->show = true;
			Plus->show = false;
			Minus->show = false;
			Menu_Options->show = true;
			Continue->show = false;
			StartButton->show = false;
			Options->show = false;
			Credits->show = false;
			QuitButton->show = false;
			CreditText->show = true;
			CreditText1->show = true;
			CreditText2->show = true;
			CreditText3->show = true;
			CreditText4->show = true;
			CreditText5->show = true;
			CreditText6->show = true;
			CreditText7->show = true;
			CreditText8->show = true;
			CreditText9->show = true;
			CreditText10->show = true;
			CreditText11->show = true;
			CreditText12->show = true;
			CreditText13->show = true;
			CreditTitle->show = true;
			OptionsTitle->show = false;
			MusicVol->show = false;
			FXVol->show = false;
			FXPlus->show = false;
			FXMinus->show = false;
		}
		if (element == Continue && maycontinue == true && element->show)
		{
			App->LoadGame();
		}
		if (element == Plus && element->show)
		{
			volume += 10;
			Mix_VolumeMusic(volume);
		}
		if (element == Minus && element->show)
		{			
			volume -= 10;
 			Mix_VolumeMusic(volume);
		}
		if (element == FXPlus && element->show)
		{
			volume += 10;
			Mix_Volume(-1, volume);
		}
		if (element == FXMinus && element->show)
		{
			volume -= 10;
			Mix_Volume(-1, volume);
		}
		break;
	
	default:
		break;
	}

	return true;
}
