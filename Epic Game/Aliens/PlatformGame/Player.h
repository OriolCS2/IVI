#ifndef __Player_H__
#define __Player_H__

#include "p2Animation.h"
#include "p2Point.h"
#include "Entity.h"

class UI_Element;

class Player : public Entity
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
	void OnCollision(Collider* c2);


public:

	float DT;

	Collider* coll = nullptr;

	SDL_Texture* texture = nullptr;
	iPoint position;
	Animation* current_animation = nullptr;
	Animation Idle;
	int Time = 0;
};



#endif // 

