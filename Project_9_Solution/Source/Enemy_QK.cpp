#include "Enemy_QK.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"

#include "ModuleFonts.h"
#include <string>
using namespace std;

Enemy_QK::Enemy_QK(int x, int y) : Enemy(x, y)
{
	QKinitAnimations();

	healthPoints = QKHEALTH;
	collider = App->collisions->AddCollider({ 0, 0, 79, 57 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_QK::Update()
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

	//shotPos = shotSpawn;
	shotPos.x += 2 * cos(degrees);
	shotPos.y += 2 * sin(degrees);

	Enemy::Update();
}

void Enemy_QK::QKstartAttack()
{
	QKattacking = true;
	startTimer = SDL_GetTicks();
}

void Enemy_QK::QKattack()
{
	currentTime = SDL_GetTicks();
	if (currentTime - startTimer >= 1000 && currentTime - startTimer <= 1100)
	{
		if (degrees > 45 && degrees < 135)
		{
			attackdir = 0;
		}

		//Left
		if (degrees > 135 && degrees < 225)
		{
			attackdir = 1;
		}

		//Up
		if (degrees > 225 && degrees < 315)
		{
			attackdir = 2;
		}

		//Right
		if (degrees > 315 || degrees < 45)
		{
			attackdir = 3;
		}
	}

	if (QKattacking && currentTime - startTimer > 1200)
	{
		shotSpawn.x = position.x;
		shotSpawn.y = position.y;
		
		switch (attackdir)
		{
		case 0://Down
			shotSpawn.y += 30;
			shotSpawn.x += 0;
			App->particles->AddParticle(App->particles->QK_SwordAttackUp, shotSpawn.x, shotSpawn.y, Collider::Type::ENEMY_SHOT);
			break;
		case 1://Left
			shotSpawn.y += 0;
			shotSpawn.x += -30;
			App->particles->AddParticle(App->particles->QK_SwordAttackUp, shotSpawn.x, shotSpawn.y, Collider::Type::ENEMY_SHOT);
			break;
		case 2://Up
			shotSpawn.y += -30;
			shotSpawn.x += 0;
			App->particles->AddParticle(App->particles->QK_SwordAttackUp, shotSpawn.x, shotSpawn.y, Collider::Type::ENEMY_SHOT);
			break;
		case 3://Right
			shotSpawn.y += 0;
			shotSpawn.x += 60;
			App->particles->AddParticle(App->particles->QK_SwordAttackUp, shotSpawn.x, shotSpawn.y, Collider::Type::ENEMY_SHOT);
			break;
		default:
			break;
		}
		//Particle* newParticle = App->particles->AddParticle(App->particles->QK_SwordAttackUp, shotSpawn.x, shotSpawn.y, Collider::Type::PLAYER_SHOT);
		//newParticle->collider->AddListener(this);
		QKattacking = false;
	}
}

void Enemy_QK::QKtrackPlayer()
{

}

void Enemy_QK::QKinitAnimations()
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

void Enemy_QK::deathAnimation() {}