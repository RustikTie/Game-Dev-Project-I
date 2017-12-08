#include "Text.h"



Text::Text(int x, int y, ElementType type, const char* text) :Element(x, y, type)
{
	this->text = text;
}


Text::~Text()
{
}

void Text::Draw()
{

}
