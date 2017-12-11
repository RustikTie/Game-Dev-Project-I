#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Element.h"
#include "j1Fonts.h"
#include "p2SString.h"
#include "Animation.h"

class Button : public Element
{
public:
	Button(int x, int y, ElementType type, SDL_Rect rec, const char* text, _TTF_Font* font);
	~Button();

	void OnClick();
	void OnHover();
	void Draw();

private:

	Animation* curr = nullptr;
	Animation idle;
	Animation hover;
	Animation click;
	Animation locked;

	bool isClicked = false;
	SDL_Rect rec;
	const char* text = nullptr;
	_TTF_Font* font = nullptr;
};

#endif // !__BUTTON_H__
