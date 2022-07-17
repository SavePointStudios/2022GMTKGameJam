#include "Enemy_Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL.h"

#include "ModuleFonts.h"
#include <string>
using namespace std;

Enemy_Boss::Enemy_Boss(int x, int y) : Enemy(x, y)
{
	initAnimations();

	collider = App->collisions->AddCollider({ 0, 0, 64, 96 }, Collider::Type::BOSS, (Module*)App->enemies);

	// Sound effect loading
	idleFx = App->audio->LoadFx("Assets/Fx/Final boss/Wind.wav"); // Played always when boss is alive
	idleFx = App->audio->LoadFx("Assets/Fx/Final boss/Attack.wav"); // Played when boss attacks
}

void Enemy_Boss::Update()
{
	updateMovement();

	//currentAnim = &idleAnim;
	//App->fonts->BlitText(10, 70, 0, std::to_string(spinAnim.currentFrame).c_str());

	if (spinAnim.currentFrame > 4.0f)
		currentAnim = &idleAnim;

	if (!attacking)
		startAttack();
	else
		attack();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_Boss::updateMovement()
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

void Enemy_Boss::startAttack()
{
	startTimer = SDL_GetTicks();
	attacking = true;
	spinAnim.Reset();
}

void Enemy_Boss::attack()
{
	currentTime = SDL_GetTicks();

	if (currentTime - startTimer >= 2000)
	{
		//spinAnim.Reset();
		App->particles->AddParticle(App->particles->bossAttackUp, position.x, position.y + 32, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->bossAttackDown, position.x, position.y + 32, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->bossAttackLeft, position.x, position.y + 32, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->bossAttackRight, position.x, position.y + 32, Collider::Type::ENEMY_SHOT);
		currentAnim = &spinAnim;
		attacking = false;
	}
}

void Enemy_Boss::deathAnimation() {

}

void Enemy_Boss::initAnimations()
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
	spinAnim.loop = false;

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
}