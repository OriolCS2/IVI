#include "j1App.h"
#include "VerticalShip.h"
#include "J1Collision.h"
#include "J1Particles.h"
#include "ModuleEnemies.h"


#include <math.h>  



Enemy_VerticalShip::Enemy_VerticalShip(int x, int y) : Enemy(x, y)
{
	type = VERTICAL_SHIP;

	fly.PushBack({ 0, 0, 41, 41 }); // 1
	

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 41, 21 }, COLLIDER_TYPE::COLLIDER_ENEMY_BAT, (j1Module*)App->enemies);
	
	original_y = y;
}

void Enemy_VerticalShip::Move(float dt)
{
	

}

void Enemy_VerticalShip::OnCollision(Collider* collider) {
	
}