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
	bgTexture = App->textures->Load("Assets/Sprites/background.png");
	mapTexture = App->textures->Load("Assets/Sprites/map_base.png");
	
	// Room 1 Music
	App->audio->PlayMusic("Assets/Music/Stage1.ogg", 1.0f); // music that plays in the first room
	//App->audio->PlayMusic("Assets/Music/Stage2.ogg", 1.0f); // music that plays in the second room
	//App->audio->PlayMusic("Assets/Music/Final boss.ogg", 1.0f); // music that plays in the final boss fight room
	//App->audio->PlayMusic("Assets/Music/All enemies killed.ogg", 1.0f); // ambiance that plays when you kill a room boss

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
	// 1st room
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 520, 550, 5);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 250, 900, 2);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 135, 560, 3);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 280, 800, 4);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 430, 880, 7);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 580, 70, 8);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 525, 200, 10);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 400, 500, 6);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 950, 775, 6);

	// 2nd room
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 1340, 700, 6);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 1410, 700, 10);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 1480, 700, 9);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 1550, 700, 3);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 1620, 700, 2);

	// 3rd room
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 1960, 870, 6);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 2060, 870, 10);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 2111, 870, 9);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 2165, 870, 3);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 2215, 870, 2);

	// 4th room
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 1960, 870, 2);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 2060, 870, 3);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 2111, 870, 7);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 2165, 870, 8);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 2215, 870, 10);

	App->enemies->AddEnemy(Enemy_Type::BASECARD, 2185, 1364, 10);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 2282, 1484, 10);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 2315, 1600, 10);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 2163, 1645, 10);

	App->enemies->AddEnemy(Enemy_Type::BASECARD, 860, 1637, 10);
	App->enemies->AddEnemy(Enemy_Type::BASECARD, 860, 1732, 10);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	// Breakables ---
	// 1st room
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 256, 324);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 412, 364);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 358, 665);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 358, 750);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 460, 665);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 585, 403);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 593, 435);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 617, 403);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 385, 240);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 440, 435);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 370, 270);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 455, 280);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 930, 715);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 930, 715);

	App->breakables->AddBreakable(BREAKABLE_TYPE::CARDBOX, 1680, 840, 0);

	// 2nd room
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 1660, 580);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 1692, 580);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 1580, 550);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 1725, 640);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 1436, 521);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 1265, 530);
	App->breakables->AddBreakable(BREAKABLE_TYPE::GOBLET, 1330, 820, 0);
	App->breakables->AddBreakable(BREAKABLE_TYPE::GOBLET, 1362, 820, 0);
	App->breakables->AddBreakable(BREAKABLE_TYPE::GOBLET, 1340, 852, 0);
	
	//3rd room
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 2215, 815);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 1890, 1220);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 1750, 845);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 1777, 880);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 1756, 900);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 2080, 1300);
	App->breakables->AddBreakable(BREAKABLE_TYPE::GOBLET, 1900, 1230, 0);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CARDBOX, 2050, 1030, 0);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CARDBOX, 2300, 1400, 0);
	//4th room
	App->breakables->AddBreakable(BREAKABLE_TYPE::GOBLET, 2254, 1458, 0);
	App->breakables->AddBreakable(BREAKABLE_TYPE::GOBLET, 2213, 1600, 0);

	// Boss room
	App->breakables->AddBreakable(BREAKABLE_TYPE::GOBLET, 63, 1224, 0);
	App->breakables->AddBreakable(BREAKABLE_TYPE::GOBLET, 812, 1224, 0);
	App->breakables->AddBreakable(BREAKABLE_TYPE::GOBLET, 63, 1974, 0);
	App->breakables->AddBreakable(BREAKABLE_TYPE::GOBLET, 812, 1974, 0);
	App->breakables->AddBreakable(BREAKABLE_TYPE::GOBLET, 1680, 872, 0);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 200, 1464);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 400, 1546);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 600, 1838);
	App->breakables->AddBreakable(BREAKABLE_TYPE::CHIPSTACK, 545, 1872);

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
	App->render->Blit(bgTexture, -160, -40, NULL);
	App->render->Blit(mapTexture, 0, 0, NULL);

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
	
	App->textures->Unload(bgTexture);
	App->textures->Unload(mapTexture);

	return true;
}