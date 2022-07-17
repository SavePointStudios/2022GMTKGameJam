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
	ceroLifeAnim.PushBack({ 0, 0, 97, 500 });
	ceroLifeAnim.loop = false;

	oneLifeAnim.PushBack({ 97, 0, 97, 500 });
	oneLifeAnim.loop = false;

	twoLifeAnim.PushBack({ 194, 0, 97, 500 });
	twoLifeAnim.loop = false;

	threeLifeAnim.PushBack({ 291, 0, 97, 500 });
	threeLifeAnim.loop = false;

	fourLifeAnim.PushBack({ 388, 0, 97, 500 });
	fourLifeAnim.loop = false;

	fiveLifeAnim.PushBack({ 485, 0, 97, 500 });
	fiveLifeAnim.loop = false;

	sixLifeAnim.PushBack({ 582, 0, 97, 500 });
	sixLifeAnim.loop = false;

}

ModuleUI::~ModuleUI()
{

}

bool ModuleUI::Start()
{
	lifeBarTexture = App->textures->Load("Assets/Sprites/Lifes_SpriteSheet.png");
	currentLifeBarAnimation = &oneLifeAnim;

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

	//if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN)	//Direct WIN (F3)
	//{

	//}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleUI::PostUpdate()
{
	// Draw UI
	SDL_Rect rect = currentLifeBarAnimation->GetCurrentFrame();
	App->render->Blit(lifeBarTexture, App->render->camera.x, App->render->camera.y, &rect);

	//Score
	//sprintf_s(scoreText, 10, "%d", score);
	//App->fonts->BlitText(204, 8, ScoreFont, scoreText);//right

	return Update_Status::UPDATE_CONTINUE;
}


bool ModuleUI::CleanUp()
{
	return true;
}