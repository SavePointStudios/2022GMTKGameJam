#include "ModuleEnemies.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "Enemy.h"
#include "Enemy_Basecard.h"
#include "Enemy_Boss.h"

#define SPAWN_MARGIN	80

ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	baseCardTexture = App->textures->Load("Assets/Sprites/Card_Clubs_Sheet.png");
	bossTexture = App->textures->Load("Assets/Sprites/AceClubs-Sheet.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	QK_midboss = App->textures->Load("Assets / Sprites / midboss.png");

	return true;
}

Update_Status ModuleEnemies::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Update();
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}
	return true;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}
	return ret;
}
void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].y * SCREEN_SIZE > App->render->camera.y - SPAWN_MARGIN &&
				spawnQueue[i].x * SCREEN_SIZE >= App->render->camera.x - SPAWN_MARGIN &&
				spawnQueue[i].x * SCREEN_SIZE <= App->render->camera.x + App->render->camera.w + SPAWN_MARGIN) {
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);
				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}
void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
			case Enemy_Type::BASECARD:
				enemies[i] = new Enemy_BaseCard(info.x, info.y);
				enemies[i]->texture = baseCardTexture;
				break;
			case Enemy_Type::BOSS:
				enemies[i] = new Enemy_Boss(info.x, info.y);
				enemies[i]->texture = bossTexture;
				break;
			case Enemy_Type::QK:
				enemies[i] = new Enemy_QK(info.x, info.y);
				enemies[i]->texture = QK_midboss;
				break;
			}

			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			if (enemies[i]->healthPoints <= 0) {
				delete enemies[i];
				enemies[i] = nullptr;
			}
			break;
		}
	}
}