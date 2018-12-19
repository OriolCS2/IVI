#ifndef __J1MENU_H__
#define __J1MENU_H__

#include "j1Module.h"
#include "p2Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct SDL_Rect;
class UI_Element;

class j1Menu : public j1Module
{
public:

	j1Menu();

	// Destructor
	virtual ~j1Menu();

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

	void MainMenu();
	void CreateMainMenu();
	void CreateIntro();
	void WantToDisappearMainMenu(bool Disappear);
;

public:

	

	SDL_Texture* Choose = nullptr;
	p2SString ChooseFx;
	p2SString IntroFx;

	bool start = false;
	SDL_Texture * ScreenStart = nullptr;
	p2SString file_texture;
	iPoint mouse;
	int playernumber = -1;
	int MinY_ChooseRect = 0;
	int MaxY_ChooseRect = 0;
	int MinX_RectChoosePlayer1 = 0;
	int MaxX_RectChoosePlayer1 = 0;
	int MinX_RectChoosePlayer2 = 0;
	int MaxX_RectChoosePlayer2 = 0;
	int MinX_RectChoosePlayer3 = 0;
	int MaxX_RectChoosePlayer3 = 0;
	int PlayerNumber1 = 0;
	int PlayerNumber2 = 0;
	int PlayerNumber3 = 0;
	bool GameOn = false;
	bool repeat = false;
	bool repeat2 = false;
	bool repeat3 = false;
	bool FirstUpdate = true;
	bool GoStart = false;
	bool GoStartSaved = false;
	bool StartChoosing = false;
	bool InMainMenu = true;
	bool AlreadyChoosen = false;
	bool Exit = false;
	bool InSettings = false;
	bool Positioned = false;
	bool SettingMenuDone = false;
	bool InHacks = false;
	bool positioned = false;
	bool HacksMenuDone = false;
	bool InCredits = false;

	unsigned int choosefx;
	unsigned int introfx;

	//START MENU
	UI_Element* Background = nullptr;
	UI_Element* Title = nullptr;
	UI_Element* sentence = nullptr;

	//INITIAL MENU
	UI_Element* MainTitle = nullptr;
	UI_Element* buttonSTARTControls1 = nullptr;
	UI_Element* buttonSTARTControls2 = nullptr;
	UI_Element* buttonEXIT = nullptr;

	//PLAYER UI

	UI_Element* image = nullptr;
	UI_Element* label = nullptr;

	// 
	

};

#endif //
