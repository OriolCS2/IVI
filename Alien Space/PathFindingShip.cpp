#include "j1App.h"
#include "PathFindingShip.h"
#include "J1Collision.h"
#include "J1Particles.h"
#include "ModuleEnemies.h"
#include "path.h"
#include "j1Render.h"
#include "Player.h"
#include "j1Pathfinding.h"


#include <math.h>  



PathFindingShip::PathFindingShip(int x, int y) : Enemy(x, y)
{
	type = PATHFINDINGSHIP;

	fly.PushBack({ 0, 0, 41, 41 }); // 1



	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 41, 21 }, COLLIDER_TYPE::COLLIDER_ENEMY_BAT, (j1Module*)App->enemies);
	original_pos.x = x;
	original_pos.y = y;
	original_y = y;

}

void PathFindingShip::Move(float dt)
{
	
	float x = App->player->position.x;
	float y = App->player->position.y;

	
		iPoint origin = { position.x / 70,position.y / 70 };
		iPoint destination = {App->player->position.x/70,App->player->position.y/70};
		if (position.DistanceTo(App->player->position)) {
			App->pathfinding->CreatePath(origin, destination);
			const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();
			for (int i = 0; i < path->Count(); i++) {
				PATH.PushBack(*path->At(i));
			}
		}
		if (PATH.Count() > 1) {
			velocity.x = -Speed;
			velocity.y = Speed;
		}
		if (App->player->position.x < position.x) {
			position.x += velocity.x * dt;
		}
		else {
			position.x += -velocity.x * dt;
		}
		if (App->player->position.y > position.y) {
			position.y += velocity.y * dt;
		}
		if (App->player->position.y < position.y) {
			position.y -= velocity.y * dt;
		}
	

}

void PathFindingShip::OnCollision(Collider* collider) {

}