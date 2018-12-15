#ifndef __PATHFINDINGSHIP_H__
#define __PATHFINDINGSHIP_H__

#include "Enemy.h"
#include "path.h"
#include "p2Point.h"
#include "p2DynArray.h"

class PathFindingShip : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	iPoint original_pos;
	Animation fly;
	p2DynArray<iPoint>	PATH;
	fPoint velocity;
	float Speed = 300;

public:

	PathFindingShip(int x, int y);
	void OnCollision(Collider* collider);
	void Move(float dt);
};

#endif