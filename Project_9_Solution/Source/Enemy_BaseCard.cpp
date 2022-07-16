#include "Enemy_BaseCard.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

Enemy_BaseCard::Enemy_BaseCard(int x, int y) : Enemy(x, y)
{
	initAnimations();
	
	collider = App->collisions->AddCollider({0, 0, 64, 64}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BaseCard::Update()
{
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	if (sqrt(pow(distance.x, 2) + pow(distance.y, 2)) > 100)
	{
		position.x += 2 * cos(alpha);
		position.y += 2 * sin(alpha);
	}

	Enemy::Update();
}

void Enemy_BaseCard::initAnimations()
{
	walk.PushBack({ 5,72,21,22 });
	currentAnim = &walk;
}
