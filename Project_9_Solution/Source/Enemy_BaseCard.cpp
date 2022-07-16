#include "Enemy_BaseCard.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL.h"

Enemy_BaseCard::Enemy_BaseCard(int x, int y) : Enemy(x, y)
{
	initAnimations();
	
	collider = App->collisions->AddCollider({0, 0, 32, 64}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BaseCard::Update()
{
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	
	if (distance.x > 30 || distance.x < -30 || distance.y > 30 || distance.y < -30)
	{
		if (distance.x > 31 || distance.x < -31)
		{
			position.x += 2 * cos(alpha);
		}
		if (distance.y > 31 || distance.y < -31)
		{
			position.y += 2 * sin(alpha);
		}
	}
	else
	{
		//attack();
	}


	Enemy::Update();
}

void Enemy_BaseCard::attack()
{
	currentTime = SDL_GetTicks();

	if (!attacking)
	{
		startTimer = SDL_GetTicks();
		attacking = true;
	}

	if (attacking && currentTime - startTimer > 2000)
	{
		//Down
		if (degrees > 45 && degrees < 135)
			App->particles->AddParticle(App->particles->cardAttackMelee, position.x, position.y + 32, Collider::Type::ENEMY_SHOT);
		//Left
		if (degrees > 135 && degrees < 225)
			App->particles->AddParticle(App->particles->cardAttackMelee, position.x - 32, position.y, Collider::Type::ENEMY_SHOT);
		//Up
		if (degrees > 225 && degrees < 315)
			App->particles->AddParticle(App->particles->cardAttackMelee, position.x, position.y - 32, Collider::Type::ENEMY_SHOT);
		//Right
		if (degrees > 315 || degrees < 45)
			App->particles->AddParticle(App->particles->cardAttackMelee, position.x + 32, position.y, Collider::Type::ENEMY_SHOT);


		attacking = false;
	}
}

void Enemy_BaseCard::initAnimations()
{
	walk.PushBack({ 5,72,21,22 });
	currentAnim = &walk;
}
