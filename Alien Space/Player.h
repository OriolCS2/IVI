#ifndef __Player_H__
#define __Player_H__

#include "p2Animation.h"
#include "p2Point.h"
#include "j1Module.h"

class UI_Element;

class Player : public j1Module
{
	
public:

	Player();

	//Destructor
	virtual ~Player();

	//Called before player is aviable
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	//// Called each loop iteration
	bool PreUpdate();

	//// Called each loop iteration
	bool PostUpdate();


	//Called every loop iteration
	bool Update(float dt);

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void Controls();
	void StartPosition();

public:

	float DT;

	Collider* coll = nullptr;

	SDL_Texture* texture = nullptr;
	iPoint position;
	Animation* current_animation = nullptr;
	Animation Idle;
	int Time = 0;
	int Time2 = 0;
	int EnemiesKilled = 0;
	int XML_enemieskilled = -10;
	int ShootNum = 0; 
	int XML_ShootNum = -10;
	bool GOD = false;
};



#endif // 

