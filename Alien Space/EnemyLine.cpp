#include "j1App.h"
#include "EnemyLine.h"
#include "J1Collision.h"
#include "J1Particles.h"
#include "ModuleEnemies.h"
#include "path.h"
#include "j1Render.h"
#include "Player.h"


#include <math.h>  



Enemy_Line::Enemy_Line(int x, int y, int direction) : Enemy(x, y) //if direction = 0, goes down, if d=1, goes up
{
	type = LINE;
	switch (direction)
	{
	case 0:
		fly.PushBack({ 42, 0, 41, 41 }); // 0
		break;
	case 1:
		fly.PushBack({ 0, 0, 41, 41 }); // 1
		break;
	case 2:
		fly.PushBack({ 84, 0, 41, 41 }); // 2
		break;
	case 3:
		fly.PushBack({ 127, 0, 41, 41 }); // 3
		break;
	}
	

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 41, 21 }, COLLIDER_TYPE::COLLIDER_ENEMY_BAT, (j1Module*)App->enemies);
	original_pos.x = x;
	original_pos.y = y;
	original_y = y;
	this->shoot = shoot;
	time = SDL_GetTicks();
	DIRECTION= direction;
	int f = 0;
}

void Enemy_Line::Move(float dt)
{
	switch (DIRECTION)
	{
	case 0:
		position.y += 200 * dt;
		break;
	case 1:
		position.y -= 200 * dt;
		break;
	case 2:
		position.x -= 300 * dt;
		break;
	case 3:
		position.x += 300 * dt;
	}
}

void Enemy_Line::OnCollision(Collider* collider) {
	
}