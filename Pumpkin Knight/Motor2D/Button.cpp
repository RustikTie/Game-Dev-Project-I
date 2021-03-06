
#include "Button.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Window.h"
#include "j1Fonts.h"
#include "j1Gui.h"

Button::Button(int x, int y, ElementType types, bool show, SDL_Rect* rec, const char* text) : Element(x, y, types)
{
	if (text != nullptr)
	{
		buttontext = text;
		ButtonText = App->font->Print(buttontext, { 255, 255, 255 }, App->gui->font);
	}

	texture_rect = rec;
	ButtonBox = App->gui->GetAtlas();
	tex_width = rec->w;
	tex_height = rec->h;

	this->show = show;
}


Button::~Button()
{

}

void Button::Draw()
{
	if (show)
	{
		int rect_x = pos.x - App->render->camera.x;
		int rect_y = pos.y - App->render->camera.y;

		debug_rect = { rect_x, rect_y, (int)(tex_width*0.5f), (int)(tex_height*0.5f) };

		App->render->Blit(ButtonBox, pos.x, pos.y, 0.5f, 0.5f, false, texture_rect);
		App->render->Blit(ButtonText, pos.x + (tex_width / 6), pos.y + (tex_height / 7), 1, 1, false);
		if (debug == true)
		{
			App->render->DrawQuad(debug_rect, 0, 255, 0, 50);
		}
	}
}