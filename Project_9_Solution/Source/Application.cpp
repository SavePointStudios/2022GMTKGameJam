#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"
#include "ModulePlayer.h"
#include "SceneMenu.h"
#include "SceneIntro.h"
#include "SceneCredits.h"
#include "SceneLevel1.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include "ModuleDebug.h"
#include "ModuleBreakable.h"
#include "ModulePowerup.h"
#include "SDL/include/SDL.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen

	modules[0] =	window =		new ModuleWindow(true);
	modules[1] =	input =			new ModuleInput(true);
	modules[2] =	textures =		new ModuleTextures(true);
	modules[3] =	audio =			new ModuleAudio(true);
	 
	modules[4] =	fonts =			new ModuleFonts(true);
	modules[5] =	sceneMenu =		new SceneMenu(true);
	modules[6] =	sceneIntro =	new SceneIntro(false);
	modules[7] =	sceneCredits =	new SceneCredits(false);
	modules[8] =	sceneLevel_1 =	new SceneLevel1(false);		//Gameplay scene starts disabled
	modules[9] =	breakables =	new ModuleBreakable(false);
	modules[10] =	powerups =		new ModulePowerup(false);
	modules[11] =	player =		new ModulePlayer(false);	//Player starts disabled
	modules[12] =	particles =		new ModuleParticles(true);
	modules[13] =	enemies =		new ModuleEnemies(false);	//Enemies start disabled
	modules[14] =	ui =			new ModuleUI(false);

	modules[15] =	collisions =	new ModuleCollisions(true);
	modules[16] =	fade =			new ModuleFadeToBlack(true);
	modules[17] =	debug =			new ModuleDebug(true);
	modules[18] =	render =		new ModuleRender(true);

}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

Update_Status Application::Update()
{
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;

	SDL_Delay((int)(1000 / 60));

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
