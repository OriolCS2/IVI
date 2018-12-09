#include <math.h>
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Particles.h"
#include "j1Audio.h"
#include "j1Particles.h"
#include "Player.h"
#include "j1Collision.h"
#include "PugiXml\src\pugiconfig.hpp"
#include "PugiXml\src\pugixml.hpp"
#include "EntityManager.h"

#define MARGIN 20


#include "SDL/include/SDL_timer.h"

j1Particles::j1Particles()
{
	name.create("particles");
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

}

j1Particles::~j1Particles()
{}

// Load assets
bool j1Particles::Start()
{
	LOG("Loading particles");

	texture = App->tex->Load("textures/shoot.png");

	shoot.anim.PushBack({ 0,0,8,45 });
	shoot.anim.speed = 0.2f;
	shoot.anim.loop = true;
	shoot.speed.y = -500;
	shoot.speed.x = 0;
	shoot.life = 3000;

	return true;
}

// Unload assets
bool j1Particles::CleanUp()
{
	LOG("Unloading particles");

	App->tex->UnLoad(texture);
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

bool j1Particles::Awake(pugi::xml_node& config) 
{
	
	return true;
}

// Update: draw background
bool j1Particles::Update(float dt)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame(App->entitymanager->GetPlayerData()->DT)));
			if (p->fx_played == false)
			{
				p->fx_played = true;
			}
		}
	}

	return true;
}

void j1Particles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider({-100,0,8,38}, collider_type, this);
			active[i] = p;
			break;
		}
	}

}

// TODO 5: Make so every time a particle hits a wall it triggers an explosion particle
void j1Particles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += (speed.x * App->entitymanager->GetPlayerData()->DT);
	position.y += (speed.y * App->entitymanager->GetPlayerData()->DT);

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}

