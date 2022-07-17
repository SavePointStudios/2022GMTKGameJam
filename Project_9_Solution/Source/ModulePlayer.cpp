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
#include "ModuleUI.h"

#include <stdio.h>
#include <time.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation right
	idleAnimRight.PushBack({ 0, 0, 32, 32 });
	idleAnimRight.PushBack({ 32, 0, 32, 32 });
	idleAnimRight.PushBack({ 64, 0, 32, 32 });
	idleAnimRight.loop = true;
	idleAnimRight.speed = 0.1f;

	// idle animation left
	idleAnimLeft.PushBack({ 0, 32, 32, 32 });
	idleAnimLeft.PushBack({ 32, 32, 32, 32 });
	idleAnimLeft.PushBack({ 64, 32, 32, 32 });
	idleAnimLeft.loop = true;
	idleAnimLeft.speed = 0.1f;

	// idle animation down
	idleAnimDown.PushBack({ 0, 64, 32, 32 });
	idleAnimDown.PushBack({ 32, 64, 32, 32 });
	idleAnimDown.PushBack({ 64, 64, 32, 32 });
	idleAnimDown.loop = true;
	idleAnimDown.speed = 0.1f;

	// idle animation up
	idleAnimUp.PushBack({ 0, 96, 32, 32 });
	idleAnimUp.PushBack({ 32, 96, 32, 32 });
	idleAnimUp.PushBack({ 64, 96, 32, 32 });
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

	// Move upwards
	upAnim.PushBack({ 0, 224, 32, 32 });
	upAnim.PushBack({ 32, 224, 32, 32 });
	upAnim.PushBack({ 64, 224, 32, 32 });
	upAnim.PushBack({ 96, 224, 32, 32 });
	upAnim.PushBack({ 128, 224, 32, 32 });
	upAnim.PushBack({ 160, 224, 32, 32 });
	upAnim.loop = true;
	upAnim.speed = 0.2f;

	// right special
	specialRightAnim.PushBack({ 128, 0, 32, 32 });
	specialRightAnim.PushBack({ 128, 0, 32, 32 });
	specialRightAnim.PushBack({ 128, 0, 32, 32 });
	specialRightAnim.PushBack({ 160, 0, 32, 32 });
	specialRightAnim.PushBack({ 192, 0, 32, 32 });
	specialRightAnim.PushBack({ 192, 0, 32, 32 });
	specialRightAnim.loop = false;
	specialRightAnim.speed = 0.1f;

	// left special
	specialLeftAnim.PushBack({ 128, 32, 32, 32 });
	specialLeftAnim.PushBack({ 128, 32, 32, 32 });
	specialLeftAnim.PushBack({ 128, 32, 32, 32 });
	specialLeftAnim.PushBack({ 160, 32, 32, 32 });
	specialLeftAnim.PushBack({ 192, 32, 32, 32 });
	specialLeftAnim.PushBack({ 192, 32, 32, 32 });
	specialLeftAnim.loop = false;
	specialLeftAnim.speed = 0.1f;

	// down special
	specialDownAnim.PushBack({ 128, 64, 32, 32 });
	specialDownAnim.PushBack({ 128, 64, 32, 32 });
	specialDownAnim.PushBack({ 128, 64, 32, 32 });
	specialDownAnim.PushBack({ 160, 64, 32, 32 });
	specialDownAnim.PushBack({ 192, 64, 32, 32 });
	specialDownAnim.PushBack({ 192, 64, 32, 32 });
	specialDownAnim.loop = false;
	specialDownAnim.speed = 0.1f;

	// up special
	specialUpAnim.PushBack({ 128, 96, 32, 32 });
	specialUpAnim.PushBack({ 128, 96, 32, 32 });
	specialUpAnim.PushBack({ 128, 96, 32, 32 });
	specialUpAnim.PushBack({ 160, 96, 32, 32 });
	specialUpAnim.PushBack({ 192, 96, 32, 32 });
	specialUpAnim.PushBack({ 192, 96, 32, 32 });
	specialUpAnim.loop = false;
	specialUpAnim.speed = 0.1f;


	// idle hand right
	idleHandAnimRight.PushBack({ 0, 0, 32, 32 });
	idleHandAnimRight.PushBack({ 0, 0, 32, 32 });
	idleHandAnimRight.PushBack({ 160, 0, 32, 32 });
	idleHandAnimRight.PushBack({ 32, 0, 32, 32 });
	idleHandAnimRight.PushBack({ 64, 0, 32, 32 });
	idleHandAnimRight.PushBack({ 96, 0, 32, 32 });
	idleHandAnimRight.PushBack({ 128, 0, 32, 32 });
	idleHandAnimRight.PushBack({ 96, 0, 32, 32 });
	idleHandAnimRight.PushBack({ 64, 0, 32, 32 });
	idleHandAnimRight.PushBack({ 32, 0, 32, 32 });
	idleHandAnimRight.PushBack({ 160, 0, 32, 32 });
	idleHandAnimRight.loop = true;
	idleHandAnimRight.speed = 0.1f;

	// idle hand left
	idleHandAnimLeft.PushBack({ 0,   32, 32, 32 });
	idleHandAnimLeft.PushBack({ 0,   32, 32, 32 });
	idleHandAnimLeft.PushBack({ 160, 32, 32, 32 });
	idleHandAnimLeft.PushBack({ 32,  32, 32, 32 });
	idleHandAnimLeft.PushBack({ 64,  32, 32, 32 });
	idleHandAnimLeft.PushBack({ 96,  32, 32, 32 });
	idleHandAnimLeft.PushBack({ 128, 32, 32, 32 });
	idleHandAnimLeft.PushBack({ 96,  32, 32, 32 });
	idleHandAnimLeft.PushBack({ 64,  32, 32, 32 });
	idleHandAnimLeft.PushBack({ 32,  32, 32, 32 });
	idleHandAnimLeft.PushBack({ 160, 32, 32, 32 });
	idleHandAnimLeft.loop = true;
	idleHandAnimLeft.speed = 0.1f;

	// idle hand down
	idleHandAnimDown.PushBack({ 0, 0, 32, 32 });
	idleHandAnimDown.PushBack({ 0, 0, 32, 32 });
	idleHandAnimDown.PushBack({ 160, 0, 32, 32 });
	idleHandAnimDown.PushBack({ 32, 0, 32, 32 });
	idleHandAnimDown.PushBack({ 64, 0, 32, 32 });
	idleHandAnimDown.PushBack({ 96, 0, 32, 32 });
	idleHandAnimDown.PushBack({ 128, 0, 32, 32 });
	idleHandAnimDown.PushBack({ 96, 0, 32, 32 });
	idleHandAnimDown.PushBack({ 64, 0, 32, 32 });
	idleHandAnimDown.PushBack({ 32, 0, 32, 32 });
	idleHandAnimDown.PushBack({ 160, 0, 32, 32 });
	idleHandAnimDown.loop = true;
	idleHandAnimDown.speed = 0.1f;

	// idle hand up
	idleHandAnimUp.PushBack({ 0,   32, 32, 32 });
	idleHandAnimUp.PushBack({ 0,   32, 32, 32 });
	idleHandAnimUp.PushBack({ 160, 32, 32, 32 });
	idleHandAnimUp.PushBack({ 32,  32, 32, 32 });
	idleHandAnimUp.PushBack({ 64,  32, 32, 32 });
	idleHandAnimUp.PushBack({ 96,  32, 32, 32 });
	idleHandAnimUp.PushBack({ 128, 32, 32, 32 });
	idleHandAnimUp.PushBack({ 96,  32, 32, 32 });
	idleHandAnimUp.PushBack({ 64,  32, 32, 32 });
	idleHandAnimUp.PushBack({ 32,  32, 32, 32 });
	idleHandAnimUp.PushBack({ 160, 32, 32, 32 });
	idleHandAnimUp.loop = true;
	idleHandAnimUp.speed = 0.1f;

	// attack hand right
	handRightAttackAnim.PushBack({ 0, 64, 32, 32 });
	handRightAttackAnim.PushBack({ 32, 64, 32, 32 });
	handRightAttackAnim.PushBack({ 64, 64, 32, 32 });
	handRightAttackAnim.PushBack({ 96, 64, 32, 32 });
	handRightAttackAnim.loop = false;
	handRightAttackAnim.speed = 0.1f;

	// attack hand left
	handLeftAttackAnim.PushBack({ 0, 96, 32, 32 });
	handLeftAttackAnim.PushBack({ 32, 96, 32, 32 });
	handLeftAttackAnim.PushBack({ 64, 96, 32, 32 });
	handLeftAttackAnim.PushBack({ 96, 96, 32, 32 });
	handLeftAttackAnim.loop = false;
	handLeftAttackAnim.speed = 0.1f;

	// attack hand down
	handDownAttackAnim.PushBack({ 0, 128, 32, 32 });
	handDownAttackAnim.PushBack({ 32, 128, 32, 32 });
	handDownAttackAnim.PushBack({ 64, 128, 32, 32 });
	handDownAttackAnim.PushBack({ 96, 128, 32, 32 });
	handDownAttackAnim.loop = false;
	handDownAttackAnim.speed = 0.1f;

	// attack hand up
	handUpAttackAnim.PushBack({ 0, 160, 32, 32 });
	handUpAttackAnim.PushBack({ 32, 160, 32, 32 });
	handUpAttackAnim.PushBack({ 64, 160, 32, 32 });
	handUpAttackAnim.PushBack({ 96, 160, 32, 32 });
	handUpAttackAnim.loop = false;
	handUpAttackAnim.speed = 0.1f;

	// special hand right
	handRightSpecialAnim.PushBack({ 128, 64, 32, 64 });
	handRightSpecialAnim.PushBack({ 128, 64, 32, 64 });
	handRightSpecialAnim.PushBack({ 128, 64, 32, 64 });
	handRightSpecialAnim.PushBack({ 160, 64, 32, 64 });
	handRightSpecialAnim.PushBack({ 192, 64, 32, 64 });
	handRightSpecialAnim.PushBack({ 192, 64, 32, 64 });
	handRightSpecialAnim.loop = false;
	handRightSpecialAnim.speed = 0.1f;

	// special hand left
	handLeftSpecialAnim.PushBack({ 128, 128, 32, 64 });
	handLeftSpecialAnim.PushBack({ 128, 128, 32, 64 });
	handLeftSpecialAnim.PushBack({ 128, 128, 32, 64 });
	handLeftSpecialAnim.PushBack({ 160, 128, 32, 64 });
	handLeftSpecialAnim.PushBack({ 192, 128, 32, 64 });
	handLeftSpecialAnim.PushBack({ 192, 128, 32, 64 });
	handLeftSpecialAnim.loop = false;
	handLeftSpecialAnim.speed = 0.1f;

	// special hand down
	handDownSpecialAnim.PushBack({ 0, 192, 32, 64 });
	handDownSpecialAnim.PushBack({ 0, 192, 32, 64 });
	handDownSpecialAnim.PushBack({ 0, 192, 32, 64 });
	handDownSpecialAnim.PushBack({ 32, 192, 32, 64 });
	handDownSpecialAnim.PushBack({ 64, 192, 32, 64 });
	handDownSpecialAnim.PushBack({ 64, 192, 32, 64 });
	handDownSpecialAnim.loop = false;
	handDownSpecialAnim.speed = 0.1f;

	// special hand up
	handUpSpecialAnim.PushBack({ 96, 192, 32, 64 });
	handUpSpecialAnim.PushBack({ 96, 192, 32, 64 });
	handUpSpecialAnim.PushBack({ 96, 192, 32, 64 });
	handUpSpecialAnim.PushBack({ 128, 192, 32, 64 });
	handUpSpecialAnim.PushBack({ 160, 192, 32, 64 });
	handUpSpecialAnim.PushBack({ 160, 192, 32, 64 });
	handUpSpecialAnim.loop = false;
	handUpSpecialAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	diceTexture = App->textures->Load("Assets/Sprites/Dice_Character_Spritesheet.png");
	currentDiceAnimation = &idleAnimRight;

	diceHandTexture = App->textures->Load("Assets/Sprites/Hand_Character_Spritesheet.png");
	currentDiceHandAnimation = &idleHandAnimRight;


	shootFx = App->audio->LoadFx("Assets/Fx/Dice/Shoot.wav"); // Played when player shoots
	dieFx = App->audio->LoadFx("Assets/Fx/Dice/Die.wav"); // Played when player dies
	hitFx = App->audio->LoadFx("Assets/Fx/Dice/Hit.wav"); // Played when player is hit
	specialLoadFx = App->audio->LoadFx("Assets/Fx/Dice/Special Loading.wav"); // Played while loading the special (dice rolling for multiplier)

	position.x = 150;
	position.y = 120;

	destroyed = false;

	lifePlayer = 1;
	direction = 3;

	App->particles->diceBasicAttack.speed.x = -5;
	App->particles->diceBasicAttack.speed.y = 0;

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

			switch (hability/50)
			{
			case 1:
				App->ui->oneRollAnim.Reset();
				App->ui->currentRollAnimation = &App->ui->oneRollAnim;
				break;
			case 2:
				App->ui->twoRollAnim.Reset();
				App->ui->currentRollAnimation = &App->ui->twoRollAnim;
				break;
			case 3:
				App->ui->threeRollAnim.Reset();
				App->ui->currentRollAnimation = &App->ui->threeRollAnim;
				break;
			case 4:
				App->ui->fourRollAnim.Reset();
				App->ui->currentRollAnimation = &App->ui->fourRollAnim;
				break;
			case 5:
				App->ui->fiveRollAnim.Reset();
				App->ui->currentRollAnimation = &App->ui->fiveRollAnim;
				break;
			case 6:
				App->ui->sixRollAnim.Reset();
				App->ui->currentRollAnimation = &App->ui->sixRollAnim;
				break;
			default:
				break;
			}

			rollTheDice = true;
		}

		habilityDelay--;

		if (habilityDelay == 40) {
			switch (direction)
			{
			case 0:
				specialUpAnim.Reset();
				currentDiceAnimation = &specialUpAnim;
				break;
			case 1:
				specialLeftAnim.Reset();
				currentDiceAnimation = &specialLeftAnim;
				break;
			case 2:
				specialDownAnim.Reset();
				currentDiceAnimation = &specialDownAnim;
				break;
			case 3:
				specialRightAnim.Reset();
				currentDiceAnimation = &specialRightAnim;
				break;
			default:
				break;
			}
		}

		if (habilityDelay == 0) {
			iPoint shotSpawn = position;
			Particle* newParticle;
			switch (direction)
			{
			case 0:
				shotSpawn.y -= 64;
				shotSpawn.x += 0;

				newParticle = App->particles->AddParticle(App->particles->diceAbilityUp, shotSpawn.x, shotSpawn.y, Collider::Type::PLAYER_SHOT_BREAKER);
				newParticle->collider->AddListener(this);
				break;
			case 1:
				shotSpawn.y -= 32;
				shotSpawn.x -= 64;

				newParticle = App->particles->AddParticle(App->particles->diceAbilityLeft, shotSpawn.x, shotSpawn.y, Collider::Type::PLAYER_SHOT_BREAKER);
				newParticle->collider->AddListener(this);
				break;
			case 2:
				shotSpawn.y += 64;
				shotSpawn.x += 0;

				newParticle = App->particles->AddParticle(App->particles->diceAbilityDown, shotSpawn.x, shotSpawn.y, Collider::Type::PLAYER_SHOT_BREAKER);
				newParticle->collider->AddListener(this);
				break;
			case 3:
				shotSpawn.y -= 20;
				shotSpawn.x += 20;

				newParticle = App->particles->AddParticle(App->particles->diceAbilityRight, shotSpawn.x, shotSpawn.y, Collider::Type::PLAYER_SHOT_BREAKER);
				newParticle->collider->AddListener(this);
				break;
			default:
				break;
			}
			App->audio->PlayFx(shootFx);
		}
		
		if (habilityDelay <= -40) {

			//End diceHability secuence, take one life, reset deffault damage, reset deffault Roll the dice, reset deffault delay
			stateHability = false;
			lifePlayer--;
			hability = 50;
			rollTheDice = false;
			habilityDelay = 100;
		}
	}
	else if (stateBasicAttack) {
		basicAttackDelay--;

#pragma region WASD

		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
		{
			position.x -= speed;

			switch (direction)
			{
			case 0:
				currentDiceAnimation = &upAnim;
				break;
			case 1:
				currentDiceAnimation = &leftAnim;
				break;
			case 2:
				currentDiceAnimation = &downAnim;
				break;
			case 3:
				currentDiceAnimation = &rightAnim;
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
				currentDiceAnimation = &upAnim;
				break;
			case 1:
				currentDiceAnimation = &leftAnim;
				break;
			case 2:
				currentDiceAnimation = &downAnim;
				break;
			case 3:
				currentDiceAnimation = &rightAnim;
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
				currentDiceAnimation = &upAnim;
				break;
			case 1:
				currentDiceAnimation = &leftAnim;
				break;
			case 2:
				currentDiceAnimation = &downAnim;
				break;
			case 3:
				currentDiceAnimation = &rightAnim;
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
				currentDiceAnimation = &upAnim;
				break;
			case 1:
				currentDiceAnimation = &leftAnim;
				break;
			case 2:
				currentDiceAnimation = &downAnim;
				break;
			case 3:
				currentDiceAnimation = &rightAnim;
				break;
			default:
				break;
			}
		}
#pragma endregion

		if (basicAttackDelay == 0) {
			iPoint shotSpawn = position;
			switch (direction)
			{
			case 0:
				shotSpawn.y += 10;
				shotSpawn.x += 15;
				break;
			case 1:
				shotSpawn.y += 10;
				shotSpawn.x += 15;
				break;
			case 2:
				shotSpawn.y += 15;
				shotSpawn.x += 5;
				break;
			case 3:
				shotSpawn.y += 10;
				shotSpawn.x += 15;
				break;
			default:
				break;
			}
			Particle* newParticle = App->particles->AddParticle(App->particles->diceBasicAttack, shotSpawn.x, shotSpawn.y, Collider::Type::PLAYER_SHOT);
			newParticle->collider->AddListener(this);
			App->audio->PlayFx(shootFx);
		}

		if (basicAttackDelay <= -40) {

			//End diceHability secuence, take one life, reset deffault damage, reset deffault Roll the dice, reset deffault delay
			stateBasicAttack = false;
			basicAttackDelay = 20;
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
				currentDiceAnimation = &upAnim;
				currentDiceHandAnimation = &idleHandAnimUp;
				break;
			case 1:
				currentDiceAnimation = &leftAnim;
				currentDiceHandAnimation = &idleHandAnimLeft;
				break;
			case 2:
				currentDiceAnimation = &downAnim;
				currentDiceHandAnimation = &idleHandAnimDown;
				break;
			case 3:
				currentDiceAnimation = &rightAnim;
				currentDiceHandAnimation = &idleHandAnimRight;
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
				currentDiceAnimation = &upAnim;
				currentDiceHandAnimation = &idleHandAnimUp;
				break;
			case 1:
				currentDiceAnimation = &leftAnim;
				currentDiceHandAnimation = &idleHandAnimLeft;
				break;
			case 2:
				currentDiceAnimation = &downAnim;
				currentDiceHandAnimation = &idleHandAnimDown;
				break;
			case 3:
				currentDiceAnimation = &rightAnim;
				currentDiceHandAnimation = &idleHandAnimRight;
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
				currentDiceAnimation = &upAnim;
				currentDiceHandAnimation = &idleHandAnimUp;
				break;
			case 1:
				currentDiceAnimation = &leftAnim;
				currentDiceHandAnimation = &idleHandAnimLeft;
				break;
			case 2:
				currentDiceAnimation = &downAnim;
				currentDiceHandAnimation = &idleHandAnimDown;
				break;
			case 3:
				currentDiceAnimation = &rightAnim;
				currentDiceHandAnimation = &idleHandAnimRight;
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
				currentDiceAnimation = &upAnim;
				currentDiceHandAnimation = &idleHandAnimUp;
				break;
			case 1:
				currentDiceAnimation = &leftAnim;
				currentDiceHandAnimation = &idleHandAnimLeft;
				break;
			case 2:
				currentDiceAnimation = &downAnim;
				currentDiceHandAnimation = &idleHandAnimDown;
				break;
			case 3:
				currentDiceAnimation = &rightAnim;
				currentDiceHandAnimation = &idleHandAnimRight;
				break;
			default:
				break;
			}
		}
#pragma endregion

		if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
		{
			direction = 0;
			App->particles->diceBasicAttack.speed.x = 0;
			App->particles->diceBasicAttack.speed.y = 5;
		}

		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
		{
			direction = 1;
			App->particles->diceBasicAttack.speed.x = 5;
			App->particles->diceBasicAttack.speed.y = 0;
		}

		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
		{
			direction = 2;
			App->particles->diceBasicAttack.speed.x = 0;
			App->particles->diceBasicAttack.speed.y = -5;
		}

		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
		{
			direction = 3;
			App->particles->diceBasicAttack.speed.x = -5;
			App->particles->diceBasicAttack.speed.y = 0;
		}

		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
		{
			stateBasicAttack = true;

			switch (direction)
			{
			case 0:
				handUpAttackAnim.Reset();
				currentDiceHandAnimation = &handUpAttackAnim;
				break;
			case 1:
				handLeftAttackAnim.Reset();
				currentDiceHandAnimation = &handLeftAttackAnim;
				break;
			case 2:
				handDownAttackAnim.Reset();
				currentDiceHandAnimation = &handDownAttackAnim;
				break;
			case 3:
				handRightAttackAnim.Reset();
				currentDiceHandAnimation = &handRightAttackAnim;
				break;
			default:
				break;
			}
		}

		if (App->input->keys[SDL_SCANCODE_E] == Key_State::KEY_DOWN) {
			stateHability = true;

			switch (direction)
			{
			case 0:
				handUpSpecialAnim.Reset();
				currentDiceHandAnimation = &handUpSpecialAnim;
				break;
			case 1:
				handLeftSpecialAnim.Reset();
				currentDiceHandAnimation = &handLeftSpecialAnim;
				break;
			case 2:
				handDownSpecialAnim.Reset();
				currentDiceHandAnimation = &handDownSpecialAnim;
				break;
			case 3:
				handRightSpecialAnim.Reset();
				currentDiceHandAnimation = &handRightSpecialAnim;
				break;
			default:
				break;
			}
		}

		// If no up/down movement detected, set the current animation back to idle
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_E] == Key_State::KEY_IDLE) {
			switch (direction)
			{
			case 0:
				currentDiceAnimation = &idleAnimUp;
				break;
			case 1:
				currentDiceAnimation = &idleAnimLeft;
				break;
			case 2:
				currentDiceAnimation = &idleAnimDown;
				break;
			case 3:
				currentDiceAnimation = &idleAnimRight;
				break;
			default:
				break;
			}
		}

		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_E] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_IDLE) {
			switch (direction)
			{
			case 0:
				currentDiceHandAnimation = &idleHandAnimUp;
				break;
			case 1:
				currentDiceHandAnimation = &idleHandAnimLeft;
				break;
			case 2:
				currentDiceHandAnimation = &idleHandAnimDown;
				break;
			case 3:
				currentDiceHandAnimation = &idleHandAnimRight;
				break;
			default:
				break;
			}
		}

	}
  
	if (lifePlayer <= 0 && !destroyed) {
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneMenu, 60);

		destroyed = true;

		App->audio->PlayFx(dieFx);
	}

	collider->SetPos(position.x, position.y);

	currentDiceAnimation->Update();
	currentDiceHandAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentDiceAnimation->GetCurrentFrame();
		App->render->Blit(diceTexture, position.x, position.y, &rect);

		if (stateHability) {
			SDL_Rect rect2 = currentDiceHandAnimation->GetCurrentFrame();
			App->render->Blit(diceHandTexture, position.x, position.y - 32, &rect2);
		}
		else {
			SDL_Rect rect2 = currentDiceHandAnimation->GetCurrentFrame();
			App->render->Blit(diceHandTexture, position.x, position.y, &rect2);
		}
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
		//Hit FX ????
		//App->audio->PlayFx(dieFx);

		lifePlayer--;
	}
}