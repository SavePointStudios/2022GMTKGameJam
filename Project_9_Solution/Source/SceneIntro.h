#ifndef __SCENE_INTRO_H__
#define __SCENE_INTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneIntro : public Module
{
public:
	//Constructor
	SceneIntro(bool startEnabled);

	//Destructor
	~SceneIntro();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	bool CleanUp();

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* scene0 = nullptr;
	SDL_Texture* scene1 = nullptr;
	SDL_Texture* scene2 = nullptr;
	SDL_Texture* scene3 = nullptr;
	SDL_Texture* scene4 = nullptr;
	SDL_Texture* scene5 = nullptr;
	SDL_Texture* scene6 = nullptr;
	SDL_Texture* scene7 = nullptr;

	int currentScene = 0;
	
	// 9 ~ 11 boss kill
};

#endif