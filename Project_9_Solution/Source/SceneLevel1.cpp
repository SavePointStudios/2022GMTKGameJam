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
#include "ModuleUI.h"

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
	
	// Room 1 Music
	App->audio->PlayMusic("Assets/Music/Stage1.ogg", 1.0f); // music that plays in the first room
	//App->audio->PlayMusic("Assets/Music/Stage2.ogg", 1.0f); // music that plays in the second room
	//App->audio->PlayMusic("Assets/Music/Final boss.ogg", 1.0f); // music that plays in the final boss fight room

	//Colliders

		//First Room
	App->collisions->AddCollider({ 64, 16, 653, 35 }, Collider::Type::UP_WALL);
	App->collisions->AddCollider({ 64, 16, 48, 985 }, Collider::Type::LEFT_WALL);
	App->collisions->AddCollider({ 64, 950, 653, 50 }, Collider::Type::DOWN_WALL);
	App->collisions->AddCollider({ 672, 843, 10, 157 }, Collider::Type::RIGHT_WALL);
	App->collisions->AddCollider({ 672, 16, 10, 691 }, Collider::Type::RIGHT_WALL);

		//First Hallway
	App->collisions->AddCollider({ 672, 696, 534, 10 }, Collider::Type::UP_WALL);
	App->collisions->AddCollider({ 672, 843, 534, 10 }, Collider::Type::DOWN_WALL);

		//Second Room
	App->collisions->AddCollider({ 1196, 464, 10, 243 }, Collider::Type::LEFT_WALL);
	App->collisions->AddCollider({ 1157, 464, 668, 19 }, Collider::Type::UP_WALL);
	App->collisions->AddCollider({ 1779, 464, 10, 228 }, Collider::Type::RIGHT_WALL);
	App->collisions->AddCollider({ 1196, 844, 10, 134 }, Collider::Type::LEFT_WALL);
	App->collisions->AddCollider({ 1157, 950, 664, 10 }, Collider::Type::DOWN_WALL);

		//Third Room
	App->collisions->AddCollider({ 1811, 950, 10, 428 }, Collider::Type::LEFT_WALL);
	App->collisions->AddCollider({ 1780, 682, 588, 10 }, Collider::Type::UP_WALL);
	App->collisions->AddCollider({ 1778, 1341, 360, 10 }, Collider::Type::DOWN_WALL);
	App->collisions->AddCollider({ 2327, 667, 10, 634 }, Collider::Type::RIGHT_WALL);

		//Fourth Room
	App->collisions->AddCollider({ 2327, 1291, 63, 10 }, Collider::Type::UP_WALL);
	App->collisions->AddCollider({ 2128, 1342, 10, 285 }, Collider::Type::LEFT_WALL);
	App->collisions->AddCollider({ 2371, 1287, 10, 410 }, Collider::Type::RIGHT_WALL);
	App->collisions->AddCollider({ 2207, 1676, 181, 10 }, Collider::Type::DOWN_WALL);


		//Second Hallway
	App->collisions->AddCollider({ 2207, 1678, 10, 125 }, Collider::Type::RIGHT_WALL);
	App->collisions->AddCollider({ 847, 1617, 1289, 10 }, Collider::Type::UP_WALL);
	App->collisions->AddCollider({ 847, 1791, 1432, 10 }, Collider::Type::DOWN_WALL);

		//Boss Room
	App->collisions->AddCollider({ 847, 1194, 10, 433 }, Collider::Type::RIGHT_WALL);
	App->collisions->AddCollider({ 847, 1791, 10, 260 }, Collider::Type::RIGHT_WALL);
	App->collisions->AddCollider({ 0, 1194, 911, 30 }, Collider::Type::UP_WALL);
	App->collisions->AddCollider({ 0, 2006, 911, 45 }, Collider::Type::DOWN_WALL);
	App->collisions->AddCollider({ 0, 1194, 62, 853 }, Collider::Type::LEFT_WALL);


	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 400, 500);
	//App->enemies->AddEnemy(Enemy_Type::BOSS, 400, 600);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	//App->enemies->AddEnemy(Enemy_Type::MECH, 900, 195);

	// Breakables ---
	//App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 210, 120);
	//App->breakables->AddBreakable(BREAKABLE_TYPE::DOOR, 113, 52, 0);
	//App->breakables->AddBreakable(BREAKABLE_TYPE::DOOR, 400, 120, 1);
	//App->breakables->AddBreakable(BREAKABLE_TYPE::CARDBOX, 400, 190, 0);
	//App->breakables->AddBreakable(BREAKABLE_TYPE::CARDBOX, 430, 190, 1);
	//App->breakables->AddBreakable(BREAKABLE_TYPE::TABLE, 430, 250, 0);
	//App->breakables->AddBreakable(BREAKABLE_TYPE::TABLE, 430, 250, 1);
	//App->breakables->AddBreakable(BREAKABLE_TYPE::GOBLET, 430, 250, 0);
	//App->breakables->AddBreakable(BREAKABLE_TYPE::GOBLET, 430, 250, 1);
	//App->breakables->AddBreakable(BREAKABLE_TYPE::GOBLET, 210, -200, 1);

	// Powerups ---
	//App->powerups->AddPowerup(POWERUP_TYPE::DICE, 210, 180);

	App->player->Enable();
	App->enemies->Enable();
	App->powerups->Enable();
	App->breakables->Enable();
	App->collisions->Enable();
	App->ui->Enable();

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
	App->ui->Disable();
	
	return true;
}