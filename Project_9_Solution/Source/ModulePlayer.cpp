#include "ModulePlayer.h"
#include "Application.h"
#include "Particle.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"

#include <stdio.h>
#include <time.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 66, 1, 32, 14 });

	// move upwards
	upAnim.PushBack({ 100, 1, 32, 14 });
	upAnim.PushBack({ 132, 0, 32, 14 });
	upAnim.loop = false;
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 33, 1, 32, 14 });
	downAnim.PushBack({ 0, 1, 32, 14 });
	downAnim.loop = false;
	downAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	//texture = App->textures->Load("Assets/Sprites/ship.png");
	currentAnimation = &idleAnim;

	//laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 150;
	position.y = 120;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 16, 16 }, Collider::Type::PLAYER, this);

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	Font = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	return ret;
}

Update_Status ModulePlayer::Update()
{
	if (stateHability) {
		if (rollTheDice == false) {
			srand(time(NULL));

			hability *= 1 + rand() % ((lifePlayer + 1) - 1);

			rollTheDice = true;
		}

		habilityDelay--;
		
		if (habilityDelay <= 0) {
			Particle* newParticle = App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT_BREAKER);
			newParticle->collider->AddListener(this);
			App->audio->PlayFx(laserFx);

			//End hability secuence, take one life, reset deffault damage, reset deffault Roll the dice, reset deffault delay
			stateHability = false;
			lifePlayer--;
			hability = 50;
			rollTheDice = false;
			habilityDelay = 100;
		}
	}
	else if (!destroyed) {
#pragma region WASD

		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
		{
			position.x -= speed;
		}

		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
		{
			position.x += speed;
		}

		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
		{
			position.y += speed;
			if (currentAnimation != &downAnim)
			{
				downAnim.Reset();
				currentAnimation = &downAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
		{
			position.y -= speed;
			if (currentAnimation != &upAnim)
			{
				upAnim.Reset();
				currentAnimation = &upAnim;
			}
		}
#pragma endregion

		if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
		{
			direction = 0;
			App->particles->laser.speed.x = 0;
			App->particles->laser.speed.y = 5;
		}

		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
		{
			direction = 1;
			App->particles->laser.speed.x = 5;
			App->particles->laser.speed.y = 0;
		}

		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
		{
			direction = 2;
			App->particles->laser.speed.x = 0;
			App->particles->laser.speed.y = -5;

			if (currentAnimation != &downAnim)
			{
				downAnim.Reset();
				currentAnimation = &downAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
		{
			direction = 3;
			App->particles->laser.speed.x = -5;
			App->particles->laser.speed.y = 0;

			if (currentAnimation != &upAnim)
			{
				upAnim.Reset();
				currentAnimation = &upAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
		{
			Particle* newParticle = App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			newParticle->collider->AddListener(this);
			App->audio->PlayFx(laserFx);
		}

		if (App->input->keys[SDL_SCANCODE_E] == Key_State::KEY_DOWN) {
			stateHability = true;
		}

		// If no up/down movement detected, set the current animation back to idle
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE)
			currentAnimation = &idleAnim;

	}

	if (App->input->keys[SDL_SCANCODE_Q] == Key_State::KEY_DOWN)
	{
		lifePlayer++;
	}
  
  if (lifePlayer <= 0 && !destroyed) {
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneMenu, 60);

		destroyed = true;
	}

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	// Draw UI (life) --------------------------------------
	sprintf_s(Text, 10, "%7d", lifePlayer);

    //Blit the text of the life in at the bottom of the screen
	App->fonts->BlitText(58, 248, Font, Text);

	sprintf_s(Text, 10, "%7d", hability);
	App->fonts->BlitText(58, 228, Font, Text);
	

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY_SHOT && destroyed == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);

		lifePlayer--;
	}

	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		lifePlayer++;
	}
}