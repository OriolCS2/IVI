#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "p2Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	Animation * animation;
	Collider* collider;

public:
	iPoint position;
	int type = 0;
	bool hit = false;
	bool dead = false;
	int stop;
public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;
	virtual void OnCollision(Collider* collider);

	virtual void Move(float dt) {};
	virtual void Draw(SDL_Texture* sprites, float dt);

};

#endif // __ENEMY_H__