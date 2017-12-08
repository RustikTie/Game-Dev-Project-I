#ifndef __TEXT_H__
#define __TEXT_H__

#include "Element.h"
#include "j1Fonts.h"


class Text : public Element
{
public:
	Text(int x, int y, ElementType type, const char* text);
	~Text();

	void Draw();

private:

	const char* text;

};

#endif // !__TEXT_H__
