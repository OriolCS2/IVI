#include "j1App.h"
#include "Enemy.h"
#include "j1Collision.h"
#include "j1Render.h"
#include "j1Particles.h"
#include "ModuleEnemies.h"

Enemy::Enemy(int x, int y) : position(x, y), collider(nullptr)
{}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->to_delete = true;
		collider = nullptr;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites, float dt)
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame(dt)));
}
void Enemy::OnCollision(Collider* collider) {}

