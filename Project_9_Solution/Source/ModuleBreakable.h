#ifndef __MODULE_BREAKABLE_H__
#define __MODULE_BREAKABLE_H__

#include "Module.h"

#define MAX_BREAKABLES		170

enum class BREAKABLE_TYPE {
	NO_TYPE,
	BARRICADE_H,
	BARRICADE_V,
	BRIDGE,
	FENCE,
	BARBED_1,
	BARBED_2,
};

struct BreakableSpawnpoint {
	BREAKABLE_TYPE type = BREAKABLE_TYPE::NO_TYPE;
	int x, y;
	ushort version = 0;
};

class Breakable;
struct SDL_Texture;

class ModuleBreakable : public Module {
public:
	// Constructor
	ModuleBreakable(bool startEnabled);

	// Destructor
	~ModuleBreakable();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	update_status Update() override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	update_status PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an enemy into the queue to be spawned later
	bool AddBreakable(BREAKABLE_TYPE type, int x, int y, ushort version = 0);

	// Iterates the queue and checks for camera position
	void HandleBreakablesSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleBreakablesDespawn();

private:
	// Spawns a new enemy using the data from the queue
	void SpawnBreakable(const BreakableSpawnpoint& info);

private:
	// A queue with all spawn points information
	BreakableSpawnpoint spawnQueue[MAX_BREAKABLES];

	// All spawned enemies in the scene
	Breakable* breakables[MAX_BREAKABLES] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* breakableTexture = nullptr;

};

#endif // __MODULE_BREAKABLE_H__