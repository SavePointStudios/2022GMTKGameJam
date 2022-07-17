#include "Enemy_BaseCard.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"

#include "ModuleFonts.h"
#include <string>
using namespace std;

Enemy_BaseCard::Enemy_BaseCard(int x, int y) : Enemy(x, y)
{
	initAnimations();
	healthPoints = NUMHEALTH;
	collider = App->collisions->AddCollider({0, 0, 32, 64}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BaseCard::Update()
{
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position

	if (spread)
	{
		position.x += 2 * cos(beta);
		position.y += 2 * sin(beta);
	}
	else if (App->debug->GetChase())
	{
		if ((distance.x > 30 || distance.x < -30 || distance.y > 30|| distance.y < -30) && !attacking)
			updateMovement();

		else if (!attacking)
			startAttack();

		if (attacking)
			attack();
	}

	if (healthPoints <= 0) {
		App->particles->AddParticle(App->particles->cardDeath, position.x, position.y);
		App->audio->PlayFx(destroyedFx);

		SetToDelete();
	}
	Enemy::Update();
}

void Enemy_BaseCard::updateMovement()
{
	if (distance.x > 31)
	{
		position.x += movSpeed;
		if (currentAnim != &walkRight)
			currentAnim = &walkRight;
	}
	if (distance.x < -31)
	{
		position.x -= movSpeed;
		if (currentAnim != &walkLeft)
			currentAnim = &walkLeft;
	}
	if (distance.y > 31)
	{
		position.y += movSpeed;
		if (currentAnim != &walkDown)
			currentAnim = &walkDown;
	}
	if (distance.y < -31)
	{
		position.y -= movSpeed;
		if (currentAnim != &walkUp)
			currentAnim = &walkUp;
	}
}

void Enemy_BaseCard::startAttack()
{
	attacking = true;
	startTimer = SDL_GetTicks();
}

void Enemy_BaseCard::attack()
{
	currentTime = SDL_GetTicks();

	if (currentTime - startTimer >= 500 && currentTime - startTimer <= 600)	{
		//Down
		if (degrees > 45 && degrees < 135)
		{
			attackdir = 0;
			currentAnim = &attackDown;
		}

		//Left
		if (degrees > 135 && degrees < 225)
		{
			attackdir = 1;
			currentAnim = &attackLeft;
		}

		//Up
		if (degrees > 225 && degrees < 315)
		{
			attackdir = 2;
			currentAnim = &attackUp;
		}

		//Right
		if (degrees > 315 || degrees < 45)
		{
			attackdir = 3;
			currentAnim = &attackRight;
		}
	}

	if (attacking && currentTime - startTimer > 700)
	{
		switch (attackdir)
		{
		case 0://Down
			App->particles->AddParticle(App->particles->cardAttackMelee, position.x, position.y + 32, Collider::Type::ENEMY_SHOT);
			attackDown.Reset();
			break;
		case 1://Left
			App->particles->AddParticle(App->particles->cardAttackMelee, position.x - 32, position.y, Collider::Type::ENEMY_SHOT);
			attackLeft.Reset();
			break;
		case 2://Up
			App->particles->AddParticle(App->particles->cardAttackMelee, position.x, position.y - 32, Collider::Type::ENEMY_SHOT);
			attackUp.Reset();
			break;
		case 3://Right
			App->particles->AddParticle(App->particles->cardAttackMelee, position.x + 32, position.y, Collider::Type::ENEMY_SHOT);
			attackRight.Reset();
			break;
		default:
			break;
		}

		attacking = false;
	}
}

void Enemy_BaseCard::initAnimations()
{
	walkRight.PushBack({ 128,0,32,64 });
	walkRight.PushBack({ 160,0,32,64 });
	walkRight.PushBack({ 192,0,32,64 });
	walkRight.PushBack({ 224,0,32,64 });
	walkRight.speed = 0.2f;
	walkRight.loop = true;

	walkLeft.PushBack({ 0,0,32,64 });
	walkLeft.PushBack({ 32,0,32,64 });
	walkLeft.PushBack({ 64,0,32,64 });
	walkLeft.PushBack({ 96,0,32,64 });
	walkLeft.speed = 0.2f;
	walkLeft.loop = true;

	walkUp.PushBack({ 0,576,32,64 });
	walkUp.PushBack({ 32,576,32,64 });
	walkUp.PushBack({ 64,576,32,64 });
	walkUp.PushBack({ 96,576,32,64 });
	walkUp.speed = 0.2f;
	walkUp.loop = true;

	walkDown.PushBack({ 256,0,32,64 });
	walkDown.PushBack({ 288,0,32,64 });
	walkDown.PushBack({ 320,0,32,64 });
	walkDown.PushBack({ 352,0,32,64 });
	walkDown.speed = 0.2f;
	walkDown.loop = true;

	attackRight.PushBack({ 512,0,32,64 });
	attackRight.PushBack({ 544,0,32,64 });
	attackRight.PushBack({ 576,0,32,64 });
	attackRight.PushBack({ 608,0,32,64 });
	attackRight.speed = 0.4;
	attackRight.loop = false;

	attackLeft.PushBack({ 384,0,32,64 });
	attackLeft.PushBack({ 416,0,32,64 });
	attackLeft.PushBack({ 448,0,32,64 });
	attackLeft.PushBack({ 480,0,32,64 });
	attackLeft.speed = 0.4;
	attackLeft.loop = false;

	attackUp.PushBack({ 128,576,32,64 });
	attackUp.PushBack({ 160,576,32,64 });
	attackUp.PushBack({ 192,576,32,64 });
	attackUp.PushBack({ 224,576,32,64 });
	attackUp.speed = 0.4;
	attackUp.loop = false;

	attackDown.PushBack({ 640,0,32,64 });
	attackDown.PushBack({ 672,0,32,64 });
	attackDown.PushBack({ 704,0,32,64 });
	attackDown.PushBack({ 736,0,32,64 });
	attackDown.speed = 0.4;
	attackDown.loop = false;
	attackDown.pingpong = false;

	currentAnim = &walkRight;

	path.PushBack({0.0f,0.0f}, 4, currentAnim);
}
