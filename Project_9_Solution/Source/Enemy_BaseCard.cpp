#include "Enemy_BaseCard.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL.h"

#include "ModuleFonts.h"
#include <string>
using namespace std;

Enemy_BaseCard::Enemy_BaseCard(int x, int y, unsigned short version) : Enemy(x, y)
{
	initAnimations(version);
	healthPoints = NUMHEALTH;
	collider = App->collisions->AddCollider({0, 0, 32, 64}, Collider::Type::ENEMY, (Module*)App->enemies);

	// Sound effects
	attackFx = App->audio->LoadFx("Assets/Fx/Cards/Attack.wav"); // Played when card attacks
	dieFx = App->audio->LoadFx("Assets/Fx/Cards/Die.wav"); // Played when card dies
	hitFx = App->audio->LoadFx("Assets/Fx/Cards/Hit.wav"); // Played when card is hit by player
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


	if (currentTime - startTimer >= 500 && currentTime - startTimer <= 600)
	{
		App->audio->PlayFx(attackFx);

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

void Enemy_BaseCard::initAnimations(unsigned short version)
{
	switch (version) {
	case 2:
#pragma region case2
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
#pragma endregion
		break;
	case 3:
#pragma region case3
		walkRight.PushBack({ 128,64,32,64 });
		walkRight.PushBack({ 160,64,32,64 });
		walkRight.PushBack({ 192,64,32,64 });
		walkRight.PushBack({ 224,64,32,64 });
		walkRight.speed = 0.2f;
		walkRight.loop = true;

		walkLeft.PushBack({ 0,64,32,64 });
		walkLeft.PushBack({ 32,64,32,64 });
		walkLeft.PushBack({ 64,64,32,64 });
		walkLeft.PushBack({ 96,64,32,64 });
		walkLeft.speed = 0.2f;
		walkLeft.loop = true;

		walkUp.PushBack({ 0,576,32,64 });
		walkUp.PushBack({ 32,576,32,64 });
		walkUp.PushBack({ 64,576,32,64 });
		walkUp.PushBack({ 96,576,32,64 });
		walkUp.speed = 0.2f;
		walkUp.loop = true;

		walkDown.PushBack({ 256,64,32,64 });
		walkDown.PushBack({ 288,64,32,64 });
		walkDown.PushBack({ 320,64,32,64 });
		walkDown.PushBack({ 352,64,32,64 });
		walkDown.speed = 0.2f;
		walkDown.loop = true;

		attackRight.PushBack({ 512,64,32,64 });
		attackRight.PushBack({ 544,64,32,64 });
		attackRight.PushBack({ 576,64,32,64 });
		attackRight.PushBack({ 608,64,32,64 });
		attackRight.speed = 0.4;
		attackRight.loop = false;

		attackLeft.PushBack({ 384,64,32,64 });
		attackLeft.PushBack({ 416,64,32,64 });
		attackLeft.PushBack({ 448,64,32,64 });
		attackLeft.PushBack({ 480,64,32,64 });
		attackLeft.speed = 0.4;
		attackLeft.loop = false;

		attackUp.PushBack({ 128,576,32,64 });
		attackUp.PushBack({ 160,576,32,64 });
		attackUp.PushBack({ 192,576,32,64 });
		attackUp.PushBack({ 224,576,32,64 });
		attackUp.speed = 0.4;
		attackUp.loop = false;

		attackDown.PushBack({ 640,64,32,64 });
		attackDown.PushBack({ 672,64,32,64 });
		attackDown.PushBack({ 704,64,32,64 });
		attackDown.PushBack({ 736,64,32,64 });
		attackDown.speed = 0.4;
		attackDown.loop = false;
		attackDown.pingpong = false;
#pragma endregion
		break;
	case 4:
#pragma region case4
		walkRight.PushBack({ 128,128,32,64 });
		walkRight.PushBack({ 160,128,32,64 });
		walkRight.PushBack({ 192,128,32,64 });
		walkRight.PushBack({ 224,128,32,64 });
		walkRight.speed = 0.2f;
		walkRight.loop = true;

		walkLeft.PushBack({ 0,128,32,64 });
		walkLeft.PushBack({ 32,128,32,64 });
		walkLeft.PushBack({ 64,128,32,64 });
		walkLeft.PushBack({ 96,128,32,64 });
		walkLeft.speed = 0.2f;
		walkLeft.loop = true;

		walkUp.PushBack({ 0,576,32,64 });
		walkUp.PushBack({ 32,576,32,64 });
		walkUp.PushBack({ 64,576,32,64 });
		walkUp.PushBack({ 96,576,32,64 });
		walkUp.speed = 0.2f;
		walkUp.loop = true;

		walkDown.PushBack({ 256,128,32,64 });
		walkDown.PushBack({ 288,128,32,64 });
		walkDown.PushBack({ 320,128,32,64 });
		walkDown.PushBack({ 352,128,32,64 });
		walkDown.speed = 0.2f;
		walkDown.loop = true;

		attackRight.PushBack({ 512,128,32,64 });
		attackRight.PushBack({ 544,128,32,64 });
		attackRight.PushBack({ 576,128,32,64 });
		attackRight.PushBack({ 608,128,32,64 });
		attackRight.speed = 0.4;
		attackRight.loop = false;

		attackLeft.PushBack({ 384,128,32,64 });
		attackLeft.PushBack({ 416,128,32,64 });
		attackLeft.PushBack({ 448,128,32,64 });
		attackLeft.PushBack({ 480,128,32,64 });
		attackLeft.speed = 0.4;
		attackLeft.loop = false;

		attackUp.PushBack({ 128,576,32,64 });
		attackUp.PushBack({ 160,576,32,64 });
		attackUp.PushBack({ 192,576,32,64 });
		attackUp.PushBack({ 224,576,32,64 });
		attackUp.speed = 0.4;
		attackUp.loop = false;

		attackDown.PushBack({ 640,128,32,64 });
		attackDown.PushBack({ 672,128,32,64 });
		attackDown.PushBack({ 704,128,32,64 });
		attackDown.PushBack({ 736,128,32,64 });
		attackDown.speed = 0.4;
		attackDown.loop = false;
		attackDown.pingpong = false;
#pragma endregion
		break;
	case 5:
#pragma region case5
		walkRight.PushBack({ 128,192,32,64 });
		walkRight.PushBack({ 160,192,32,64 });
		walkRight.PushBack({ 192,192,32,64 });
		walkRight.PushBack({ 224,192,32,64 });
		walkRight.speed = 0.2f;
		walkRight.loop = true;

		walkLeft.PushBack({ 0,192,32,64 });
		walkLeft.PushBack({ 32,192,32,64 });
		walkLeft.PushBack({ 64,192,32,64 });
		walkLeft.PushBack({ 96,192,32,64 });
		walkLeft.speed = 0.2f;
		walkLeft.loop = true;

		walkUp.PushBack({ 0,576,32,64 });
		walkUp.PushBack({ 32,576,32,64 });
		walkUp.PushBack({ 64,576,32,64 });
		walkUp.PushBack({ 96,576,32,64 });
		walkUp.speed = 0.2f;
		walkUp.loop = true;

		walkDown.PushBack({ 256,192,32,64 });
		walkDown.PushBack({ 288,192,32,64 });
		walkDown.PushBack({ 320,192,32,64 });
		walkDown.PushBack({ 352,192,32,64 });
		walkDown.speed = 0.2f;
		walkDown.loop = true;

		attackRight.PushBack({ 512,192,32,64 });
		attackRight.PushBack({ 544,192,32,64 });
		attackRight.PushBack({ 576,192,32,64 });
		attackRight.PushBack({ 608,192,32,64 });
		attackRight.speed = 0.4;
		attackRight.loop = false;

		attackLeft.PushBack({ 384,192,32,64 });
		attackLeft.PushBack({ 416,192,32,64 });
		attackLeft.PushBack({ 448,192,32,64 });
		attackLeft.PushBack({ 480,192,32,64 });
		attackLeft.speed = 0.4;
		attackLeft.loop = false;

		attackUp.PushBack({ 128,576,32,64 });
		attackUp.PushBack({ 160,576,32,64 });
		attackUp.PushBack({ 192,576,32,64 });
		attackUp.PushBack({ 224,576,32,64 });
		attackUp.speed = 0.4;
		attackUp.loop = false;

		attackDown.PushBack({ 640,192,32,64 });
		attackDown.PushBack({ 672,192,32,64 });
		attackDown.PushBack({ 704,192,32,64 });
		attackDown.PushBack({ 736,192,32,64 });
		attackDown.speed = 0.4;
		attackDown.loop = false;
		attackDown.pingpong = false;
#pragma endregion
		break;
	case 6:
#pragma region case6
		walkRight.PushBack({ 128,256,32,64 });
		walkRight.PushBack({ 160,256,32,64 });
		walkRight.PushBack({ 192,256,32,64 });
		walkRight.PushBack({ 224,256,32,64 });
		walkRight.speed = 0.2f;
		walkRight.loop = true;

		walkLeft.PushBack({ 0,256,32,64 });
		walkLeft.PushBack({ 32,256,32,64 });
		walkLeft.PushBack({ 64,256,32,64 });
		walkLeft.PushBack({ 96,256,32,64 });
		walkLeft.speed = 0.2f;
		walkLeft.loop = true;

		walkUp.PushBack({ 0,576,32,64 });
		walkUp.PushBack({ 32,576,32,64 });
		walkUp.PushBack({ 64,576,32,64 });
		walkUp.PushBack({ 96,576,32,64 });
		walkUp.speed = 0.2f;
		walkUp.loop = true;

		walkDown.PushBack({ 256,256,32,64 });
		walkDown.PushBack({ 288,256,32,64 });
		walkDown.PushBack({ 320,256,32,64 });
		walkDown.PushBack({ 352,256,32,64 });
		walkDown.speed = 0.2f;
		walkDown.loop = true;

		attackRight.PushBack({ 512,256,32,64 });
		attackRight.PushBack({ 544,256,32,64 });
		attackRight.PushBack({ 576,256,32,64 });
		attackRight.PushBack({ 608,256,32,64 });
		attackRight.speed = 0.4;
		attackRight.loop = false;

		attackLeft.PushBack({ 384,256,32,64 });
		attackLeft.PushBack({ 416,256,32,64 });
		attackLeft.PushBack({ 448,256,32,64 });
		attackLeft.PushBack({ 480,256,32,64 });
		attackLeft.speed = 0.4;
		attackLeft.loop = false;

		attackUp.PushBack({ 128,576,32,64 });
		attackUp.PushBack({ 160,576,32,64 });
		attackUp.PushBack({ 192,576,32,64 });
		attackUp.PushBack({ 224,576,32,64 });
		attackUp.speed = 0.4;
		attackUp.loop = false;

		attackDown.PushBack({ 640,256,32,64 });
		attackDown.PushBack({ 672,256,32,64 });
		attackDown.PushBack({ 704,256,32,64 });
		attackDown.PushBack({ 736,256,32,64 });
		attackDown.speed = 0.4;
		attackDown.loop = false;
		attackDown.pingpong = false;
#pragma endregion
		break;
	case 7:
#pragma region case7
		walkRight.PushBack({ 128,320,32,64 });
		walkRight.PushBack({ 160,320,32,64 });
		walkRight.PushBack({ 192,320,32,64 });
		walkRight.PushBack({ 224,320,32,64 });
		walkRight.speed = 0.2f;
		walkRight.loop = true;

		walkLeft.PushBack({ 0,320,32,64 });
		walkLeft.PushBack({ 32,320,32,64 });
		walkLeft.PushBack({ 64,320,32,64 });
		walkLeft.PushBack({ 96,320,32,64 });
		walkLeft.speed = 0.2f;
		walkLeft.loop = true;

		walkUp.PushBack({ 0,576,32,64 });
		walkUp.PushBack({ 32,576,32,64 });
		walkUp.PushBack({ 64,576,32,64 });
		walkUp.PushBack({ 96,576,32,64 });
		walkUp.speed = 0.2f;
		walkUp.loop = true;

		walkDown.PushBack({ 256,256,32,64 });
		walkDown.PushBack({ 288,256,32,64 });
		walkDown.PushBack({ 320,256,32,64 });
		walkDown.PushBack({ 352,256,32,64 });
		walkDown.speed = 0.2f;
		walkDown.loop = true;

		attackRight.PushBack({ 512,320,32,64 });
		attackRight.PushBack({ 544,320,32,64 });
		attackRight.PushBack({ 576,320,32,64 });
		attackRight.PushBack({ 608,320,32,64 });
		attackRight.speed = 0.4;
		attackRight.loop = false;

		attackLeft.PushBack({ 384,320,32,64 });
		attackLeft.PushBack({ 416,320,32,64 });
		attackLeft.PushBack({ 448,320,32,64 });
		attackLeft.PushBack({ 480,320,32,64 });
		attackLeft.speed = 0.4;
		attackLeft.loop = false;

		attackUp.PushBack({ 128,576,32,64 });
		attackUp.PushBack({ 160,576,32,64 });
		attackUp.PushBack({ 192,576,32,64 });
		attackUp.PushBack({ 224,576,32,64 });
		attackUp.speed = 0.4;
		attackUp.loop = false;

		attackDown.PushBack({ 640,320,32,64 });
		attackDown.PushBack({ 672,320,32,64 });
		attackDown.PushBack({ 704,320,32,64 });
		attackDown.PushBack({ 736,320,32,64 });
		attackDown.speed = 0.4;
		attackDown.loop = false;
		attackDown.pingpong = false;
#pragma endregion
		break;
	case 8:
#pragma region case8
		walkRight.PushBack({ 128,384,32,64 });
		walkRight.PushBack({ 160,384,32,64 });
		walkRight.PushBack({ 192,384,32,64 });
		walkRight.PushBack({ 224,384,32,64 });
		walkRight.speed = 0.2f;
		walkRight.loop = true;

		walkLeft.PushBack({ 0,384,32,64 });
		walkLeft.PushBack({ 32,384,32,64 });
		walkLeft.PushBack({ 64,384,32,64 });
		walkLeft.PushBack({ 96,384,32,64 });
		walkLeft.speed = 0.2f;
		walkLeft.loop = true;

		walkUp.PushBack({ 0,576,32,64 });
		walkUp.PushBack({ 32,576,32,64 });
		walkUp.PushBack({ 64,576,32,64 });
		walkUp.PushBack({ 96,576,32,64 });
		walkUp.speed = 0.2f;
		walkUp.loop = true;

		walkDown.PushBack({ 256,384,32,64 });
		walkDown.PushBack({ 288,384,32,64 });
		walkDown.PushBack({ 320,384,32,64 });
		walkDown.PushBack({ 352,384,32,64 });
		walkDown.speed = 0.2f;
		walkDown.loop = true;

		attackRight.PushBack({ 512,384,32,64 });
		attackRight.PushBack({ 544,384,32,64 });
		attackRight.PushBack({ 576,384,32,64 });
		attackRight.PushBack({ 608,384,32,64 });
		attackRight.speed = 0.4;
		attackRight.loop = false;

		attackLeft.PushBack({ 384,384,32,64 });
		attackLeft.PushBack({ 416,384,32,64 });
		attackLeft.PushBack({ 448,384,32,64 });
		attackLeft.PushBack({ 480,384,32,64 });
		attackLeft.speed = 0.4;
		attackLeft.loop = false;

		attackUp.PushBack({ 128,576,32,64 });
		attackUp.PushBack({ 160,576,32,64 });
		attackUp.PushBack({ 192,576,32,64 });
		attackUp.PushBack({ 224,576,32,64 });
		attackUp.speed = 0.4;
		attackUp.loop = false;

		attackDown.PushBack({ 640,384,32,64 });
		attackDown.PushBack({ 672,384,32,64 });
		attackDown.PushBack({ 704,384,32,64 });
		attackDown.PushBack({ 736,384,32,64 });
		attackDown.speed = 0.4;
		attackDown.loop = false;
		attackDown.pingpong = false;
#pragma endregion
		break;
	case 9:
#pragma region case9
		walkRight.PushBack({ 128,448,32,64 });
		walkRight.PushBack({ 160,448,32,64 });
		walkRight.PushBack({ 192,448,32,64 });
		walkRight.PushBack({ 224,448,32,64 });
		walkRight.speed = 0.2f;
		walkRight.loop = true;

		walkLeft.PushBack({ 0,448,32,64 });
		walkLeft.PushBack({ 32,448,32,64 });
		walkLeft.PushBack({ 64,448,32,64 });
		walkLeft.PushBack({ 96,448,32,64 });
		walkLeft.speed = 0.2f;
		walkLeft.loop = true;

		walkUp.PushBack({ 0,576,32,64 });
		walkUp.PushBack({ 32,576,32,64 });
		walkUp.PushBack({ 64,576,32,64 });
		walkUp.PushBack({ 96,576,32,64 });
		walkUp.speed = 0.2f;
		walkUp.loop = true;

		walkDown.PushBack({ 256,448,32,64 });
		walkDown.PushBack({ 288,448,32,64 });
		walkDown.PushBack({ 320,448,32,64 });
		walkDown.PushBack({ 352,448,32,64 });
		walkDown.speed = 0.2f;
		walkDown.loop = true;

		attackRight.PushBack({ 512,448,32,64 });
		attackRight.PushBack({ 544,448,32,64 });
		attackRight.PushBack({ 576,448,32,64 });
		attackRight.PushBack({ 608,448,32,64 });
		attackRight.speed = 0.4;
		attackRight.loop = false;

		attackLeft.PushBack({ 384,448,32,64 });
		attackLeft.PushBack({ 416,448,32,64 });
		attackLeft.PushBack({ 448,448,32,64 });
		attackLeft.PushBack({ 480,448,32,64 });
		attackLeft.speed = 0.4;
		attackLeft.loop = false;

		attackUp.PushBack({ 128,576,32,64 });
		attackUp.PushBack({ 160,576,32,64 });
		attackUp.PushBack({ 192,576,32,64 });
		attackUp.PushBack({ 224,576,32,64 });
		attackUp.speed = 0.4;
		attackUp.loop = false;

		attackDown.PushBack({ 640,448,32,64 });
		attackDown.PushBack({ 672,448,32,64 });
		attackDown.PushBack({ 704,448,32,64 });
		attackDown.PushBack({ 736,448,32,64 });
		attackDown.speed = 0.4;
		attackDown.loop = false;
		attackDown.pingpong = false;
#pragma endregion
		break;
	case 10:
#pragma region case10
		walkRight.PushBack({ 128,512,32,64 });
		walkRight.PushBack({ 160,512,32,64 });
		walkRight.PushBack({ 192,512,32,64 });
		walkRight.PushBack({ 224,512,32,64 });
		walkRight.speed = 0.2f;
		walkRight.loop = true;

		walkLeft.PushBack({ 0,512,32,64 });
		walkLeft.PushBack({ 32,512,32,64 });
		walkLeft.PushBack({ 64,512,32,64 });
		walkLeft.PushBack({ 96,512,32,64 });
		walkLeft.speed = 0.2f;
		walkLeft.loop = true;

		walkUp.PushBack({ 0,576,32,64 });
		walkUp.PushBack({ 32,576,32,64 });
		walkUp.PushBack({ 64,576,32,64 });
		walkUp.PushBack({ 96,576,32,64 });
		walkUp.speed = 0.2f;
		walkUp.loop = true;

		walkDown.PushBack({ 256,512,32,64 });
		walkDown.PushBack({ 288,512,32,64 });
		walkDown.PushBack({ 320,512,32,64 });
		walkDown.PushBack({ 352,512,32,64 });
		walkDown.speed = 0.2f;
		walkDown.loop = true;

		attackRight.PushBack({ 512,512,32,64 });
		attackRight.PushBack({ 544,512,32,64 });
		attackRight.PushBack({ 576,512,32,64 });
		attackRight.PushBack({ 608,512,32,64 });
		attackRight.speed = 0.4;
		attackRight.loop = false;

		attackLeft.PushBack({ 384,512,32,64 });
		attackLeft.PushBack({ 416,512,32,64 });
		attackLeft.PushBack({ 448,512,32,64 });
		attackLeft.PushBack({ 480,512,32,64 });
		attackLeft.speed = 0.4;
		attackLeft.loop = false;

		attackUp.PushBack({ 128,576,32,64 });
		attackUp.PushBack({ 160,576,32,64 });
		attackUp.PushBack({ 192,576,32,64 });
		attackUp.PushBack({ 224,576,32,64 });
		attackUp.speed = 0.4;
		attackUp.loop = false;

		attackDown.PushBack({ 640,512,32,64 });
		attackDown.PushBack({ 672,512,32,64 });
		attackDown.PushBack({ 704,512,32,64 });
		attackDown.PushBack({ 736,512,32,64 });
		attackDown.speed = 0.4;
		attackDown.loop = false;
		attackDown.pingpong = false;
#pragma endregion
		break;
	default:
#pragma region default
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
		break;
#pragma endregion
	}

	currentAnim = &walkRight;

	path.PushBack({0.0f,0.0f}, 4, currentAnim);
}

void Enemy_BaseCard::deathAnimation() {
	if (healthPoints <= 0) {
		App->audio->PlayFx(dieFx);
		App->particles->AddParticle(App->particles->cardDeath, position.x, position.y);

		App->player->lifePlayer++;

		SetToDelete();
	}
}