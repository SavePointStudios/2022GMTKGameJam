#include "ModuleUI.h"


#include "SDL/include/SDL.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"


#include "stdio.h"

ModuleUI::ModuleUI(bool startEnabled) : Module(startEnabled)
{
	ceroLifeAnim.PushBack({ 0, 0, 39, 200 });
	ceroLifeAnim.loop = false;

	oneLifeAnim.PushBack({ 39, 0, 39, 200 });
	oneLifeAnim.loop = false;

	twoLifeAnim.PushBack({ 78, 0, 39, 200 });
	twoLifeAnim.loop = false;

	threeLifeAnim.PushBack({ 117, 0, 39, 200 });
	threeLifeAnim.loop = false;

	fourLifeAnim.PushBack({ 156, 0, 39, 200 });
	fourLifeAnim.loop = false;

	fiveLifeAnim.PushBack({ 195, 0, 39, 200 });
	fiveLifeAnim.loop = false;

	sixLifeAnim.PushBack({ 234, 0, 38, 200 });
	sixLifeAnim.loop = false;

	oneRollAnim.PushBack({ 0, 0, 32, 32 });
	oneRollAnim.PushBack({ 32, 0, 32, 32 });
	oneRollAnim.PushBack({ 64, 96, 32, 32 });
	oneRollAnim.PushBack({ 96, 96, 32, 32 });
	oneRollAnim.loop = false;
	oneRollAnim.speed = 0.05f;

	twoRollAnim.PushBack({ 0, 0, 32, 32 });
	twoRollAnim.PushBack({ 32, 0, 32, 32 });
	twoRollAnim.PushBack({ 0, 96, 32, 32 });
	twoRollAnim.PushBack({ 32, 96, 32, 32 });
	twoRollAnim.loop = false;
	twoRollAnim.speed = 0.05f;

	threeRollAnim.PushBack({ 0, 0, 32, 32 });
	threeRollAnim.PushBack({ 32, 0, 32, 32 });
	threeRollAnim.PushBack({ 64, 64, 32, 32 });
	threeRollAnim.PushBack({ 96, 64, 32, 32 });
	threeRollAnim.loop = false;
	threeRollAnim.speed = 0.05f;

	fourRollAnim.PushBack({ 0, 0, 32, 32 });
	fourRollAnim.PushBack({ 32, 0, 32, 32 });
	fourRollAnim.PushBack({ 0, 64, 32, 32 });
	fourRollAnim.PushBack({ 32, 64, 32, 32 });
	fourRollAnim.loop = false;
	fourRollAnim.speed = 0.05f;

	fiveRollAnim.PushBack({ 0, 0, 32, 32 });
	fiveRollAnim.PushBack({ 32, 0, 32, 32 });
	fiveRollAnim.PushBack({ 64, 32, 32, 32 });
	fiveRollAnim.PushBack({ 96, 32, 32, 32 });
	fiveRollAnim.loop = false;
	fiveRollAnim.speed = 0.05f;

	sixRollAnim.PushBack({ 0, 0, 32, 32 });
	sixRollAnim.PushBack({ 32, 0, 32, 32 });
	sixRollAnim.PushBack({ 0, 32, 32, 32 });
	sixRollAnim.PushBack({ 32, 32, 32, 32 });
	sixRollAnim.loop = false;
	sixRollAnim.speed = 0.05f;
}

ModuleUI::~ModuleUI()
{

}

bool ModuleUI::Start()
{
	lifeBarTexture = App->textures->Load("Assets/Sprites/Lifes_SpriteSheet.png");
	currentLifeBarAnimation = &oneLifeAnim;

	rollTexture = App->textures->Load("Assets/Sprites/Dice_Special_Spritesheet.png");
	currentRollAnimation = &oneRollAnim;

	bool ret = true;

	score = 0;

	//uiSprites = App->textures->Load("Assets/Spriteswind/Sprites/UI/UISpriteSheetFinal.png");

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	ScoreFont = App->fonts->Load("Assets/Fonts/casino_font_black.png", lookupTable, 1);

	//winnerRefereeSFX = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/Referee/WinnerReferee.wav");

	return ret;
}

Update_Status ModuleUI::Update()
{
	switch (App->player->lifePlayer)
	{
	case 0:
		currentLifeBarAnimation = &ceroLifeAnim;
		break;
	case 1:
		currentLifeBarAnimation = &oneLifeAnim;
		break;
	case 2:
		currentLifeBarAnimation = &twoLifeAnim;
		break;
	case 3:
		currentLifeBarAnimation = &threeLifeAnim;
		break;
	case 4:
		currentLifeBarAnimation = &fourLifeAnim;
		break;
	case 5:
		currentLifeBarAnimation = &fiveLifeAnim;
		break;
	case 6:
		currentLifeBarAnimation = &sixLifeAnim;
		break;
	default:
		break;
	}

	currentLifeBarAnimation->Update();
	currentRollAnimation->Update();

	//if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN)	//Direct WIN (F3)
	//{

	//}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleUI::PostUpdate()
{
	// Draw UI
	SDL_Rect rect = currentLifeBarAnimation->GetCurrentFrame();
	App->render->Blit(lifeBarTexture, App->render->camera.x, App->render->camera.y+80, &rect);

	if (App->player->stateAbility) {
		if (App->player->abilityDelay<=90) {
			SDL_Rect rect2 = currentRollAnimation->GetCurrentFrame();
			App->render->Blit(rollTexture, App->player->position.x, App->player->position.y - 64, &rect2);
		}
	}

	//Score
	//sprintf_s(scoreText, 10, "%d", score);
	//App->fonts->BlitText(204, 8, ScoreFont, scoreText);//right

	return Update_Status::UPDATE_CONTINUE;
}


bool ModuleUI::CleanUp()
{
	return true;
}