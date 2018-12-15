#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "j1Module.h"
#include "EnemyLine.h"


#define MAX_ENEMIES 500


enum ENEMY_TYPES {
	
	No_TYPE = 0,

	LINE,
	HORITZONTAL_SHIP,
	VERTICAL,

};

class Enemy;

struct EnemyInfo
{
	int type = 0;
	int x, y;
	int Type;
	int num;
	int direction;
};

class ModuleEnemies : public j1Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	bool DeleteEnemies();
	void OnCollision(Collider* c1, Collider* c2);
	bool AddEnemy(ENEMY_TYPES type, int x, int y, int direction);

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;
	int lives[MAX_ENEMIES];
};

#endif // __ModuleEnemies_H__