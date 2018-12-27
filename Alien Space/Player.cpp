#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1FadeToBlack.h"
#include "j1Collision.h"
#include "j1Audio.h"
#include "p2SString.h"
#include "j1Timer.h"
#include "j1Scene.h"
#include "j1Menu.h"
#include "Player.h"
#include "j1Particles.h"
#include "UI_Element.h"
#include "UI_Manager.h"
#include "ModuleEnemies.h"
#include "Image.h"
#include "j1Window.h"
#include "Brofiler/Brofiler.h"

Player::Player() : j1Module()
{
	name.create("ESTADISTICAS_DEL_JUGADOR");
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

	shoot=App->audio->LoadFx("audio/fx/Laser.wav");

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

	if (Controls)
		Controls1();
	else
		Controls2();

	App->render->Blit(texture, position.x, position.y, &current_animation->GetCurrentFrame(dt));
	if (!GOD) {
		if (coll == nullptr)
			coll = App->collision->AddCollider({ position.x,position.y,41,47 }, COLLIDER_PLAYER, this);
		coll->SetPos(position.x, position.y);
	}
	
	return true;
}

bool Player::PostUpdate()
{
	BROFILER_CATEGORY("Player: PostUpdate", Profiler::Color::Green);
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {
		if (GOD) {
			GOD = false;
		}
		else {
			GOD = true;
			App->collision->ColliderCleanUpPlayer();
			coll = nullptr;
		}
	}
	return true;
}
bool Player::Load(pugi::xml_node& player)
{
	

	

	return true;
}
bool Player::Save(pugi::xml_node& player) const
{
	if (Controls)
		player.append_child("Controles").append_attribute("Tipo") = "Controles_1";
	else
		player.append_child("Controles").append_attribute("Tipo") = "Controles_2";
	player.append_child("Numero_De_Muertes").append_attribute("value") = NumeroDeMuertes;
	player.append_child("Enemigos_Asesinados").append_attribute("value") = EnemiesKilled;
	player.append_child("Numero_de_Disparos").append_attribute("value") = ShootNum;
	player.append_child("Porcentaje_Disparos_Acertados").append_attribute("value") = Porcentaje;

	return true;
}

bool Player::CleanUp()
{
	App->tex->UnLoad(texture);
	return true;
}

void Player::OnCollision(Collider* c1, Collider* c2) //this determine what happens when the player touch a type of collider
{


	++NumeroDeMuertes;
	
	App->enemies->DeleteEnemies();

	DestroyP = true;
	if (App->scene->StartRound1) {
		App->scene->Time = SDL_GetTicks();
		App->scene->SpawnEnemies(1);
		CleanUp();
		Start();
		App->scene->SpawnRound2 = false;
		App->scene->SpawnRound3 = true;
	}
	if (App->scene->StartRound2) {
		App->scene->Time = SDL_GetTicks();
		CleanUp();
		Start();
		App->scene->SpawnRound4 = false;
		App->scene->SpawnRound5 = true;
		App->scene->SpawnRound6 = true;
	}
	if (App->scene->StartRound3) {
		App->scene->Time = SDL_GetTicks();
		CleanUp();
		Start();
		App->scene->SpawnRound7 = false;
		App->scene->SpawnRound8 = true;
		App->scene->SpawnRound9 = true;
	}
	if (App->scene->StartRound4) {
		App->scene->Time = SDL_GetTicks();
		CleanUp();
		Start();
		App->scene->SpawnRound10 = false;
		App->scene->SpawnRound11 = true;
		App->scene->SpawnRound12 = true;
	}

}

void Player::Controls1()
{
	if (position.x >= -App->render->camera.x + 9) {
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			position.x -= 400 * DT;
		}
	}
	if (position.x <= -App->render->camera.x + App->render->camera.w - 49) {
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			position.x += 400 * DT;
		}
	}
	if (position.y >= -App->render->camera.y + 9) {
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			position.y -= 400 * DT;
		}
	}
	if (position.y <= -App->render->camera.y + App->render->camera.h - 53) {
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			position.y += 400 * DT;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && SDL_GetTicks() - Time >= 200 && App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_IDLE) {
		ShootNum++;
		App->audio->PlayFx(shoot);
		Time = SDL_GetTicks();
		App->particles->AddParticle(App->particles->shoot, position.x + 16, position.y - 45, COLLIDER_PARTICLE);
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && SDL_GetTicks() - Time >= 200 && App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_IDLE) {
		ShootNum++;
		App->audio->PlayFx(shoot);
		Time = SDL_GetTicks();
		App->particles->AddParticle(App->particles->shoot2, position.x + 16, position.y, COLLIDER_PARTICLE);
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && SDL_GetTicks() - Time >= 200 && App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_IDLE) {
		ShootNum++;
		App->audio->PlayFx(shoot);
		Time = SDL_GetTicks();
		App->particles->AddParticle(App->particles->shootH2, position.x + 32, position.y + 21, COLLIDER_PARTICLE);
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && SDL_GetTicks() - Time >= 200 && App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_IDLE) {
		ShootNum++;
		App->audio->PlayFx(shoot);
		Time = SDL_GetTicks();
		App->particles->AddParticle(App->particles->shootH, position.x - 20, position.y + 21, COLLIDER_PARTICLE);
	}
}

void Player::Controls2()
{
	App->input->GetMousePosition(position.x,position.y);

	if (position.x >=800-42)
		position.x =800-42;

	if (position.y >= 800 - 47)
		position.y = 800 - 47;

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && SDL_GetTicks() - Time >= 200 && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE) {
		ShootNum++;
		App->audio->PlayFx(shoot);
		Time = SDL_GetTicks();
		App->particles->AddParticle(App->particles->shoot, position.x + 16, position.y - 45, COLLIDER_PARTICLE);
	}
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT)==KEY_DOWN && App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && SDL_GetTicks() - Time >= 200 && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE) {
		ShootNum++;
		App->audio->PlayFx(shoot);
		Time = SDL_GetTicks();
		App->particles->AddParticle(App->particles->shoot2, position.x + 16, position.y, COLLIDER_PARTICLE);
	}
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && SDL_GetTicks() - Time >= 200 && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE) {
		ShootNum++;
		App->audio->PlayFx(shoot);
		Time = SDL_GetTicks();
		App->particles->AddParticle(App->particles->shootH2, position.x + 32, position.y + 21, COLLIDER_PARTICLE);
	}
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && SDL_GetTicks() - Time >= 200 && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE) {
		ShootNum++;
		App->audio->PlayFx(shoot);
		Time = SDL_GetTicks();
		App->particles->AddParticle(App->particles->shootH, position.x - 20, position.y + 21, COLLIDER_PARTICLE);
	}
}
void Player::StartPosition()
{
	position.x = -App->render->camera.x + 200;
	position.y = -App->render->camera.y + 350;
}