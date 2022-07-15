#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleUI : public Module
{
public:

	ModuleUI(bool startEnabled);

	~ModuleUI();


	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	bool CleanUp();

	int getScore() { return score; }
	

	//God Mode
	//bool godMode = false;

	SDL_Texture* uiSprites = nullptr;

	Animation* currentAnimation = nullptr;

	//score

	uint score = 000;
	char scoreText[10] = { "\0" };
	int ScoreFont = -1;

private:

	//SFX

};

#endif