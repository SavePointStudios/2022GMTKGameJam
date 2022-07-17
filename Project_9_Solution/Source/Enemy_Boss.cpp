#include "Enemy_Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Boss::Enemy_Boss(int x, int y) : Enemy(x, y)
{
	idleAnim.PushBack({ 0,0,64,96 });
	idleAnim.PushBack({ 64,0,64,96 });
	idleAnim.PushBack({ 128,0,64,96 });
	idleAnim.PushBack({ 192,0,64,96 });
	idleAnim.PushBack({ 256,0,64,96 });
	idleAnim.speed = 0.2f;

	spinAnim.PushBack({ 320,0,64,96 });
	spinAnim.PushBack({ 384,0,64,96 });
	spinAnim.PushBack({ 448,0,64,96 });
	spinAnim.PushBack({ 512,0,64,96 });
	spinAnim.PushBack({ 576,0,64,96 });
	spinAnim.speed = 0.2f;

	deathAnim.PushBack({ 0,96,64,96 });
	deathAnim.PushBack({ 64,96,64,96 });
	deathAnim.PushBack({ 128,96,64,96 });
	deathAnim.PushBack({ 192,96,64,96 });
	deathAnim.PushBack({ 256,96,64,96 });
	deathAnim.PushBack({ 320,96,64,96 });
	deathAnim.PushBack({ 384,96,64,96 });
	deathAnim.PushBack({ 448,96,64,96 });
	deathAnim.PushBack({ 512,96,64,96 });
	deathAnim.PushBack({ 576,96,64,96 });
	deathAnim.speed = 0.2f;


	currentAnim = &idleAnim;

	collider = App->collisions->AddCollider({ 0, 0, 64, 96 }, Collider::Type::BOSS, (Module*)App->enemies);
}

void Enemy_Boss::Update()
{
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}