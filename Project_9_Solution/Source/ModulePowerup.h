#ifndef __MODULE_POWERUP_H__
#define __MODULE_POWERUP_H__

#include "Module.h"

#define MAX_POWERUPS	100

enum class POWERUP_TYPE {
	NO_TYPE, DICE
};

struct PowerupSpawnpoint {
	POWERUP_TYPE type = POWERUP_TYPE::NO_TYPE;
	int x, y;
};

class Powerup;
struct SDL_Texture;

class ModulePowerup : public Module {
public:
	// Constructor
	ModulePowerup(bool startEnabled);

	// Destructor
	~ModulePowerup();

	// Called when the module is activated
	// Loads the necessary textures for the powerups
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles powerup movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the powerup sprite
	Update_Status PostUpdate() override;

	bool CleanUp() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add a powerup into the queue to be spawned later
	bool AddPowerup(POWERUP_TYPE type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandlePowerupsSpawn();

	// Destroys any powerups that have moved outside the camera limits
	void HandlePowerupsDespawn();

private:
	// Spawns a new powerup using the data from the queue
	void SpawnPowerup(const PowerupSpawnpoint& info);

private:
	// A queue with all spawn points information
	PowerupSpawnpoint spawnQueue[MAX_POWERUPS];

	// All spawned powerups in the scene
	Powerup* powerUps[MAX_POWERUPS] = { nullptr };

	// The powerups sprite sheet
	SDL_Texture* powerupTexture = nullptr;

	// The audio fx for picking up a powerup
	int powerupPickUpFx = 0;
	
};

#endif // __MODULE_POWERUP_H__