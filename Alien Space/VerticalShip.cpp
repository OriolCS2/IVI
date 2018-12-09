#include "j1App.h"
#include "VerticalShip.h"
#include "J1Collision.h"
#include "J1Particles.h"
#include "ModuleEnemies.h"


#include <math.h>  



Enemy_VerticalShip::Enemy_VerticalShip(int x, int y) : Enemy(x, y)
{
	type = VERTICAL_SHIP;

	fly.PushBack({ 311, 4, 23, 17 }); // 1
	fly.PushBack({ 340, 2, 23, 20 }); // 2
	fly.PushBack({ 368,0,23,22 }); // 3
	fly.PushBack({ 396,1,23,19 }); // 4
	fly.speed = 0.08f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 23, 22 }, COLLIDER_TYPE::COLLIDER_ENEMY_BAT, (j1Module*)App->enemies);
	
	original_y = y;
}

void Enemy_VerticalShip::Move(float dt)
{
	

}

void Enemy_VerticalShip::OnCollision(Collider* collider) {
	
}