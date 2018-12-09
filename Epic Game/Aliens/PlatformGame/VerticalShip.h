#ifndef __ENEMY_VERTICALSHIP_H__
#define __ENEMY_VERTICALSHIP_H__

#include "Enemy.h"

class Enemy_VerticalShip : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
	int shot = 0;
	float x, y, m;
	bool gun;

public:

	Enemy_VerticalShip(int x, int y);
	void OnCollision(Collider* collider);
	void Move(float dt);
};

#endif
