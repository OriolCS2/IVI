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
#include "Entity.h"
#include "EntityManager.h"
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

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	BROFILER_CATEGORY("Scene: PostUpdate", Profiler::Color::LightYellow);
	bool ret = true;
	if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) {
		SpawnEnemies();
	}

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	App->tex->UnLoad(space);
	LOG("Freeing scene");
	return true;
}

bool j1Scene::Load(pugi::xml_node & scene)
{
	

	return true;
}

bool j1Scene::Save(pugi::xml_node & scene) const
{
	


	return true;
}

void j1Scene::SpawnEnemies()
{

	App->enemies->AddEnemy(VERTICAL_SHIP, 25, 10);
	App->enemies->AddEnemy(VERTICAL_SHIP, 76, 10);
	App->enemies->AddEnemy(VERTICAL_SHIP, 126, 10);
	App->enemies->AddEnemy(VERTICAL_SHIP, 177, 10); 
	App->enemies->AddEnemy(VERTICAL_SHIP, 228, 10);
	App->enemies->AddEnemy(VERTICAL_SHIP, 279, 10);
	App->enemies->AddEnemy(VERTICAL_SHIP, 330, 10);
	App->enemies->AddEnemy(VERTICAL_SHIP, 381, 10);
	App->enemies->AddEnemy(VERTICAL_SHIP, 432, 10);

}




