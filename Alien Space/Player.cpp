#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1FadeToBlack.h"
#include "j1Collision.h"
#include "j1Audio.h"
#include "EntityManager.h"
#include "j1Timer.h"
#include "j1Scene.h"
#include "j1Menu.h"
#include "Player.h"
#include "j1Particles.h"
#include "UI_Element.h"
#include "UI_Manager.h"
#include "Image.h"

#include "Brofiler/Brofiler.h"

Player::Player() : Entity()
{

}

Player::~Player() {}

bool Player::Awake(pugi::xml_node& config)
{
	LOG("Init SDL player");


	bool ret = true;
	return ret;
}

bool Player::Start()
{
	BROFILER_CATEGORY("Player: Start", Profiler::Color::DarkGreen)
	bool ret = true;
	
	texture = App->tex->Load("textures/ship.png");
	
	Idle.PushBack({ 113,5,41,47 });

	StartPosition();

	current_animation = &Idle;

	return ret;
}
bool Player::PreUpdate() //Here we preload the input functions to determine the state of the player
{
	BROFILER_CATEGORY("Player: PreUpdate", Profiler::Color::Green);
	
	return true;
}
bool Player::Update(float dt)
{
	BROFILER_CATEGORY("Player: Update", Profiler::Color::Green);
	DT = dt;

	Controls();

	App->render->Blit(texture, position.x, position.y, &current_animation->GetCurrentFrame(dt));

	return true;
}

bool Player::PostUpdate()
{
	BROFILER_CATEGORY("Player: PostUpdate", Profiler::Color::Green);
	
	return true;
}
bool Player::Load(pugi::xml_node& player)
{
	

	

	return true;
}
bool Player::Save(pugi::xml_node& player) const
{
	
	return true;
}

bool Player::CleanUp()
{
	App->tex->UnLoad(texture);
	return true;
}

void Player::OnCollision(Collider * c2) //this determine what happens when the player touch a type of collider
{
	
}

void Player::Controls()
{
	if (position.x >= -App->render->camera.x + 9) {
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			position.x -= 400 * DT;
		}
	}
	if (position.x <= -App->render->camera.x + App->render->camera.w - 49) {
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			position.x += 400 * DT;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && SDL_GetTicks() - Time >= 250) {
		Time = SDL_GetTicks();
		App->particles->AddParticle(App->particles->shoot, position.x + 16, position.y - 45, COLLIDER_PARTICLE);
	}
}

void Player::StartPosition()
{
	position.x = -App->render->camera.x + 200;
	position.y = -App->render->camera.y + 700;
}