#include "Text.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Window.h"
#include "j1Fonts.h"
#include "j1Gui.h"


Text::Text(int x, int y, ElementType type, bool show, const char* text) :Element(x, y, type)
{
	if (text != nullptr)
	{
		this->text = text;
		tex = App->font->Print(this->text, { 0, 0, 0 }, App->gui->credits_font);
	}
	this->show = show;
}


Text::~Text()
{

}

void Text::Draw()
{
	if (show)
	{
		App->render->Blit(tex, pos.x, pos.y, 1.0f, 1.0f, false);
	}
}

void Text::EditText(char* text)
{
	tex = App->font->Print(text, { 0,0,0 }, App->gui->credits_font);
}