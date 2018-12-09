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
	
	return true;
}

void Player::OnCollision(Collider * c2) //this determine what happens when the player touch a type of collider
{
	
}


