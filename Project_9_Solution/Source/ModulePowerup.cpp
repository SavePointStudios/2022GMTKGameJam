#include "ModulePowerup.h"

#include "Application.h"
#include "Globals.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "Powerup.h"
#include "Powerup_Dice.h"

#define SPAWN_MARGIN	50

ModulePowerup::ModulePowerup(bool startEnabled) : Module(startEnabled) {
	for (uint i = 0; i < MAX_POWERUPS; ++i)
		powerUps[i] = nullptr;
}

ModulePowerup::~ModulePowerup() {
}

bool ModulePowerup::Start() {

	//powerupPickUpFx = App->audio->LoadFx("Assets/sounds/sfx/16 5.wav");

	return true;
}

Update_Status ModulePowerup::PreUpdate() {
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_POWERUPS; ++i) {
		if (powerUps[i] != nullptr && powerUps[i]->pendingToDelete) {
			delete powerUps[i];
			powerUps[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePowerup::Update() {
	HandlePowerupsSpawn();

	for (uint i = 0; i < MAX_POWERUPS; ++i) {
		if (powerUps[i] != nullptr)
			powerUps[i]->Update();
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePowerup::PostUpdate() {
	for (uint i = 0; i < MAX_POWERUPS; ++i) {
		if (powerUps[i] != nullptr)
			powerUps[i]->Draw();
	}
	return Update_Status::UPDATE_CONTINUE;
}

bool ModulePowerup::CleanUp() {
	LOG("Freeing all powerups");
	for (uint i = 0; i < MAX_POWERUPS; ++i) {
		if (powerUps[i] != nullptr) {
			delete powerUps[i];
			powerUps[i] = nullptr;
		}
	}

	return true;
}

bool ModulePowerup::AddPowerup(POWERUP_TYPE type, int x, int y) {
	bool ret = false;

	for (uint i = 0; i < MAX_POWERUPS; ++i) {
		if (spawnQueue[i].type == POWERUP_TYPE::NO_TYPE) {
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModulePowerup::HandlePowerupsSpawn() {
	// Iterate all the powerups queue
	for (uint i = 0; i < MAX_POWERUPS; ++i) {
		if (spawnQueue[i].type != POWERUP_TYPE::NO_TYPE) {
			// Spawn a new powerup if the screen has reached a spawn position
			if (spawnQueue[i].y * SCREEN_SIZE < (App->render->camera.y + App->render->camera.h) * SCREEN_SIZE + SPAWN_MARGIN &&
				spawnQueue[i].x * SCREEN_SIZE >= App->render->camera.x * SCREEN_SIZE - SPAWN_MARGIN &&
				spawnQueue[i].x * SCREEN_SIZE <= (App->render->camera.x + App->render->camera.w) * SCREEN_SIZE + SPAWN_MARGIN) {
				LOG("Spawning powerup at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnPowerup(spawnQueue[i]);
				spawnQueue[i].type = POWERUP_TYPE::NO_TYPE; // Removing the newly spawned powerup from the queue
			}
		}
	}
}

void ModulePowerup::SpawnPowerup(const PowerupSpawnpoint& info) {
	// Find an empty slot in the powerups array
	for (uint i = 0; i < MAX_POWERUPS; ++i) {
		if (powerUps[i] == nullptr) {
			switch (info.type) {
			case POWERUP_TYPE::DICE:
				powerUps[i] = new Powerup_Dice(info.x, info.y);
				break;
			}
			powerUps[i]->texture = powerupTexture;
			//powerUps[i]->pickUpFx = this->powerupPickUpFx;
			break;
		}
	}
}

void ModulePowerup::OnCollision(Collider* c1, Collider* c2) {
	for (uint i = 0; i < MAX_POWERUPS; ++i) {
		if (powerUps[i] != nullptr && powerUps[i]->GetCollider() == c1) {
			powerUps[i]->OnCollision(c2);
			delete powerUps[i];
			powerUps[i] = nullptr;
			break;
		}
	}
}