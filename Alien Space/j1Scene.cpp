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
	space = App->tex->Load("textures/space.png");
	App->audio->PlayMusic("audio/music/Space Cube.ogg");

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	App->render->Blit(space, 0, 0, NULL);

	// SE LI HA DE DIR AL XAN
	// IMPORTANT
	// SHA DESTUDIAR QUE LA GENT SEGUR QUE AL PRINCIPI ANIRA A MATAR I DISPARAR ENEMICS 
	// I A MESURA QUE NO SHO PASSI COMENÇARA A SUDAR DE MATAR I ANIRA A ESQUIVAR
	// IMPORTANT

	//RONDA 1
	if (SDL_GetTicks() - Time >= 4000 && !SpawnRound2) { //OLEADA 2 RONDA 1
		Time = SDL_GetTicks();
		SpawnRound2 = true;
		SpawnRound3 = false;
		SpawnEnemies(2);
	}
	if (SDL_GetTicks() - Time >= 4000 && !SpawnRound3) { //ULITMA OLEADA DE LA RONDA 1
		Time = SDL_GetTicks();
		SpawnRound3 = true;
		SpawnRound4 = false;
		SpawnEnemies(3);
	}
	//

	//RONDA 2
	if (SDL_GetTicks() - Time >= 5000 && !SpawnRound4) { //OLEADA 1 RONDA 2
		if (!SaveXML_ROUND1) {
			SaveXML_ROUND1 = true;
			float J = App->player->EnemiesKilled;
			float H = App->player->ShootNum;
			App->player->Porcentaje = (J / H) * 100;
			if (App->player->Controls)
				App->player->Estadisticas.create("Archivos a enviar/EstadisticasControles_1_Round_1.xml");
			else
				App->player->Estadisticas.create("Archivos a enviar/EstadisticasControles_2_Round_1.xml");
			App->SaveGame(App->player->Estadisticas.GetString());
			rounds->ChangeLabel("ROUND 2", 40);
		}
		StartRound1 = false;
		StartRound2 = true;
		Time = SDL_GetTicks();
		SpawnRound4 = true;
		SpawnRound5 = false;
		SpawnEnemies(4);
	}
	if (SDL_GetTicks() - Time >= 4000 && !SpawnRound5) { //OLEADA 2 RONDA 2
		Time = SDL_GetTicks();
		SpawnRound5 = true;
		SpawnRound6 = false;
		SpawnEnemies(5);
	}
	if (SDL_GetTicks() - Time >= 7000 && !SpawnRound6) { //OLEADA 3 RONDA 2
		Time = SDL_GetTicks();
		SpawnRound6 = true;
		SpawnRound7 = false;
		SpawnEnemies(6);
	}

	//RONDA 3
	if (SDL_GetTicks() - Time >= 5000 && !SpawnRound7) { //OLEADA 1 RONDA 3
		if (!SaveXMLROUND2) {
			SaveXMLROUND2 = true;
			float J = App->player->EnemiesKilled;
			float H = App->player->ShootNum;
			App->player->Porcentaje = (J / H) * 100;
			if (App->player->Controls)
				App->player->Estadisticas.create("Archivos a enviar/EstadisticasControles_1_Round_2.xml");
			else
				App->player->Estadisticas.create("Archivos a enviar/EstadisticasControles_2_Round_2.xml");
			App->SaveGame(App->player->Estadisticas.GetString());
			rounds->ChangeLabel("ROUND 3", 40);
		}
		StartRound2 = false;
		StartRound3 = true;
		Time = SDL_GetTicks();
		SpawnRound7 = true;
		SpawnRound8 = false;
		SpawnEnemies(7);
	}
	if (SDL_GetTicks() - Time >= 3000 && !SpawnRound8) { //OLEADA 2 RONDA 3
		Time = SDL_GetTicks();
		SpawnRound8 = true;
		SpawnRound9 = false;
		SpawnEnemies(8);
	}
	if (SDL_GetTicks() - Time >= 3000 && !SpawnRound9) { //OLEADA 3 RONDA 3
		Time = SDL_GetTicks();
		SpawnRound9 = true;
		SpawnRound10 = false;
		SpawnEnemies(9);
	}

	//RONDA 4
	if (SDL_GetTicks() - Time >= 3000 && !SpawnRound10) { //OLEADA 1 RONDA 4
		if (!SaveXMLROUND3) {
			SaveXMLROUND3 = true;
			float J = App->player->EnemiesKilled;
			float H = App->player->ShootNum;
			App->player->Porcentaje = (J / H) * 100;
			if (App->player->Controls)
				App->player->Estadisticas.create("Archivos a enviar/EstadisticasControles_1_Round_3.xml");
			else
				App->player->Estadisticas.create("Archivos a enviar/EstadisticasControles_2_Round_3.xml");
			App->SaveGame(App->player->Estadisticas.GetString());
			rounds->ChangeLabel("ROUND 4", 40);
		}
		StartRound3 = false;
		StartRound4 = true;
		Time = SDL_GetTicks();
		SpawnRound10 = true;
		SpawnRound11 = false;
		SpawnEnemies(10);
	}
	if (SDL_GetTicks() - Time >= 3000 && !SpawnRound11) { //OLEADA 2 RONDA 4
		Time = SDL_GetTicks();
		SpawnRound11 = true;
		SpawnRound12 = false;
		SpawnEnemies(11);
	}
	if (SDL_GetTicks() - Time >= 3000 && !SpawnRound12) { //OLEADA 3 RONDA 4
		Time = SDL_GetTicks();
		SpawnRound12 = true;
		CanFinish = true;
		SpawnEnemies(12);
	}
	if (SDL_GetTicks() - Time >= 3000 && CanFinish) { 
		Time = SDL_GetTicks();
		SpawnRound12 = false;
		CanFinish = false;
		float J = App->player->EnemiesKilled;
		float H = App->player->ShootNum;
		App->player->Porcentaje = (J / H) * 100;
		if (App->player->Controls)
			App->player->Estadisticas.create("Archivos a enviar/EstadisticasControles_1_Round_4.xml");
		else
			App->player->Estadisticas.create("Archivos a enviar/EstadisticasControles_2_Round_4.xml");

		App->SaveGame(App->player->Estadisticas.GetString());
		App->enemies->DeleteEnemies();
		App->menu->InMainMenu = true;
		App->menu->GoStart = false;
		App->scene->active = false;
		App->collision->active = false;
		App->menu->start = true;
		App->menu->GameOn = false;
		App->menu->Start();
		App->ui_manager->DeleteUI_Element(App->scene->rounds);
		SDL_ShowCursor(SDL_ENABLE);
		
	}
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
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
		App->enemies->AddEnemy(LINE, 700, -700, 0);
		App->enemies->AddEnemy(LINE, 300, -500, 0);
		App->enemies->AddEnemy(LINE, 220, -900, 0);
		App->enemies->AddEnemy(LINE, 510, -400, 0);
		App->enemies->AddEnemy(LINE, 280, -700, 0);
		App->enemies->AddEnemy(LINE, 543, -650, 0);
		App->enemies->AddEnemy(LINE, 110, -570, 0);
		App->enemies->AddEnemy(LINE, 475, -800, 0);
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
	}
	if (Round == 3) {
		App->enemies->AddEnemy(LINE, 1000, 100, 2);
		App->enemies->AddEnemy(LINE, 1400, 500, 2);
		App->enemies->AddEnemy(LINE, 1320, 700, 2);
		App->enemies->AddEnemy(LINE, 1610, 400, 2);
		App->enemies->AddEnemy(LINE, 1480, 350, 2);
		App->enemies->AddEnemy(LINE, 1543, 450, 2);
		App->enemies->AddEnemy(LINE, 1210, 570, 2);
		App->enemies->AddEnemy(LINE, 1335, 200, 2);
	}

	if (Round == 4) {
		App->enemies->AddEnemy(LINE, 100, 900, 1);
		App->enemies->AddEnemy(LINE, 400, 1000, 1);
		App->enemies->AddEnemy(LINE, 320, 1100, 1);
		App->enemies->AddEnemy(LINE, 610, 950, 1);
		App->enemies->AddEnemy(LINE, 480, 1250, 1);
		App->enemies->AddEnemy(LINE, 543, 1150, 1);
		App->enemies->AddEnemy(LINE, 710, 1200, 1);
		App->enemies->AddEnemy(LINE, 735, 850, 1);
	}
	if (Round == 5) {
		App->enemies->AddEnemy(LINE, 1000, 700, 2);
		App->enemies->AddEnemy(LINE, 1400, 500, 2);
		App->enemies->AddEnemy(LINE, 1320, 700, 2);
		App->enemies->AddEnemy(LINE, 1610, 400, 2);
		App->enemies->AddEnemy(LINE, 1480, 200, 2);
		App->enemies->AddEnemy(LINE, 1543, 450, 2);
		App->enemies->AddEnemy(LINE, 1210, 570, 2);
		App->enemies->AddEnemy(LINE, 1335, 200, 2);

		App->enemies->AddEnemy(LINE, -1100, 400, 3);
		App->enemies->AddEnemy(LINE, -1170, 530, 3);
		App->enemies->AddEnemy(LINE, -1260, 600, 3);
		App->enemies->AddEnemy(LINE, -1410, 230, 3);
		App->enemies->AddEnemy(LINE, -1180, 170, 3);
		App->enemies->AddEnemy(LINE, -1443, 450, 3);
		App->enemies->AddEnemy(LINE, -1510, 370, 3);
		App->enemies->AddEnemy(LINE, -1375, 640, 3);
	}

	if (Round == 6) {
		App->enemies->AddEnemy(LINE, 100, 900, 1);
		App->enemies->AddEnemy(LINE, 400, 1000, 1);
		App->enemies->AddEnemy(LINE, 320, 1100, 1);
		App->enemies->AddEnemy(LINE, 610, 950, 1);
		App->enemies->AddEnemy(LINE, 480, 1250, 1);
		App->enemies->AddEnemy(LINE, 543, 1150, 1);
		App->enemies->AddEnemy(LINE, 710, 1200, 1);
		App->enemies->AddEnemy(LINE, 735, 850, 1);

		App->enemies->AddEnemy(LINE, 700, -700, 0);
		App->enemies->AddEnemy(LINE, 300, -500, 0);
		App->enemies->AddEnemy(LINE, 220, -900, 0);
		App->enemies->AddEnemy(LINE, 510, -400, 0);
		App->enemies->AddEnemy(LINE, 280, -700, 0);
		App->enemies->AddEnemy(LINE, 543, -650, 0);
		App->enemies->AddEnemy(LINE, 110, -570, 0);
		App->enemies->AddEnemy(LINE, 475, -800, 0);
	}

	if (Round == 7) {
		App->enemies->AddEnemy(LINE, -200, -100, 5);
		App->enemies->AddEnemy(LINE, 900, 900, 6);
		App->enemies->AddEnemy(LINE, 00, -100, 5);
		App->enemies->AddEnemy(LINE, 700, 900, 6);
		App->enemies->AddEnemy(LINE, 200, -100, 5);
		App->enemies->AddEnemy(LINE, 500, 900, 6);
		App->enemies->AddEnemy(LINE, -100, -200, 5);
		App->enemies->AddEnemy(LINE, 800, 1000, 6);
		App->enemies->AddEnemy(LINE, 100, -200, 5);
		App->enemies->AddEnemy(LINE, 600, 1000, 6);
		App->enemies->AddEnemy(LINE, 300, -200, 5);
		App->enemies->AddEnemy(LINE, 400, 1000, 6);
		App->enemies->AddEnemy(LINE, 00, -300, 5);
		App->enemies->AddEnemy(LINE, 700, 1100, 6);
		App->enemies->AddEnemy(LINE, 200, -300, 5);
		App->enemies->AddEnemy(LINE, 500, 1100, 6);
		App->enemies->AddEnemy(LINE, 400, -300, 5);
		App->enemies->AddEnemy(LINE, 300, 1100, 6);
	}
	if (Round == 8) {
		App->enemies->AddEnemy(LINE, 900, -100, 4);
		App->enemies->AddEnemy(LINE, -200, 900, 7);
		App->enemies->AddEnemy(LINE, 70, -100, 4);
		App->enemies->AddEnemy(LINE, 00, 900, 7);
		App->enemies->AddEnemy(LINE, 500, -100, 4);
		App->enemies->AddEnemy(LINE, 200, 900, 7);
		App->enemies->AddEnemy(LINE, 800, -200, 4);
		App->enemies->AddEnemy(LINE, -100, 1000, 7);
		App->enemies->AddEnemy(LINE, 600, -200, 4);
		App->enemies->AddEnemy(LINE, 100, 1000, 7);
		App->enemies->AddEnemy(LINE, 400, -200, 4);
		App->enemies->AddEnemy(LINE, 300, 1000, 7);
		App->enemies->AddEnemy(LINE, 700, -300, 4);
		App->enemies->AddEnemy(LINE, 00, 1100, 7);
		App->enemies->AddEnemy(LINE, 500, -300, 4);
		App->enemies->AddEnemy(LINE, 200, 1100, 7);
		App->enemies->AddEnemy(LINE, 300, -300, 4);
		App->enemies->AddEnemy(LINE, 400, 1100, 7);
	}
	if (Round == 9) {
		App->enemies->AddEnemy(LINE, -100, -100, 5);
		App->enemies->AddEnemy(LINE, 900, -100, 4);
		App->enemies->AddEnemy(LINE, -150, -100, 5);
		App->enemies->AddEnemy(LINE, 950, -100, 4);
		App->enemies->AddEnemy(LINE, -100, -150, 5);
		App->enemies->AddEnemy(LINE, 900, -150, 4);
		App->enemies->AddEnemy(LINE, -150, -150, 5);
		App->enemies->AddEnemy(LINE, 950, -150, 4);

		App->enemies->AddEnemy(LINE, 380, 900, 1);
		App->enemies->AddEnemy(LINE, 280, 950, 1);
		App->enemies->AddEnemy(LINE, 480, 950, 1);
		App->enemies->AddEnemy(LINE, 180, 1000, 1);
		App->enemies->AddEnemy(LINE, 580, 1000, 1);
	}
	if (Round == 10) {
		App->enemies->AddEnemy(LINE, -100, 900, 7);
		App->enemies->AddEnemy(LINE, 900, 900, 6);
		App->enemies->AddEnemy(LINE, -150, 900, 7);
		App->enemies->AddEnemy(LINE, 950, 900, 6);
		App->enemies->AddEnemy(LINE, -100, 950, 7);
		App->enemies->AddEnemy(LINE, 900, 950, 6);
		App->enemies->AddEnemy(LINE, -150, 950, 7);
		App->enemies->AddEnemy(LINE, 950, 950, 6);

		App->enemies->AddEnemy(LINE, 380, -100, 0);
		App->enemies->AddEnemy(LINE, 280, -150, 0);
		App->enemies->AddEnemy(LINE, 480, -150, 0);
		App->enemies->AddEnemy(LINE, 180, -200, 0);
		App->enemies->AddEnemy(LINE, 580, -200, 0);
	}
	if (Round == 11){
		App->enemies->AddEnemy(LINE, 900, 900, 6);
		App->enemies->AddEnemy(LINE, 900, -100, 4);
		App->enemies->AddEnemy(LINE, 950, 900, 6);
		App->enemies->AddEnemy(LINE, 950, -100, 4);
		App->enemies->AddEnemy(LINE, 900, 950, 6);
		App->enemies->AddEnemy(LINE, 900, -150, 4);
		App->enemies->AddEnemy(LINE, 950, 950, 6);
		App->enemies->AddEnemy(LINE, 950, -150, 4);

		App->enemies->AddEnemy(LINE, -100, 380, 3);
		App->enemies->AddEnemy(LINE, -150, 280, 3);
		App->enemies->AddEnemy(LINE, -150, 480, 3);
		App->enemies->AddEnemy(LINE, -200, 180, 3);
		App->enemies->AddEnemy(LINE, -200, 580, 3);
	}
	if (Round == 12) {
		App->enemies->AddEnemy(LINE, -100, 900, 7);
		App->enemies->AddEnemy(LINE, -100, -100, 5);
		App->enemies->AddEnemy(LINE, -150, 900, 7);
		App->enemies->AddEnemy(LINE, -150, -100, 5);
		App->enemies->AddEnemy(LINE, -100, 950, 7);
		App->enemies->AddEnemy(LINE, -100, -150, 5);
		App->enemies->AddEnemy(LINE, -150, 950, 7);
		App->enemies->AddEnemy(LINE, -150, -150, 5);

		App->enemies->AddEnemy(LINE, 900, 380, 2);
		App->enemies->AddEnemy(LINE, 950, 280, 2);
		App->enemies->AddEnemy(LINE, 950, 480, 2);
		App->enemies->AddEnemy(LINE, 1000, 180, 2);
		App->enemies->AddEnemy(LINE, 1000, 580, 2);
	}
}

void j1Scene::ResetRounds()
{
	App->player->RONDA = 1;
	SpawnRound2 = false;
	SpawnRound3 = true;
	SpawnRound4 = true;
	SpawnRound5 = true;
	SpawnRound6 = true;
	SpawnRound7 = true;
	SpawnRound8 = true;
	SpawnRound9 = true;
	SpawnRound10 = true;
	SpawnRound11 = true;
	SpawnRound12 = true;

	StartRound1 = false;
	StartRound2 = false;
	StartRound3 = false;
	StartRound4 = false;
	CanFinish = false;
	SaveXML_ROUND1 = false;
	SaveXMLROUND2 = false;
	SaveXMLROUND3 = false;
	SaveXMLROUND4 = false;

	ResetRound1 = true;
	ResetRound2 = true;
	ResetRound3 = true;
	ResetRound4 = true;
}




