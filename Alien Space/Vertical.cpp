#include "Vertical.h"
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


Vertical::Vertical(int x, int y) : Enemy(x, y)
{

	type = VERTICAL;

	fly.PushBack({ 0, 0, 41, 41 }); // 1



	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 41, 46 }, COLLIDER_TYPE::COLLIDER_ENEMY_BAT, (j1Module*)App->enemies);
	original_pos.x = x;
	original_pos.y = y;
	original_y = y;

	if (position.y <= -App->render->camera.y) {
		GODOWN = true;
	}
	if (position.y >= -App->render->camera.y + App->render->camera.h) {
		GOUP = true;
	}

}

void Vertical::OnCollision(Collider * collider)
{
}

void Vertical::Move(float dt)
{

	if ((position.y >= -App->render->camera.y && GoDown) || GODOWN) {
		position.y += 300 * dt;
		if (position.y >= -App->render->camera.y + App->win->Height - 40) {
			GoUp = true;
			GoDown = false;
			GODOWN = false;
		}
	}
	if ((position.y <= -App->render->camera.y + App->render->camera.h && GoUp) || GOUP) {
		position.y -= 300 * dt;
		if (position.y <= -App->render->camera.y + 5) {
			GoUp = false;
			GoDown = true;
			GOUP = false;
		}
	}
}
