#include "Enemy_QK.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL.h"

#include "ModuleFonts.h"
#include <string>
using namespace std;

Enemy_QK::Enemy_QK(int x, int y) : Enemy(x, y)
{
	initAnimations();
	collider = App->collisions->AddCollider({ 0, 0, 120, 64 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_QK::Update()
{
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position

	Enemy::Update();
}

void Enemy_QK::initAnimations()
{

}
