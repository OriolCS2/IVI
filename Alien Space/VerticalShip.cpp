#include "j1App.h"
#include "VerticalShip.h"
#include "J1Collision.h"
#include "J1Particles.h"
#include "ModuleEnemies.h"
#include "path.h"
#include "j1Render.h"
#include "Player.h"
#include "EntityManager.h"

#include <math.h>  



Enemy_VerticalShip::Enemy_VerticalShip(int x, int y, int Type) : Enemy(x, y)
{
	type = VERTICAL_SHIP;
	this->Type = Type;
	fly.PushBack({ 0, 0, 41, 41 }); // 1

	

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 41, 21 }, COLLIDER_TYPE::COLLIDER_ENEMY_BAT, (j1Module*)App->enemies);
	original_pos.x = x;
	original_pos.y = y;
	original_y = y;
	Down = position.y + 60;
	if (Type == 2) {
		Right = 131;
		Left = 24;

	}
	if (Type == 3) {
		Right = 182;
		Left = 75;
	}
	if (Type == 4) {
		Right = 233;
		Left = 126;

	}
	if (Type == 5) {
		Right = 284;
		Left = 177;

	}
	if (Type == 6) {
		Right = 335;
		Left = 228;

	}
	if (Type == 7) {
		Right = 386;
		Left = 279;

	}
	if (Type == 8) {
		Right = 437;
		Left = 330;

	}
	
}

void Enemy_VerticalShip::Move(float dt)
{
	
		if (ToDo1) { //va dreta
			if (position.x <= Right) {
				position.x += 120 * dt;
			}
			else {
				ToDo1 = false;
				ToDo2 = true;
			}
		}
		if (ToDo2) { //baixa
			if (position.y <= Down) {
				position.y += 100 * dt;
			}
			else {
				Down += 50;
				ToDo2 = false;
				ToDo3 = true;
			}
		}
		if (ToDo3) { //va esquerre
			if (position.x >= Left) {
				position.x -= 100 * dt;
			}
			else {
				ToDo3 = false;
				ToDo4 = true;
			}
		}
		if (ToDo4) { //baixa
			if (position.y <= Down) {
				position.y += 100 * dt;
			}
			else {
				Down += 50;
				ToDo4 = false;
				ToDo1 = true;
			}
		}

}

void Enemy_VerticalShip::OnCollision(Collider* collider) {
	
}