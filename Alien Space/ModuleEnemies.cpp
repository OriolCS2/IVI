#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "ModuleEnemies.h"
#include "j1Particles.h"
#include "j1Textures.h"
#include "Vertical.h"
#include "Enemy.h"
#include "j1Window.h"
#include "Player.h"
#include "PathFindingShip.h"
#include "EnemyLine.h"
#include "j1Audio.h"



#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->tex->Load("textures/starshipdark.png");
	exp = App->audio->LoadFx("audio/fx/Enemy_Explosion.wav");

	return true;
}

bool ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::No_TYPE)
		{
			
			
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::No_TYPE;
			
		}
	}

	return true;
}

// Called before render is available
bool ModuleEnemies::Update(float dt)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move(dt);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Draw(sprites, dt);

	return true;
}

bool ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn


	return true;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{

	App->tex->UnLoad(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}
bool ModuleEnemies::DeleteEnemies()
{

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y,int direction)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::No_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].direction = direction;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::LINE:
			enemies[i] = new Enemy_Line(info.x, info.y, info.direction);
			break;
		case ENEMY_TYPES::HORITZONTAL_SHIP:
			enemies[i] = new PathFindingShip(info.x, info.y);
			break;
		case ENEMY_TYPES::VERTICAL:
			enemies[i] = new Vertical(info.x, info.y);
			break;
		}
		
	}
	}


void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			switch (enemies[i]->type)
			{
			case No_TYPE:
				enemies[i]->OnCollision(c2);
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			case LINE:
				App->player->EnemiesKilled++;
				enemies[i]->OnCollision(c2);
				App->audio->PlayFx(exp);
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			case HORITZONTAL_SHIP:
				App->player->EnemiesKilled++;
				enemies[i]->OnCollision(c2);
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			case VERTICAL:
				App->player->EnemiesKilled++;
				enemies[i]->OnCollision(c2);
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			default:
				break;
			}
		}
	}
}