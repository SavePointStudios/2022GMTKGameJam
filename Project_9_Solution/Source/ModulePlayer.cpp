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
	// idle animation right
	idleAnimRight.PushBack({ 0, 0, 32, 32 });
	idleAnimRight.PushBack({ 33, 0, 32, 32 });
	idleAnimRight.PushBack({ 65, 0, 32, 32 });
	idleAnimRight.loop = true;
	idleAnimRight.speed = 0.1f;

	// idle animation left
	idleAnimLeft.PushBack({ 0, 33, 32, 32 });
	idleAnimLeft.PushBack({ 33, 33, 32, 32 });
	idleAnimLeft.PushBack({ 65, 33, 32, 32 });
	idleAnimLeft.loop = true;
	idleAnimLeft.speed = 0.1f;

	// idle animation down
	idleAnimDown.PushBack({ 0, 65, 32, 32 });
	idleAnimDown.PushBack({ 33, 65, 32, 32 });
	idleAnimDown.PushBack({ 65, 65, 32, 32 });
	idleAnimDown.loop = true;
	idleAnimDown.speed = 0.1f;

	// idle animation up
	idleAnimUp.PushBack({ 0, 97, 32, 32 });
	idleAnimUp.PushBack({ 33, 97, 32, 32 });
	idleAnimUp.PushBack({ 65, 97, 32, 32 });
	idleAnimUp.loop = true;
	idleAnimUp.speed = 0.1f;

	// Move right
	rightAnim.PushBack({ 0,  128, 32, 32 });
	rightAnim.PushBack({ 32, 128, 32, 32 });
	rightAnim.PushBack({ 64, 128, 32, 32 });
	rightAnim.PushBack({ 96, 128, 32, 32 });
	rightAnim.PushBack({ 128, 128, 32, 32 });
	rightAnim.PushBack({ 160, 128, 32, 32 });
	rightAnim.loop = true;
	rightAnim.speed = 0.2f;

	// Move left
	leftAnim.PushBack({ 0, 160, 32, 32 });
	leftAnim.PushBack({ 32, 160, 32, 32 });
	leftAnim.PushBack({ 64, 160, 32, 32 });
	leftAnim.PushBack({ 96, 160, 32, 32 });
	leftAnim.PushBack({ 128, 160, 32, 32 });
	leftAnim.PushBack({ 160, 160, 32, 32 });
	leftAnim.loop = true;
	leftAnim.speed = 0.2f;

	// Move down
	downAnim.PushBack({ 0, 192, 32, 32 });
	downAnim.PushBack({ 32, 192, 32, 32 });
	downAnim.PushBack({ 64, 192, 32, 32 });
	downAnim.PushBack({ 96, 192, 32, 32 });
	downAnim.PushBack({ 128, 192, 32, 32 });
	downAnim.PushBack({ 160, 192, 32, 32 });
	downAnim.loop = true;
	downAnim.speed = 0.2f;

	// move upwards
	upAnim.PushBack({ 0, 224, 32, 32 });
	upAnim.PushBack({ 32, 224, 32, 32 });
	upAnim.PushBack({ 64, 224, 32, 32 });
	upAnim.PushBack({ 96, 224, 32, 32 });
	upAnim.PushBack({ 128, 224, 32, 32 });
	upAnim.PushBack({ 160, 224, 32, 32 });
	upAnim.loop = true;
	upAnim.speed = 0.2f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	diceTexture = App->textures->Load("Assets/Sprites/Dice_Character_Spritesheet.png");
	currentAnimation = &idleAnimRight;

	//laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 150;
	position.y = 120;

	destroyed = false;

	lifePlayer = 1;
	direction = 3;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 32 }, Collider::Type::PLAYER, this);

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	Font = App->fonts->Load("Assets/Fonts/casino_font_black.png", lookupTable, 1);

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

			switch (direction)
			{
			case 0:
				currentAnimation = &upAnim;
				break;
			case 1:
				currentAnimation = &leftAnim;
				break;
			case 2:
				currentAnimation = &downAnim;
				break;
			case 3:
				currentAnimation = &rightAnim;
				break;
			default:
				break;
			}
		}

		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
		{
			position.x += speed;

			switch (direction)
			{
			case 0:
				currentAnimation = &upAnim;
				break;
			case 1:
				currentAnimation = &leftAnim;
				break;
			case 2:
				currentAnimation = &downAnim;
				break;
			case 3:
				currentAnimation = &rightAnim;
				break;
			default:
				break;
			}
		}

		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
		{
			position.y += speed;

			switch (direction)
			{
			case 0:
				currentAnimation = &upAnim;
				break;
			case 1:
				currentAnimation = &leftAnim;
				break;
			case 2:
				currentAnimation = &downAnim;
				break;
			case 3:
				currentAnimation = &rightAnim;
				break;
			default:
				break;
			}
		}

		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
		{
			position.y -= speed;

			switch (direction)
			{
			case 0:
				currentAnimation = &upAnim;
				break;
			case 1:
				currentAnimation = &leftAnim;
				break;
			case 2:
				currentAnimation = &downAnim;
				break;
			case 3:
				currentAnimation = &rightAnim;
				break;
			default:
				break;
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
		}

		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
		{
			direction = 3;
			App->particles->laser.speed.x = -5;
			App->particles->laser.speed.y = 0;
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
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE) {
			switch (direction)
			{
			case 0:
				currentAnimation = &idleAnimUp;
				break;
			case 1:
				currentAnimation = &idleAnimLeft;
				break;
			case 2:
				currentAnimation = &idleAnimDown;
				break;
			case 3:
				currentAnimation = &idleAnimRight;
				break;
			default:
				break;
			}
		}

	}

	if (App->input->keys[SDL_SCANCODE_Q] == Key_State::KEY_DOWN)
	{
		lifePlayer++;
		if (lifePlayer > 6) { lifePlayer = 6; }
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
		App->render->Blit(diceTexture, position.x, position.y, &rect);
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

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::UP_WALL)
	{
		position.y += speed;
	}
	else if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::DOWN_WALL)
	{
		position.y -= speed;
	}
	else if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::RIGHT_WALL)
	{
		position.x -= speed;
	}
	else if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::LEFT_WALL)
	{
		position.x += speed;
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