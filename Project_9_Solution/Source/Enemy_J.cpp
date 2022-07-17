#include "Enemy_J.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SDL/include/SDL.h"

Enemy_J::Enemy_J(int x, int y) : Enemy(x, y) {
	idleAnim.PushBack({ 5, 108, 31, 29 });
	idleAnim.speed = 0.1f;
	idleAnim.loop = true;
	currentAnim = &idleAnim;
	timerSpawn = SDL_GetTicks();
	healthPoints = JHEALTH;
	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_J::Update() {
	int currentTime = SDL_GetTicks();
	if ((timerSpawn - currentTime)/3000.0f >= SPAWN_TIMER) {
		timerSpawn = currentTime;
		//App->enemies->AddEnemy(ENEMY_TYPE::TACKLER, position.x + 92, position.y + SCREEN_WIDTH);
	}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
