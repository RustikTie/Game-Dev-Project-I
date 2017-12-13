//#include "Button.h"
//#include "Element.h"
//#include "p2Log.h"
//#include "j1App.h"
//#include "j1Render.h"
//#include "j1Textures.h"
//#include "j1Window.h"
//#include "j1Gui.h"
//
//
//Button::Button(int x, int y, ElementType type, SDL_Rect rec, const char* text, _TTF_Font* font) : Element(x, y, type)
//{
//	this->rec = rec;
//	this->text = text;
//	this->font = font;
//	
//	idle.PushBack({ 102,3152,363,181 });
//	hover.PushBack({ 487,3152,363,181 });
//	click.PushBack({ 870,3152,363,181 });
//	locked.PushBack({ 1257,3152,363,181 });
//	curr = &idle;
//}
//
//
//Button::~Button()
//{
//
//}
//
//void Button::OnClick()
//{
//
//}
//
//void Button::OnHover()
//{
//
//}
//
//void Button::Draw()
//{
//	App->render->Blit(App->gui->GetGuiAtlas(), pos.x, pos.y, 0.4f, 0.4f, false, &curr->GetCurrentFrame(), NULL);
//	
//	if (text != nullptr)
//	{
//		SDL_Texture* textPrint = App->font->Print(text, { (255),(255),(255),(255) }, font);
//		App->render->Blit(textPrint, pos.x + 1, pos.y + 2, 1, 1, false, &rec, NULL);
//	}
//}
//
#include "Button.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Window.h"
#include "j1Fonts.h"
#include "j1Gui.h"

Button::Button(int x, int y, ElementType types, SDL_Rect* TexRect, const char* text) : Element(x, y, types)
{
	if (text != nullptr)
	{
		buttontext = text;
		ButtonText = App->font->Print(buttontext, { 255, 255, 0 }, App->gui->font);
	}

	texture_rect = TexRect;

	ButtonBox = App->gui->GetAtlas();
	tex_width = texture_rect->w;
	tex_height = texture_rect->h;
}


Button::~Button()
{

}

void Button::Draw()
{
	App->render->Blit(ButtonBox, pos.x, pos.y, 0.5f, 0.5f, false, texture_rect);
	App->render->Blit(ButtonText, pos.x + tex_width / 2, pos.y + tex_height / 2, 1, 1, false);

}