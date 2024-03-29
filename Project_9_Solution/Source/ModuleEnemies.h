#ifndef __MODULE_ENEMIES_H__
#define __MODULE_ENEMIES_H__
#include "Module.h"
#include "ModuleDebug.h"
#define MAX_ENEMIES 150
enum class Enemy_Type
{
	NO_TYPE,
	BASECARD,
	BOSS,
	QK,
};

struct EnemySpawnpoint
{
	Enemy_Type type = Enemy_Type::NO_TYPE;
	int x = -1, y = -1;
	unsigned short version = 0;
};
class Enemy;
struct SDL_Texture;
class ModuleEnemies : public Module
{
public:
	// Constructor
	ModuleEnemies(bool startEnabled);
	// Destructor
	~ModuleEnemies();
	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;
	// Called at the beginning of the application loop
	// Removes all enemies pending to delete
	Update_Status PreUpdate() override;
	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	Update_Status Update() override;
	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	Update_Status PostUpdate() override;
	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;
	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;
	// Add an enemy into the queue to be spawned later
	bool AddEnemy(Enemy_Type type, int x, int y, unsigned short version = 0);
	// Iterates the queue and checks for camera position
	void HandleEnemiesSpawn();
private:
	// Spawns a new enemy using the data from the queue
	void SpawnEnemy(const EnemySpawnpoint& info);
private:
	// A queue with all spawn points information
	EnemySpawnpoint spawnQueue[MAX_ENEMIES];
	// All spawned enemies in the scene
	Enemy* enemies[MAX_ENEMIES] = { nullptr };
	// The enemies sprite sheet
	SDL_Texture* baseCardTexture = nullptr;
	SDL_Texture* bossTexture = nullptr;
	SDL_Texture* QK_midboss = nullptr;

	// The audio fx for destroying an enemy
	int enemyDestroyedFx = 0;
	friend void ModuleDebug::DebugDraw();
};
#endif // __MODULE_ENEMIES_H__