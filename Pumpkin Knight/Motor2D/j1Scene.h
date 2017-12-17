#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "p2DynArray.h"
#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
class Element;
enum SCENE
{
	MENU,
	LVL1,
	LVL2,
	CREDITS,
	OPTIONS,
};

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&)const;

	bool MouseEvents(Element* element);

	bool checkSaveFile();

	void TimerUpdate(uint32 time);

	p2DynArray<iPoint> path;
	bool start = true;

	
	Element* Candies = nullptr;
	Element* CandyCount = nullptr;
	Element* Score = nullptr;
	Element* ScoreCount = nullptr;
	Element* Counter = nullptr;
	Element* CounterTimer = nullptr;

	bool maycontinue = false;
private:
	int volume = 50;
	int button_click;
	uint32 start_counter = 0;
	uint32 curr_counter = 0;

	SDL_Rect screen = { 0, 0, 1024, 764 };
	uint32 currSec = 0;
	uint32 currMin = 0;
	uint32 currHour = 0;
	uint32 currSec2 = 0;
	uint32 currMin2 = 0;
	uint32 currHour2 = 0;

	bool exit = true;
	bool level1 = false;
	bool level2 = false;
	bool credits = false;
	bool options = false;
	bool transitioning = false;


	SCENE previousScene;

	SDL_Rect hover;
	SDL_Rect idle;
	SDL_Rect click;
	SDL_Rect rect_window;
	SDL_Rect plus_hover;
	SDL_Rect plus_idle;
	SDL_Rect plus_click;
	SDL_Rect minus_hover;
	SDL_Rect minus_idle;
	SDL_Rect minus_click;

	SDL_Texture* transition = nullptr;
	Animation* _anim = nullptr;
	Animation backToBlack;
	bool _transitioning = false;

	char currScore[100];
	char currCandies[100];
	char currTime[100];

	Element* Background = nullptr;
	Element* Continue = nullptr;
	Element* StartButton = nullptr;
	Element* QuitButton = nullptr;
	Element* Options = nullptr;
	Element* Credits = nullptr;
	Element* BigWindow = nullptr;
	Element* Menu_Credits = nullptr;
	Element* Menu_Options = nullptr;
	Element* OptionsTitle = nullptr;
	Element* CreditTitle = nullptr;
	Element* CreditText = nullptr;
	Element* CreditText1 = nullptr;
	Element* CreditText2 = nullptr;
	Element* CreditText3 = nullptr;
	Element* CreditText4 = nullptr;
	Element* CreditText5 = nullptr;
	Element* CreditText6 = nullptr;
	Element* CreditText7 = nullptr;
	Element* CreditText8 = nullptr;
	Element* CreditText9 = nullptr;
	Element* CreditText10 = nullptr;
	Element* CreditText11 = nullptr;
	Element* CreditText12 = nullptr;
	Element* CreditText13 = nullptr;
	Element* CreditText14 = nullptr;
	Element* Plus = nullptr;
	Element* Minus = nullptr;
	Element* FXPlus = nullptr;
	Element* FXMinus = nullptr;
	Element* MusicVol = nullptr;
	Element* FXVol = nullptr;
	
};

#endif // __j1SCENE_H__