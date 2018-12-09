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

	if (Type == 2) {
		Right = 127;
		Left = 20;
		Down = 70;
	}
	if (Type == 3) {
		Right = 178;
		Left = 71;
		Down = 70;
	}
	if (Type == 4) {
		Right = 229;
		Left = 122;
		Down = 70;
	}
	if (Type == 5) {
		Right = 280;
		Left = 173;
		Down = 70;
	}
	if (Type == 6) {
		Right = 331;
		Left = 224;
		Down = 70;
	}
	if (Type == 7) {
		Right = 382;
		Left = 275;
		Down = 70;
	}
	if (Type == 8) {
		Right = 433;
		Left = 326;
		Down = 70;
	}
	
}

void Enemy_VerticalShip::Move(float dt)
{
	
		if (ToDo1) {
			if (position.x <= Right) {
				position.x += 120 * dt;
			}
			else {
				ToDo1 = false;
				ToDo2 = true;
			}
		}
		if (ToDo2) {
			if (position.x >= Left) {
				position.x -= 100 * dt;
			}
			else {
				ToDo2 = false;
				ToDo3 = true;
			}
		}
		if (ToDo3) {
			if (position.y <= Down) {
				position.y += 100 * dt;
			}
			else {
				ToDo3 = false;
				ToDo4 = true;
			}
		}
		if (ToDo4) {
			Down += 50;
			ToDo4 = false;
			ToDo1 = true;
		}
}

void Enemy_VerticalShip::OnCollision(Collider* collider) {
	
}