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


#include "stdio.h"

ModuleUI::ModuleUI(bool startEnabled) : Module(startEnabled)
{

}

ModuleUI::~ModuleUI()
{

}

bool ModuleUI::Start()
{
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

	//if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN)	//Direct WIN (F3)
	//{

	//}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleUI::PostUpdate()
{
	// Draw UI 

	//Score
	//sprintf_s(scoreText, 10, "%d", score);
	//App->fonts->BlitText(204, 8, ScoreFont, scoreText);//right

	return Update_Status::UPDATE_CONTINUE;
}


bool ModuleUI::CleanUp()
{
	return true;
}