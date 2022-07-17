#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
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

	// Explosion particle
	diceAbility.anim.PushBack({ 192, 0, 64, 32 });
	diceAbility.anim.PushBack({ 192, 32, 64, 32 });
	diceAbility.anim.loop = true;
	diceAbility.speed.x = 5;
	diceAbility.anim.speed = 0.1f;
	diceAbility.lifetime = 180;
	diceAbility.isShot = true;

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
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
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
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
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