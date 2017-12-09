#include "Background.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Gui.h"


Background::Background(int x, int y, ElementType type, SDL_Rect rec) : Element(x, y, type)
{
	this->rec = rec;

}


Background::~Background()
{
}

void Background::Draw()
{

	App->render->Blit(App->gui->GetBackground(), pos.x, pos.y, 1, 1, false, &rec);

}
