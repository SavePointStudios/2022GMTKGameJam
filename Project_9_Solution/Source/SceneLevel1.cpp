#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleBreakable.h"
#include "ModulePowerup.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/map_scratch.png");
	//App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);

	//Bottomside collider
	//App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 0, 0);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	//App->enemies->AddEnemy(Enemy_Type::MECH, 900, 195);

	// Breakables ---
	//App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 210, 120);
	App->breakables->AddBreakable(BREAKABLE_TYPE::DOOR, 210, 120, 0);
	App->breakables->AddBreakable(BREAKABLE_TYPE::DOOR, 400, 120, 1);
	// Powerups ---
	App->powerups->AddPowerup(POWERUP_TYPE::DICE, 210, 180);
	App->render->camera.y = 0;


	App->player->Enable();
	App->enemies->Enable();
	App->powerups->Enable();
	App->breakables->Enable();
	App->collisions->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	App->render->camera.x += 0;

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->breakables->Disable();
	App->powerups->Disable();
	App->collisions->Disable();
	
	return true;
}