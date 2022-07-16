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
	
	if ((distance.x > 30 || distance.x < -30 || distance.y > 30 || distance.y < -30) && !attacking)
		updateMovement();

	else if (!attacking)
		startAttack();

	if (attacking)
		attack();

	Enemy::Update();
}

void Enemy_BaseCard::updateMovement()
{
	if (distance.x > 31)
	{
		position.x += movSpeed;
	}
	if (distance.x < -31)
	{
		position.x -= movSpeed;
	}
	if (distance.y > 31)
	{
		position.y += movSpeed;
	} 
	if (distance.y < -31)
	{
		position.y -= movSpeed;
	}
}

void Enemy_BaseCard::startAttack()
{
	attacking = true;
	startTimer = SDL_GetTicks();
	//Down
	if (degrees > 45 && degrees < 135)
		attackdir = 0;
	//Left
	if (degrees > 135 && degrees < 225)
		attackdir = 1;
	//Up
	if (degrees > 225 && degrees < 315)
		attackdir = 2;
	//Right
	if (degrees > 315 || degrees < 45)
		attackdir = 3;
}

void Enemy_BaseCard::attack()
{
	currentTime = SDL_GetTicks();

	if (attacking && currentTime - startTimer > 2000)
	{
		switch (attackdir)
		{
		case 0:
			App->particles->AddParticle(App->particles->cardAttackMelee, position.x, position.y + 32, Collider::Type::ENEMY_SHOT);
			break;
		case 1:
			App->particles->AddParticle(App->particles->cardAttackMelee, position.x - 32, position.y, Collider::Type::ENEMY_SHOT);
			break;
		case 2:
			App->particles->AddParticle(App->particles->cardAttackMelee, position.x, position.y - 32, Collider::Type::ENEMY_SHOT);
			break;
		case 3:
			App->particles->AddParticle(App->particles->cardAttackMelee, position.x + 32, position.y, Collider::Type::ENEMY_SHOT);
			break;
		default:
			break;
		}

		attacking = false;
	}
}

void Enemy_BaseCard::initAnimations()
{
	walk.PushBack({ 5,72,21,22 });
	currentAnim = &walk;
}
