#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "p2SString.h"

struct SDL_Texture;
class UI_Element;
class Label;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();



	void SpawnEnemies(int Round);
	void ResetRounds();

public:

	SDL_Texture * space = nullptr;
	bool StartRound1 = false;
	bool StartRound2 = false;
	bool StartRound3 = false;
	bool StartRound4 = false;

	bool SpawnRound2 = false;
	bool SpawnRound3 = true;
	bool SpawnRound4 = true;
	bool SpawnRound5 = true;
	bool SpawnRound6 = true;
	bool SpawnRound7 = true;
	bool SpawnRound8 = true;
	bool SpawnRound9 = true;
	bool SpawnRound10 = true;
	bool SpawnRound11 = true;
	bool SpawnRound12 = true;
	bool ResetRound1 = true;
	bool ResetRound2 = true;
	bool ResetRound3 = true;
	bool ResetRound4 = true;
	bool CanFinish = false;

	int Time = 0;
	p2SString Rounds;
	UI_Element* rounds = nullptr;

	bool SaveXML_ROUND1 = false;
	bool SaveXMLROUND2 = false;
	bool SaveXMLROUND3 = false;
	bool SaveXMLROUND4 = false;

};

#endif // __j1SCENE_H__