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

	App->player->Controls = false;

	ScreenStart = App->tex->Load(file_texture.GetString());
	choosefx = App->audio->LoadFx(ChooseFx.GetString());
	introfx = App->audio->LoadFx(IntroFx.GetString());
	CreateMainMenu();
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
			App->scene->rounds->ChangeLabel("ROUND 1", 40);
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
	buttonSTARTControls1 = App->ui_manager->CreateButton(150, 370, 1, nullptr, "CONTROLS 1", 30);
	buttonSTARTControls2 = App->ui_manager->CreateButton(150, 470, 1, nullptr, "CONTROLS 2", 30);
	buttonEXIT = App->ui_manager->CreateButton(150, 570, 1, nullptr, "EXIT", 30);
	label2 = App->ui_manager->CreateLabel(400, 350, "MOVIMIENTO: W A S D",30,true);
	label3 = App->ui_manager->CreateLabel(400, 380, "DISPARO: ESPACIO", 30, true);
	label4 = App->ui_manager->CreateLabel(400, 410, "DIRECCION DISPARO: FLECHAS", 30, true);
	label5 = App->ui_manager->CreateLabel(400, 450, "MOVIMIENTO: RATON", 30, true);
	label6 = App->ui_manager->CreateLabel(400, 480, "DISPARO: BOTON IZQUIERDO RATON", 30, true);
	label7 = App->ui_manager->CreateLabel(400, 510, "DIRECCION DISPARO: W A S D", 30, true);
}

void j1Menu::MainMenu()
{
	if (buttonSTARTControls1->pressed) {
		App->fade->FadeToBlack(3.0f);
		WantToDisappearMainMenu(true);
		InMainMenu = false;
		GoStart = true;
		App->player->Controls = true;
		SDL_ShowCursor(SDL_DISABLE);
	}
	if ( buttonSTARTControls2->pressed) {
		App->fade->FadeToBlack(3.0f);
		WantToDisappearMainMenu(true);
		InMainMenu = false;
		GoStart = true;
		SDL_ShowCursor(SDL_DISABLE);
	}

	if (buttonEXIT->pressed) {
		Exit = true;
	}
}


void j1Menu::WantToDisappearMainMenu(bool Disappear)
{
	if (Disappear) {
		buttonSTARTControls1->NoUse = true;
		buttonSTARTControls2->NoUse = true;
		buttonEXIT->NoUse = true;
		buttonSTARTControls1->WantToRender = false;
		buttonSTARTControls2->WantToRender = false;
		label2->WantToRender = false;
		label3->WantToRender = false;
		label4->WantToRender = false;
		label5->WantToRender = false;
		label6->WantToRender = false;
		label7->WantToRender = false;
		buttonEXIT->WantToRender = false;
		MainTitle->WantToRender = false;
	}
	else {
		buttonSTARTControls1->NoUse = false;
		buttonSTARTControls2->NoUse = false;
		buttonEXIT->NoUse = false;
		buttonSTARTControls1->WantToRender = true;
		buttonSTARTControls2->WantToRender = true;
		label2->WantToRender = true;
		label3->WantToRender = true;
		label4->WantToRender = true;
		label5->WantToRender = true;
		label6->WantToRender = true;
		label7->WantToRender = true;
		buttonEXIT->WantToRender = true;
		MainTitle->WantToRender = true;
	}
}





