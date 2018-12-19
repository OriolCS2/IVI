#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1Menu.h"
#include "Player.h"
#include "j1Collision.h"
#include "j1FadeToBlack.h"
#include "Button.h"
#include "UI_Element.h"
#include "Image.h"
#include "UI_Manager.h"

#include "Brofiler/Brofiler.h"

j1Menu::j1Menu() : j1Module()
{
	name.create("choose");
}

// Destructor
j1Menu::~j1Menu()
{}

// Called before render is available
bool j1Menu::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	file_texture = config.child("Start").text().as_string();
	MinY_ChooseRect = config.child("MinY_ChooseRect").attribute("value").as_int();
	MaxY_ChooseRect = config.child("MaxY_ChooseRect").attribute("value").as_int();
	MinX_RectChoosePlayer1 = config.child("MinX_RectChoosePlayer1").attribute("value").as_int();
	MaxX_RectChoosePlayer1 = config.child("MaxX_RectChoosePlayer1").attribute("value").as_int();
	MinX_RectChoosePlayer2 = config.child("MinX_RectChoosePlayer2").attribute("value").as_int();
	MaxX_RectChoosePlayer2 = config.child("MaxX_RectChoosePlayer2").attribute("value").as_int();
	MinX_RectChoosePlayer3 = config.child("MinX_RectChoosePlayer3").attribute("value").as_int();
	MaxX_RectChoosePlayer3 = config.child("MaxX_RectChoosePlayer3").attribute("value").as_int();
	PlayerNumber1 = config.child("PlayerNumber1").attribute("value").as_int();
	PlayerNumber2 = config.child("PlayerNumber2").attribute("value").as_int();
	PlayerNumber3 = config.child("PlayerNumber3").attribute("value").as_int();
	ChooseFx= config.child("ChooseFx").text().as_string();
	IntroFx = config.child("IntroFx").text().as_string();



	
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Menu::Start()
{
	App->scene->active = false;
	//App->player->active = false;
	App->collision->active = false;

	GameOn = false;
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	start = false;


	ScreenStart = App->tex->Load(file_texture.GetString());
	Settings = App->tex->Load("textures/Settings.png");
	choosefx = App->audio->LoadFx(ChooseFx.GetString());
	introfx = App->audio->LoadFx(IntroFx.GetString());
	CreateMainMenu();
	CreateSettingsButtons();
	CreateIntro();
	WantToDisappearMainMenu(true);
	App->player->EnemiesKilled = 0;
	return true;
}

// Called each loop iteration
bool j1Menu::PreUpdate()
{
	BROFILER_CATEGORY("Menu: PreUpdate", Profiler::Color::Aquamarine);
	App->input->GetMousePosition(mouse.x, mouse.y);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !GameOn && !start) {
		start = true;
		App->audio->PlayFx(introfx);	
		App->ui_manager->DeleteUI_Element(Title);
		App->ui_manager->DeleteUI_Element(sentence);
		WantToDisappearMainMenu(false);
		buttonSETTINGS->NoUse = true;
		buttonSETTINGS->WantToRender = false;
		//CreateMainMenuButtons();
		//CreateButtons();
	}
	return true;
}

// Called each loop iteration
bool j1Menu::Update(float dt)
{
	BROFILER_CATEGORY("Menu: Update", Profiler::Color::Aquamarine);
	if (start) {
		if (!GameOn) {
			if (InSettings)
				SettingsMenu(dt);
			if (InMainMenu)
				MainMenu();
		}
	}

	return true;
}

// Called each loop iteration
bool j1Menu::PostUpdate()
{
	BROFILER_CATEGORY("Menu: PostUpdate", Profiler::Color::Aquamarine);
	bool ret = true;
	if (!GameOn) {
		if (Exit)
			ret = false;
	}
	if (GoStart) {
		if (App->fade->current_step==App->fade->fade_from_black) {
			App->scene->ResetRounds();
			App->ui_manager->DeleteAllUI();
			App->scene->active = true;
			App->collision->active = true;
			GoStart = false;
			App->scene->Time = SDL_GetTicks();
			App->scene->StartRound1 = true;
			App->scene->SpawnEnemies(1);
			App->player->Start();
			App->scene->rounds = App->ui_manager->CreateLabel(350, 10, "ROUND 1", 40, false);
			GameOn = true;
		}
	}
	return ret;
}

// Called before quitting
bool j1Menu::CleanUp()
{
	App->tex->UnLoad(ScreenStart);
	LOG("Freeing scene");
	return true;
}

//MENU
void j1Menu::CreateIntro()
{
	Background = App->ui_manager->CreateImage(0, 0, false);
	Background->SetSpritesData({ 0,1158,1024,900 });
	Title = App->ui_manager->CreateImage((App->win->width / 2) - (354 / 2), 70, false);
	Title->SetSpritesData({ 0,783,354,305 });
	sentence = App->ui_manager->CreateImage((App->win->width / 2) - (268 / 2), 550, false);
	sentence->SetSpritesData({ 0,1105,268,35 });
}

void j1Menu::CreateMainMenu()
{
	AlreadyChoosen = false;
	MainTitle = App->ui_manager->CreateImage((App->win->width / 2) - (844 / 2), 70, false);
	MainTitle->SetSpritesData({ 401,784,844	,165 });
	MainTitle->type = BUTTON;
	buttonSTART = App->ui_manager->CreateButton(310, 370, 1, nullptr, "START", 30);
	buttonSETTINGS = App->ui_manager->CreateButton(310, 470, 1, nullptr, "SETTINGS", 30);
	buttonEXIT = App->ui_manager->CreateButton(310, 570, 1, nullptr, "EXIT", 30);
}

void j1Menu::MainMenu()
{
	if (buttonSTART->pressed) {
		App->fade->FadeToBlack(3.0f);
		WantToDisappearMainMenu(true);
		InMainMenu = false;
		GoStart = true;
		SDL_ShowCursor(SDL_DISABLE);
	}
	if (buttonSETTINGS->pressed) {
		SettingMenuDone = false;
		Positioned = false;
		buttonSTART->NoUse = true;
		buttonSETTINGS->NoUse = true;
		buttonEXIT->NoUse = true;
		InMainMenu = false;
		InSettings = true;
		if (App->capactivated)
			checkboxFPS->pressed = true;
		else checkboxFPS->pressed = false;

	}
	if (buttonEXIT->pressed) {
		Exit = true;
	}
}


void j1Menu::WantToDisappearMainMenu(bool Disappear)
{
	if (Disappear) {
		buttonSTART->NoUse = true;
		buttonSETTINGS->NoUse = true;
		buttonEXIT->NoUse = true;
		buttonSTART->WantToRender = false;
		buttonSETTINGS->WantToRender = false;
		buttonEXIT->WantToRender = false;
		MainTitle->WantToRender = false;
	}
	else {
		buttonSTART->NoUse = false;
		buttonSETTINGS->NoUse = false;
		buttonEXIT->NoUse = false;
		buttonSTART->WantToRender = true;
		buttonSETTINGS->WantToRender = true;
		buttonEXIT->WantToRender = true;
		MainTitle->WantToRender = true;
	}
}






void j1Menu::CreateSettingsButtons()
{
	SettingMenuDone = false;
	imageSETTINGS = App->ui_manager->CreateImage(170, 1000, true);
	imageSETTINGS->SetSpritesData({ 758,0,705,671 });
	imageSETTINGS->type = BUTTON;
	buttonGOBACKSETTINGS = App->ui_manager->CreateButton(37, 40, 3, imageSETTINGS);
	buttonGOBACKSETTINGS->SetSpritesData({ 559,0,39,31 }, { 652,0,39,31 }, { 608,0,39,28 });
	checkboxFPS = App->ui_manager->CreateCheckBox(380, 157, imageSETTINGS);
	labelFPS = App->ui_manager->CreateLabel(100, 150, "CAP FPS TO 30", 50, true, imageSETTINGS);
	sliderVOLUMEMUSIC = App->ui_manager->CreateSlider(380, 452, App->audio->volume, imageSETTINGS);
	labelMUSICVOLUME = App->ui_manager->CreateLabel(100, 450, "MUSIC VOLUME", 50, true, imageSETTINGS);
	sliderVOLUMEFX = App->ui_manager->CreateSlider(380, 552, App->audio->fxvolume, imageSETTINGS);
	labelVOLUMEFX = App->ui_manager->CreateLabel(100, 550, "FX VOLUME", 50, true, imageSETTINGS);
	labelSETTINGS = App->ui_manager->CreateLabel(imageSETTINGS->width / 2, 50, "SETTINGS", 60, true, imageSETTINGS);
	labelSETTINGS->Local_pos.x -= labelSETTINGS->width / 2;
	labelGENERALSOUND = App->ui_manager->CreateLabel(100, 350, "GENERAL SOUND", 50, true, imageSETTINGS);
	sliderGENERALSOUND = App->ui_manager->CreateSlider(380, 352, 50, imageSETTINGS);
	checkboxSOUND = App->ui_manager->CreateCheckBox(380, 257, imageSETTINGS);
	if (!App->audio->NoAudio)
		checkboxSOUND->pressed = true;
	else checkboxSOUND->pressed = false;
	labelSOUND = App->ui_manager->CreateLabel(100, 250, "SOUND", 50, true, imageSETTINGS);
	if (App->capactivated)
		checkboxFPS->pressed = true;
}


void j1Menu::SettingsMenu(float dt)
{
	Title->NoRenderLabel = true;
	sentence->NoRenderLabel = true;
	if (imageSETTINGS->Local_pos.y <= buttonEXIT->Local_pos.y + buttonEXIT->height) {
		buttonEXIT->WantToRender = false;
	}
	if (imageSETTINGS->Local_pos.y <= buttonSETTINGS->Local_pos.y + buttonSETTINGS->height) {
		buttonSETTINGS->WantToRender = false;
	}
	if (imageSETTINGS->Local_pos.y <= buttonSTART->Local_pos.y + buttonSTART->height) {
		buttonSTART->WantToRender = false;
	}
	if (imageSETTINGS->Local_pos.y >= buttonEXIT->Local_pos.y) {
		buttonEXIT->WantToRender = true;
	}
	if (imageSETTINGS->Local_pos.y >= buttonSETTINGS->Local_pos.y) {
		buttonSETTINGS->WantToRender = true;
	}
	if (imageSETTINGS->Local_pos.y >= buttonSTART->Local_pos.y) {
		buttonSTART->WantToRender = true;
	}
	if (!Positioned && !SettingMenuDone) { //MENU GOING UP
		imageSETTINGS->Local_pos.y -= 1000 * dt;
		if (imageSETTINGS->Local_pos.y <= 100) {
			Positioned = true;
			//buttonGOBACKSETTINGS->pressed = false;
			SettingMenuDone = true;
		}
	}
	if (!Positioned && SettingMenuDone) { //MENU GOING DOWN

		imageSETTINGS->Local_pos.y += 2000 * dt;
		if (imageSETTINGS->Local_pos.y >= 1225) {
			buttonSTART->NoUse = false;
			buttonSETTINGS->NoUse = false;
			buttonEXIT->NoUse = false;
			InSettings = false;
			InMainMenu = true;
		}
	}
	if (SettingMenuDone) { //MENU LOGIC BUTTONS
		if (buttonGOBACKSETTINGS->pressed) {
			Positioned = false;
		}
	
		if (checkboxFPS->pressed) {
			App->capactivated = true;
		}
		if (!checkboxFPS->pressed) {
			App->capactivated = false;
		}
		if (checkboxSOUND->pressed) {
			App->audio->NoAudio = false;
			sliderGENERALSOUND->NoUse = false;
			sliderVOLUMEMUSIC->NoUse = false;
			sliderVOLUMEFX->NoUse = false;
			App->audio->general = sliderGENERALSOUND->Value;
			App->audio->volume = sliderVOLUMEMUSIC->Value;
			App->audio->fxvolume = sliderVOLUMEFX->Value;
		}
		else {
			App->audio->NoAudio = true;
			sliderGENERALSOUND->NoUse = true;
			sliderVOLUMEMUSIC->NoUse = true;
			sliderVOLUMEFX->NoUse = true;
		}
	}
}









