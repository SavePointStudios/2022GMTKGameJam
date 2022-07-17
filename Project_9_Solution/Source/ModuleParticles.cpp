#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{
}
bool ModuleParticles::Start()
{
	LOG("Loading particles");

	baseCardTexture = App->textures->Load("Assets/Sprites/Card_Clubs_Sheet.png");
	handTexture = App->textures->Load("Assets/Sprites/Hand_Character_Spritesheet.png");
	QK_Sword = App->textures->Load("Assets/Sprites/midboss_Attack");

	// Explosion particle
	diceAbilityRight.anim.PushBack({ 192, 0, 64, 32 });
	diceAbilityRight.anim.PushBack({ 192, 32, 64, 32 });
	diceAbilityRight.anim.loop = true;
	diceAbilityRight.speed.x = -5;
	diceAbilityRight.speed.y = 0;
	diceAbilityRight.anim.speed = 0.1f;
	diceAbilityRight.lifetime = 180;
	diceAbilityRight.isShot = true;

	diceAbilityLeft.anim.PushBack({ 256, 0, 64, 32 });
	diceAbilityLeft.anim.PushBack({ 256, 32, 64, 32 });
	diceAbilityLeft.anim.loop = true;
	diceAbilityLeft.speed.x = 5;
	diceAbilityLeft.speed.y = 0;
	diceAbilityLeft.anim.speed = 0.1f;
	diceAbilityLeft.lifetime = 180;
	diceAbilityLeft.isShot = true;

	diceAbilityDown.anim.PushBack({ 320, 0, 32, 64 });
	diceAbilityDown.anim.PushBack({ 352, 0, 32, 64 });
	diceAbilityDown.anim.loop = true;
	diceAbilityDown.speed.x = 0;
	diceAbilityDown.speed.y = -5;
	diceAbilityDown.anim.speed = 0.1f;
	diceAbilityDown.lifetime = 180;
	diceAbilityDown.isShot = true;

	diceAbilityUp.anim.PushBack({ 384, 0, 32, 64 });
	diceAbilityUp.anim.PushBack({ 416, 0, 32, 64 });
	diceAbilityUp.anim.loop = true;
	diceAbilityUp.speed.x = 0;
	diceAbilityUp.speed.y = 5;
	diceAbilityUp.anim.speed = 0.1f;
	diceAbilityUp.lifetime = 180;
	diceAbilityUp.isShot = true;

	diceBasicAttack.anim.PushBack({ 225, 65, 13, 13 });
	diceBasicAttack.speed.x = 5;
	diceBasicAttack.lifetime = 180;
	diceBasicAttack.isShot = true;

	cardAttackMelee.anim.PushBack({ 768, 576, 32, 64 });
	cardAttackMelee.lifetime = 10;

	cardDeath.anim.PushBack({ 768, 0, 32, 64 });
	cardDeath.anim.PushBack({ 800, 0, 32, 64 });
	cardDeath.anim.PushBack({ 832, 0, 32, 64 });
	cardDeath.anim.PushBack({ 864, 0, 32, 64 });
	cardDeath.lifetime = 70;
	cardDeath.anim.speed = 0.2;
	cardDeath.anim.loop = false;
	cardDeath.isBaseCard = true;

	QK_SwordAttack.anim.PushBack({ 0, 0, 21, 9 });
	QK_SwordAttack.speed.x = 5;
	QK_SwordAttack.lifetime = 180;
	QK_SwordAttack.isQK_Shot = true;

	deathAnimBoss.anim.PushBack({ 0,96,64,96 });
	deathAnimBoss.anim.PushBack({ 64,96,64,96 });
	deathAnimBoss.anim.PushBack({ 128,96,64,96 });
	deathAnimBoss.anim.PushBack({ 192,96,64,96 });
	deathAnimBoss.anim.PushBack({ 256,96,64,96 });
	deathAnimBoss.anim.PushBack({ 320,96,64,96 });
	deathAnimBoss.anim.PushBack({ 384,96,64,96 });
	deathAnimBoss.anim.PushBack({ 448,96,64,96 });
	deathAnimBoss.anim.PushBack({ 512,96,64,96 });
	deathAnimBoss.anim.PushBack({ 576,96,64,96 });
	deathAnimBoss.anim.speed = 0.2f;
	deathAnimBoss.lifetime = 70;
	deathAnimBoss.anim.loop = false;
	deathAnimBoss.isBoss = true;

	return true;
}

Update_Status ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}
	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}
	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}
	}
}

Update_Status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];
		if (particle != nullptr && particle->isAlive)
		{
			//App->render->Blit(baseCardTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			if (particle->isShot)
				App->render->Blit(handTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));

			else if (particle->isBaseCard)
				App->render->Blit(baseCardTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));

			else if (particle->isQK_Shot)
				App->render->Blit(QK_Sword, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;
			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);
			particles[i] = newParticle;
			break;
		}
	}
	return newParticle;
}