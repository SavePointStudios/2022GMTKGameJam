#include "Enemy_QK.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"

#include "ModuleFonts.h"
#include <string>
using namespace std;

ModuleQK::ModuleQK(int x, int y) : Enemy(x, y)
{
	QKinitAnimations();

	healthPoints = QKHEALTH;
	collider = App->collisions->AddCollider({ 0, 0, 79, 57 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void ModuleQK::Update()
{
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position

	if (!QKattacking)
		QKstartAttack();

	if (QKattacking)
		QKattack();

	if (healthPoints <= 0) {
		//App->particles->AddParticle(App->particles->cardDeath, position.x, position.y);
		App->audio->PlayFx(destroyedFx);

		SetToDelete();
	}

	Enemy::Update();
}

void ModuleQK::QKstartAttack()
{
	QKattacking = true;
	startTimer = SDL_GetTicks();
}

void ModuleQK::QKattack()
{
	currentTime = SDL_GetTicks();
	if (currentTime - startTimer >= 1000 && currentTime - startTimer <= 1100)
	{
		if (degrees > 45 && degrees < 135)
		{
			attackdir = 0;
			moveUp += QKattackSpeed;
		}

		//Left
		if (degrees > 135 && degrees < 225)
		{
			attackdir = 1;
			moveLeft += QKattackSpeed;
		}

		//Up
		if (degrees > 225 && degrees < 315)
		{
			attackdir = 2;
			moveDown += QKattackSpeed;
		}

		//Right
		if (degrees > 315 || degrees < 45)
		{
			attackdir = 3;
			moveRight += QKattackSpeed;
		}
	}

	if (QKattacking && currentTime - startTimer > 1200)
	{
		switch (attackdir)
		{
		case 0://Down
			App->particles->AddParticle(App->particles->QK_SwordAttack, position.x, moveDown, Collider::Type::ENEMY_SHOT);
			break;
		case 1://Left
			App->particles->AddParticle(App->particles->QK_SwordAttack, moveLeft, position.y, Collider::Type::ENEMY_SHOT);
			break;
		case 2://Up
			App->particles->AddParticle(App->particles->QK_SwordAttack, position.x, moveUp, Collider::Type::ENEMY_SHOT);
			break;
		case 3://Right
			App->particles->AddParticle(App->particles->QK_SwordAttack, moveRight, position.y, Collider::Type::ENEMY_SHOT);
			break;
		default:
			break;
		}
		QKattacking = false;
	}
}

void ModuleQK::QKinitAnimations()
{
	//Front
	idleAnimation.PushBack({ 9, 3, 126, 57 });
	idleAnimation.PushBack({ 7, 67, 130, 55 });
	idleAnimation.PushBack({ 7, 129, 126, 57 });
	idleAnimation.PushBack({ 5, 194, 130, 59 });
	idleAnimation.speed = 0.1f;
	idleAnimation.loop = true;

	currentAnim = &idleAnimation;
}