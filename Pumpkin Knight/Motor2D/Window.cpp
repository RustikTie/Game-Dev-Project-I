#include "j1App.h"
#include "j1Render.h"
#include "Element.h"
#include "Window.h"
#include "j1Gui.h"

// window coords {16, 528, 457, 485 }
Window::Window(int x, int y, ElementType type, SDL_Rect rec) : Element(x, y, type)
{
	this->rec = rec;
	this->tex = GetAtlas();
}

Window::~Window()
{
}

void Window::LinkElement(Element* elem)
{
	linked_elements.add(elem);
}

void Window::Draw()
{
	App->render->Blit(tex, 300, 300, 1, 1, false, &rec, NULL);
}