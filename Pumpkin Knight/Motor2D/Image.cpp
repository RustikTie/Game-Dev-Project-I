#include "Image.h"
#include "j1App.h"
#include "j1Render.h"


Image::Image(int x, int y, ElementType type, SDL_Rect rec):Element(x,y,type)
{
	this->rec = rec;
}


Image::~Image()
{
}

void Image::Draw()
{
	App->render->Blit(App->gui->GetGuiAtlas(), pos.x, pos.y, 1, 1, false, &rec);
}