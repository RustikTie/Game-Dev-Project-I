#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "Element.h"


class Background : public Element
{
public:
	Background(int x, int y, ElementType type, SDL_Rect rec);
	~Background();
	void Draw();

public:
	bool isAnimated = false;
	SDL_Rect rec;
	SDL_Texture* tex = nullptr;

};

#endif // !__BACKGROUND_H__