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

	bgTexture = App->textures->Load("Assets/Sprites/map_base.png");
	//App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);

	//Colliders

		//First Room
	App->collisions->AddCollider({ 64, 16, 653, 35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 64, 16, 48, 985 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 64, 950, 653, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 672, 843, 45, 157 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 672, 16, 45, 691 }, Collider::Type::WALL);

		//First Hallway
	App->collisions->AddCollider({ 672, 696, 534, 11 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 672, 843, 534, 12 }, Collider::Type::WALL);

		//Second Room
	App->collisions->AddCollider({ 1157, 464, 49, 243 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1157, 464, 668, 19 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1779, 464, 46, 228 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1157, 844, 49, 134 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1157, 950, 664, 27 }, Collider::Type::WALL);

		//Third Room
	App->collisions->AddCollider({ 1778, 950, 43, 428 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1780, 667, 588, 25 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1778, 1341, 360, 37 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 2327, 667, 41, 634 }, Collider::Type::WALL);

		//Fourth Room
	App->collisions->AddCollider({ 2327, 1287, 63, 14 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 2118, 1342, 20, 285 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 2371, 1287, 19, 410 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 2279, 1676, 111, 21 }, Collider::Type::WALL);


		//Second Hallway
	App->collisions->AddCollider({ 2207, 1681, 72, 125 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 911, 1614, 1225, 13 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 911, 1791, 1368, 14 }, Collider::Type::WALL);

		//Boss Room
	App->collisions->AddCollider({ 847, 1194, 64, 433 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 847, 1791, 64, 260 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 1194, 911, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 2006, 911, 45 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 1194, 62, 853 }, Collider::Type::WALL);


	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 0, 0);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	//App->enemies->AddEnemy(Enemy_Type::MECH, 900, 195);

	// Breakables ---
	//App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 210, 120);
	App->breakables->AddBreakable(BREAKABLE_TYPE::DOOR, 210, 120, 0);
	App->breakables->AddBreakable(BREAKABLE_TYPE::DOOR, 400, 120, 1);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CARDBOX, 400, 190, 0);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CARDBOX, 430, 190, 1);
	App->breakables->AddBreakable(BREAKABLE_TYPE::TABLE, 430, 250, 0);
	App->breakables->AddBreakable(BREAKABLE_TYPE::TABLE, 430, 250, 1);
	App->breakables->AddBreakable(BREAKABLE_TYPE::GOBLET, 430, 250, 1);
	App->breakables->AddBreakable(BREAKABLE_TYPE::GOBLET, 430, 250, 1);

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