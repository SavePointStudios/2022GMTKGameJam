#include "ModuleBreakable.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Breakable.h"
#include "Breakable_Fence.h"

#include "Collider.h"

#define SPAWN_MARGIN	260

ModuleBreakable::ModuleBreakable(bool startEnabled) : Module(startEnabled) {
	for (uint i = 0; i < MAX_BREAKABLES; ++i)
		breakables[i] = nullptr;
}

ModuleBreakable::~ModuleBreakable() {

}

bool ModuleBreakable::Start() {
	breakableTexture = App->textures->Load("Assets/img/sprites/breakables.png");

	return true;
}

Update_Status ModuleBreakable::Update() {
	HandleBreakablesSpawn();

	for (uint i = 0; i < MAX_BREAKABLES; ++i) {
		if (breakables[i] != nullptr)
			breakables[i]->Update();
	}

	HandleBreakablesDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleBreakable::PostUpdate() {
	for (uint i = 0; i < MAX_BREAKABLES; ++i) {
		if (breakables[i] != nullptr)
			breakables[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleBreakable::CleanUp() {
	LOG("Freeing all breakables");

	App->textures->Unload(breakableTexture);

	for (uint i = 0; i < MAX_BREAKABLES; ++i) {
		if (breakables[i] != nullptr) {
			App->textures->Unload(breakables[i]->texture);
			delete breakables[i];
			breakables[i] = nullptr;
		}
	}

	return true;
}

bool ModuleBreakable::AddBreakable(BREAKABLE_TYPE type, int x, int y, ushort version) {
	bool ret = false;

	for (uint i = 0; i < MAX_BREAKABLES; ++i) {
		if (spawnQueue[i].type == BREAKABLE_TYPE::NO_TYPE) {
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			if (version != 0) {
				spawnQueue[i].version = version;
			}
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleBreakable::HandleBreakablesSpawn() {
	// Iterate all the breakables queue
	for (uint i = 0; i < MAX_BREAKABLES; ++i) {
		if (spawnQueue[i].type != BREAKABLE_TYPE::NO_TYPE) {
			// Spawn a new breakable if the screen has reached a spawn position
			if (spawnQueue[i].y > App->render->camera.y - SPAWN_MARGIN) {
				LOG("Spawning breakable at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnBreakable(spawnQueue[i]);
				spawnQueue[i].type = BREAKABLE_TYPE::NO_TYPE; // Removing the newly spawned breakable from the queue
			}
		}
	}
}

void ModuleBreakable::HandleBreakablesDespawn() {
	// Iterate existing breakables
	for (uint i = 0; i < MAX_BREAKABLES; ++i) {
		if (breakables[i] != nullptr) {
			// Delete the breakable when it has reached the end of the screen
			if (breakables[i]->position.y > App->render->camera.y + App->render->camera.h + SPAWN_MARGIN) {
				LOG("DeSpawning breakable at %d", breakables[i]->position.x * SCREEN_SIZE);

				delete breakables[i];
				breakables[i] = nullptr;
			}
		}
	}
}

void ModuleBreakable::SpawnBreakable(const BreakableSpawnpoint& info) {
	// Find an empty slot in the breakables array
	for (uint i = 0; i < MAX_BREAKABLES; ++i) {
		if (breakables[i] == nullptr) {
			switch (info.type) {
			case BREAKABLE_TYPE::FENCE:
				breakables[i] = new Breakable_Fence(info.x, info.y, info.version);
				breakables[i]->texture = breakableTexture;
				break;
			}
			break;
		}
	}
}

void ModuleBreakable::OnCollision(Collider* c1, Collider* c2) {
	for (uint i = 0; i < MAX_BREAKABLES; ++i) {
		if (breakables[i] != nullptr && breakables[i]->GetCollider() == c1) {
			breakables[i]->OnCollision(c2); // Notify the breakable of a collision
			delete breakables[i];
			breakables[i] = nullptr;

			break;
		}
	}
}