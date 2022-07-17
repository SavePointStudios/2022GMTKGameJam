#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Enemy.h"
#include "Enemy_RedBird.h"
#include "Enemy_Basecard.h"
#include "Enemy_Mech.h"
#include "Enemy_Boss.h"

#define SPAWN_MARGIN	80

ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
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
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	SpreadEnemies();

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

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
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

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == Enemy_Type::NO_TYPE)
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
				case Enemy_Type::REDBIRD:
					enemies[i] = new Enemy_RedBird(info.x, info.y);
					break;
				case Enemy_Type::BROWNSHIP:
					enemies[i] = new Enemy_BaseCard(info.x, info.y);
					break;
				case Enemy_Type::MECH:
					enemies[i] = new Enemy_Mech(info.x, info.y);
					break;
				case Enemy_Type::BASECARD:
					enemies[i] = new Enemy_BaseCard(info.x, info.y);
					break;
				case Enemy_Type::BOSS:
					enemies[i] = new Enemy_Boss(info.x, info.y);
					break;
			}
			if(info.type == Enemy_Type::BOSS)
			enemies[i]->texture = bossTexture;
			else
			enemies[i]->texture = baseCardTexture;

			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void ModuleEnemies::SpreadEnemies()
{
	for (size_t i = 0; i < MAX_ENEMIES - 1; i++)
	{
		float distMin = 50;

		for (size_t j = i + 1; j < MAX_ENEMIES; j++)
		{
			if (enemies[i] != nullptr && enemies[j] != nullptr)
			{
				float deltaX = enemies[j]->position.x + 16 - (enemies[i]->position.x + 16);
				float deltaY = enemies[j]->position.y + 32 - (enemies[i]->position.y + 32);

				float dist = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

				distMin = dist < distMin ? dist : distMin;

				if (dist < 50 && dist <= distMin)
				{
					if (enemies[i]->spread == 0)
					{
						enemies[i]->spread = 10;

						enemies[i]->beta = atan2(-deltaY, -deltaX) + 180;  // / (M_PI / 180);

						/*if (enemies[i]->beta < 0)
							enemies[i]->beta += 360.0f;*/
					}
					enemies[i]->spread--;
				}
				else
					enemies[i]->spread = 0;
			}
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
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