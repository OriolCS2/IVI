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

	Animation LoadGigantAliensAnimations(int playernumber, pugi::xml_node&, p2SString NameAnim) const;
	void MainMenu();
	void CreateMainMenu();
	void SettingsMenu(float dt);
	void CreateSettingsButtons();
	void CreateIntro();
	void WantToDisappearMainMenu(bool Disappear);


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
	UI_Element* buttonSTART = nullptr;
	UI_Element* buttonSETTINGS = nullptr;
	UI_Element* buttonEXIT = nullptr;


	//SETTINGS
	UI_Element* buttonGOBACKSETTINGS = nullptr;
	UI_Element* imageSETTINGS = nullptr;
	UI_Element* checkboxFPS = nullptr;
	UI_Element* labelFPS = nullptr;
	SDL_Texture* Settings = nullptr;
	UI_Element* sliderVOLUMEMUSIC = nullptr;
	UI_Element* labelMUSICVOLUME = nullptr;
	UI_Element* sliderVOLUMEFX = nullptr;
	UI_Element* labelSETTINGS = nullptr;
	UI_Element* labelVOLUMEFX = nullptr;
	UI_Element* labelGODMODE = nullptr;
	UI_Element* checkboxGODMODE = nullptr;
	UI_Element* sliderGENERALSOUND = nullptr;
	UI_Element* labelGENERALSOUND = nullptr;
	UI_Element* checkboxSOUND = nullptr;
	UI_Element* labelSOUND = nullptr;
	int x = 170;
	int y = 950;

	//PLAYER UI

	UI_Element* image = nullptr;
	UI_Element* label = nullptr;

	// 
	

};

#endif //
