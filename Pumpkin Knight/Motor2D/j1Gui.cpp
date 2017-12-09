#include "j1Gui.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "Element.h"
#include "Background.h"
#include "Button.h"
#include "Text.h"
//#include "Text_Box.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	background = App->tex->Load("gui/MenuBackground.png");
	button = App->tex->Load("gui/button_panel.png");
	box = App->tex->Load("gui/text_box.png");

	fonts.PushBack(App->font->Load("fonts/wow/ARIALN.ttf", 20));

	font = App->font->Load("fonts/wow/ARIALN.ttf", 20);
	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{

	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	p2List_item<Element*>* item = elements.start;

	while (item != NULL)
	{
		item->data->Draw();
		item = item->next;
	}

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	p2List_item<Element*>* item;
	item = elements.start;
	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	elements.clear();

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

SDL_Texture* j1Gui::GetBackground() const
{
	return background;
}

SDL_Texture* j1Gui::GetButton() const
{
	return button;
}


void j1Gui::AddBackground(int x, int y, ElementType type, SDL_Rect rec)
{
	Element* elem = new Background(x, y, type, rec);
	elements.add(elem);
}
//
//void j1Gui::AddButton(int x, int y, ElementType type, const char* text)
//{
//	Element* elem = new Button(x, y, type, text);
//	elements.add(elem);
//}
//
//void j1Gui::AddText(int x, int y, ElementType type, const char* text)
//{
//	Element* elem = new Text(x, y, type, text);
//	elements.add(elem);
//}
//
//void j1Gui::AddTextBox(int x, int y, ElementType type, const char* text)
//{
//	Element* elem = new Text_Box(x, y, type, text);
//	elements.add(elem);
//}