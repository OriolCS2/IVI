#ifndef __ENEMY_VERTICALSHIP_H__
#define __ENEMY_VERTICALSHIP_H__

#include "Enemy.h"
#include "path.h"
#include "p2Point.h"

class Enemy_VerticalShip : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	iPoint original_pos;
	Animation fly;
	Path path;

public:

	Enemy_VerticalShip(int x, int y);
	void OnCollision(Collider* collider);
	void Move(float dt);
};

#endif
