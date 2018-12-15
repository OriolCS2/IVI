#include "j1App.h"
#include "PathFindingShip.h"
#include "J1Collision.h"
#include "J1Particles.h"
#include "ModuleEnemies.h"
#include "path.h"
#include "j1Window.h"
#include "j1Render.h"
#include "Player.h"
#include "j1Pathfinding.h"


#include <math.h>  



PathFindingShip::PathFindingShip(int x, int y) : Enemy(x, y)
{
	type = HORITZONTAL_SHIP;

	fly.PushBack({ 0, 0, 41, 41 }); // 1



	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 41, 21 }, COLLIDER_TYPE::COLLIDER_ENEMY_BAT, (j1Module*)App->enemies);
	original_pos.x = x;
	original_pos.y = y;
	original_y = y;

	if (position.x <= -App->render->camera.x) {
		GORIGHT = true;
	}
	if (position.x >= -App->render->camera.x + App->render->camera.w) {
		GOLEFT = true;
	}

}

void PathFindingShip::Move(float dt)
{
	
	if ((position.x >= -App->render->camera.x && GoRight) || GORIGHT) {
		position.x += 300 * dt;
		if (position.x >= -App->render->camera.x + App->win->Width - 40) {
			GoLeft = true;
			GoRight = false;
			GORIGHT = false;
		}
	}
	if ((position.x <= -App->render->camera.x + App->render->camera.w && GoLeft) || GOLEFT) {
		position.x -= 300 * dt;
		if (position.x <= -App->render->camera.x + 5) {
			GoLeft = false;
			GoRight = true;
			GOLEFT = false;
		}
	}

}

void PathFindingShip::OnCollision(Collider* collider) {

}