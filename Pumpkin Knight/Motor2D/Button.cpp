#include "Button.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Window.h"
#include "j1Gui.h"


Button::Button(int x, int y, ElementType type, SDL_Rect rec, const char* text, SDL_Texture* tex, _TTF_Font* font) : Element(x, y, type)
{
	this->rec = rec;
	this->text = text;
	this->tex = tex;
	this->font = font;

	App->tex->GetSize(this->tex, tex_width, tex_height);
}


Button::~Button()
{

}

void Button::OnClick()
{

}

void Button::OnHover()
{

}

void Button::Draw()
{
	App->render->Blit(tex, pos.x, pos.y, 1, 1, false, &rec, NULL);
	SDL_Texture* textPrint = App->font->Print(text, { (255),(255),(255),(255) }, font);
	App->render->Blit(textPrint, pos.x + 1, pos.y + 2, 1, 1, false, &rec, NULL);
}

