#ifndef __VERTICAL_H__
#define __VERTICAL_H__

#include "Enemy.h"
#include "path.h"
#include "p2Point.h"

class Vertical : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	iPoint original_pos;
	Animation fly;
	bool GoUp = true;
	bool GoDown = false;
	bool GOUP = false;
	bool GODOWN = false;

public:

	Vertical(int x, int y);
	void OnCollision(Collider* collider);
	void Move(float dt);
};

#endif