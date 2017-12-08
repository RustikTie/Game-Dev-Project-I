#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "p2List.h"
#include "p2Log.h"
#include "j1Module.h"
#include "p2DynArray.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes
enum ELEMENT_TYPES
{
	BACKGROUND,
	TEXT_BOX,
	BUTTON,
	IMAGE,
	TEXT,
	NOTYPE
};

class SDL_Texture;
class SDL_Rect;
class Elements;
class _TTF_Font;

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions
	/*void AddBackground(int x, int y, ELEMENT_TYPES types);
	void AddButton(int x, int y, ELEMENT_TYPES types, const char* text);
	void AddText(int x, int y, ELEMENT_TYPES types, const char* text);
	void AddTextBox(int x, int y, ELEMENT_TYPES types, const char* text);*/

	const SDL_Texture* GetAtlas() const;
	SDL_Texture* GetBackground() const;
	SDL_Texture* GetButton() const;

	p2List<Elements*> elements;
	p2DynArray<_TTF_Font*> fonts;
	SDL_Texture* background = nullptr;
	SDL_Texture* button = nullptr;
	SDL_Texture* box = nullptr;
	_TTF_Font* font = nullptr;

private:


	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__