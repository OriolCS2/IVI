#include "j1App.h"
#include "VerticalShip.h"
#include "J1Collision.h"
#include "J1Particles.h"
#include "ModuleEnemies.h"
#include "path.h"
#include "j1Render.h"
#include "Player.h"


#include <math.h>  



Enemy_VerticalShip::Enemy_VerticalShip(int x, int y, int direction) : Enemy(x, y) //if direction = 0, goes down, if d=1, goes up
{
	type = VERTICAL_SHIP;
	fly.PushBack({ 0, 0, 41, 41 }); // 1

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 41, 21 }, COLLIDER_TYPE::COLLIDER_ENEMY_BAT, (j1Module*)App->enemies);
	original_pos.x = x;
	original_pos.y = y;
	original_y = y;
	this->shoot = shoot;
	time = SDL_GetTicks();
	direction = DIRECTION;
}

void Enemy_VerticalShip::Move(float dt)
{
	switch (DIRECTION)
	{
	case 0:
		position.y += 200 * dt;
		break;
	case 1:
		position.y -= 200 * dt;
		break;
	}
}

void Enemy_VerticalShip::OnCollision(Collider* collider) {
	
}