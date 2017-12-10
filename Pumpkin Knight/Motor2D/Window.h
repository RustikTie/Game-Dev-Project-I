#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Element.h"
#include "p2List.h"


class Window : public Element
{
public:
	Window(int x, int y, ElementType type, SDL_Rect rec);

	void LinkElement(Element* elem);
	void Draw();
	void Move();
	~Window();

private:
	SDL_Rect rec;
	SDL_Texture* tex = nullptr;
	p2List<Element*> linked_elements;
};

#endif // !__WINDOW_H__
