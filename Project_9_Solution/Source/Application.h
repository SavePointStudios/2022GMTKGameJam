#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 19

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModuleUI;
class ModulePlayer;
class SceneMenu;
class SceneIntro;
class SceneCredits;
class SceneLevel1;
class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModuleFadeToBlack;
class ModuleFonts;
class ModuleRender;
class ModuleDebug;
class ModuleBreakable;
class ModulePowerup;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	Update_Status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;
	
	ModuleUI* ui = nullptr;

	ModulePlayer* player = nullptr;

	SceneMenu* sceneMenu = nullptr;
	SceneIntro* sceneIntro = nullptr;
	SceneCredits* sceneCredits = nullptr;
	SceneLevel1* sceneLevel_1 = nullptr;

	ModuleBreakable* breakables = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;
	ModulePowerup* powerups = nullptr;
	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;

	ModuleRender* render = nullptr;

	ModuleDebug* debug = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__