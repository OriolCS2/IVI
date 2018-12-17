#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "UI_Manager.h"
#include "UI_Element.h"
#include "j1Scene.h"
#include "Player.h"
#include "j1Collision.h"
#include "j1Menu.h"
#include "ModuleEnemies.h"
#include "j1FadeToBlack.h"

#include "Brofiler/Brofiler.h"

j1Scene::j1Scene() : j1Module()
{
	
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");


	bool ret = true;
	
	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	BROFILER_CATEGORY("Scene: Start", Profiler::Color::LightYellow);
	space = App->tex->Load("textures/space.png");
	
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	BROFILER_CATEGORY("Scene: PreUpdate", Profiler::Color::LightYellow);
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("Scene: Update", Profiler::Color::LightYellow);
	
	App->render->Blit(space, 0, 0, NULL);

	// SE LI HA DE DIR AL XAN
	// IMPORTANT
	// SHA DESTUDIAR QUE LA GENT SEGUR QUE AL PRINCIPI ANIRA A MATAR I DISPARAR ENEMICS 
	// I A MESURA QUE NO SHO PASSI COMENÇARA A SUDAR DE MATAR I ANIRA A ESQUIVAR
	// IMPORTANT

	if (SDL_GetTicks() - Time >= 4000 && !SpawnRound2) {
		Time = SDL_GetTicks();
		SpawnRound2 = true;
		SpawnEnemies(2);
	}

	if (SDL_GetTicks() - Time >= 4000 && !SpawnRound3) { //ULITMA OLEADA DE LA RONDA 1
		Time = SDL_GetTicks();
		SpawnRound3 = true;
		SpawnEnemies(3);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	BROFILER_CATEGORY("Scene: PostUpdate", Profiler::Color::LightYellow);
	bool ret = true;


	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	App->tex->UnLoad(space);
	LOG("Freeing scene");
	return true;
}


void j1Scene::SpawnEnemies(int Round)
{


	if (Round == 1) {
		App->enemies->AddEnemy(LINE, 100, -700, 0);
		App->enemies->AddEnemy(LINE, 400, -500, 0);
		App->enemies->AddEnemy(LINE, 320, -900, 0);
		App->enemies->AddEnemy(LINE, 610, -400, 0);
		App->enemies->AddEnemy(LINE, 480, -700, 0);
		App->enemies->AddEnemy(LINE, 543, -650, 0);
		App->enemies->AddEnemy(LINE, 710, -570, 0);
		App->enemies->AddEnemy(LINE, 735, -800, 0);

		App->enemies->AddEnemy(LINE, 100, -400, 0);
		App->enemies->AddEnemy(LINE, 170, -530, 0);
		App->enemies->AddEnemy(LINE, 260, -600, 0);
		App->enemies->AddEnemy(LINE, 410, -830, 0);
		App->enemies->AddEnemy(LINE, 180, -970, 0);
		App->enemies->AddEnemy(LINE, 443, -450, 0);
		App->enemies->AddEnemy(LINE, 510, -570, 0);
		App->enemies->AddEnemy(LINE, 375, -640, 0);
	}
	if (Round == 2) {
		App->enemies->AddEnemy(LINE, -400, 400, 3);
		App->enemies->AddEnemy(LINE, -770, 500, 3);
		App->enemies->AddEnemy(LINE, -900, 200, 3);
		App->enemies->AddEnemy(LINE, -1050, 400, 3);
		App->enemies->AddEnemy(LINE, -500, 600, 3);
		App->enemies->AddEnemy(LINE, -650, 650, 3);
		App->enemies->AddEnemy(LINE, -980, 570, 3);
		App->enemies->AddEnemy(LINE, -1100, 100, 3);

		App->enemies->AddEnemy(LINE, -490, 400, 3);
		App->enemies->AddEnemy(LINE, -690, 330, 3);
		App->enemies->AddEnemy(LINE, -730, 600, 3);
		App->enemies->AddEnemy(LINE, -210, 430, 3);
		App->enemies->AddEnemy(LINE, -1000, 270, 3);
		App->enemies->AddEnemy(LINE, -820, 450, 3);
		App->enemies->AddEnemy(LINE, -650, 470, 3);
		App->enemies->AddEnemy(LINE, -890, 240, 3);
	}
	if (Round == 3) {
		App->enemies->AddEnemy(LINE, 100, -700, 0);
		App->enemies->AddEnemy(LINE, 300, -500, 0);
		App->enemies->AddEnemy(LINE, 320, -900, 0);
		App->enemies->AddEnemy(LINE, 210, -400, 0);
		App->enemies->AddEnemy(LINE, 280, -700, 0);
		App->enemies->AddEnemy(LINE, 543, -650, 0);
		App->enemies->AddEnemy(LINE, 510, -570, 0);
		App->enemies->AddEnemy(LINE, 475, -800, 0);

		App->enemies->AddEnemy(LINE, 500, -400, 0);
		App->enemies->AddEnemy(LINE, 670, -530, 0);
		App->enemies->AddEnemy(LINE, 460, -600, 0);
		App->enemies->AddEnemy(LINE, 210, -830, 0);
		App->enemies->AddEnemy(LINE, 180, -970, 0);
		App->enemies->AddEnemy(LINE, 343, -450, 0);
		App->enemies->AddEnemy(LINE, 610, -570, 0);
		App->enemies->AddEnemy(LINE, 275, -640, 0);
	}


	
	
}

void j1Scene::ResetRounds()
{
	App->player->RONDA = 1;
	SpawnRound2 = false;
	SpawnRound3 = false;
}




