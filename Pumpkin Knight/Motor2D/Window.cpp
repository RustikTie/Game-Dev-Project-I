#include "j1App.h"
#include "j1Render.h"
#include "Element.h"
#include "Window.h"
#include "p2List.h"
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
	App->render->Blit(App->gui->GetGuiAtlas(), 125, 100, 0.7f, 0.7f, false, &rec, NULL);
}

void Window::Move()
{
	p2List_item<Element*>* item; 

	//move window

	for (item = linked_elements.start; item != NULL; item = item->next)
	{
		//move items inside window
	}
}