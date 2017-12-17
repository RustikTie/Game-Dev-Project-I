#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Element.h"

class Image : public Element
{
public:
	Image(int x, int y, ElementType type, bool show, SDL_Rect rec);
	~Image();
	void Draw();
private: 
	SDL_Rect rec;
};

#endif // !__IMAGE_H__
