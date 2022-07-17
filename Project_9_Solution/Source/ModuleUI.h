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

	SDL_Texture* lifeBarTexture = nullptr;
	Animation* currentLifeBarAnimation = nullptr;

	SDL_Texture* rollTexture = nullptr;
	Animation* currentRollAnimation = nullptr;

	Animation ceroLifeAnim;
	Animation oneLifeAnim;
	Animation twoLifeAnim;
	Animation threeLifeAnim;
	Animation fourLifeAnim;
	Animation fiveLifeAnim;
	Animation sixLifeAnim;

	Animation oneRollAnim;
	Animation twoRollAnim;
	Animation threeRollAnim;
	Animation fourRollAnim;
	Animation fiveRollAnim;
	Animation sixRollAnim;

private:

	//SFX

};

#endif