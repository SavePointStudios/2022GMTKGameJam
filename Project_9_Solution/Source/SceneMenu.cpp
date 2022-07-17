#include "SceneMenu.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h" 
#include "ModuleFonts.h"
#include "ModuleParticles.h"

SceneMenu::SceneMenu(bool startEnabled) : Module(startEnabled) {

	anim.PushBack({ 0, 64, 32, 32 });
	anim.PushBack({ 32, 64, 32, 32 });
	anim.PushBack({ 64, 64, 32, 32 });
	anim.speed = 0.1f;
	currentAnim = &anim;
}

SceneMenu::~SceneMenu() {

}

// Load assets
bool SceneMenu::Start() {
	LOG("Loading background assets");
	bool ret = true;

	bgTexture = App->textures->Load("Assets/Scenes/0.png");
	playerTexture = App->textures->Load("Assets/Sprites/Dice_Character_Spritesheet.png");
	logo = App->textures->Load("Assets/Sprites/logoGame.png");
	App->audio->PlayMusic("Assets/Music/Menu minor.ogg", 1.0f); // Take minor out if we want the "happy" version
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	fontId = App->fonts->Load("Assets/Fonts/casino_font_black.png", lookupTable, 1);

	// SFX Loading
	selectHover = App->audio->LoadFx("Assets/Fx/Menu/Hover.wav");
	selected = App->audio->LoadFx("Assets/Fx/Menu/Select.wav");
	hasSelected = false;
	selection = 0;

	return ret;
}

Update_Status SceneMenu::Update() {
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN && !hasSelected) {
		if (selection == 2) {
			selection = 0;
		} else {
			selection++;
		}
		if (!hasSelected) {
			App->audio->PlayFx(selectHover);
		}
	}
	if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN && !hasSelected) {
		if (selection == 0) {
			selection = 2;
		} else {
			selection--;
		}
		if (!hasSelected) {
			App->audio->PlayFx(selectHover);
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {

		if (!hasSelected) {
			hasSelected = !hasSelected;
			App->audio->PlayFx(selected);
		}
		
		switch (selection) {
		case 0:
			App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
			break;
		case 1:
			App->fade->FadeToBlack(this, (Module*)App->sceneCredits, 90);
			break;
		case 2:
			return Update_Status::UPDATE_STOP;
		default:
			break;
		}
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneMenu::PostUpdate() {
	// Draw everything --------------------------------------

	SDL_Rect rect;
	rect.h = 20;
	rect.w = 20;

	App->render->Blit(bgTexture, App->render->camera.x, App->render->camera.y, NULL);

	App->fonts->BlitText(50, 25, 0, "no time to dice"); // need to change game title
	App->fonts->BlitText(50, 75, 0, "start");
	App->fonts->BlitText(50, 125, 0, "credits");
	App->fonts->BlitText(50, 175, 0, "exit");
	int x = 15;
	int y;
	switch (selection) {
	case 0:
		y = 72;
		break;
	case 1:
		y = 122;
		break;
	case 2:
		y = 172;
		break;
	default:
		break;
	}
	rect = currentAnim->GetCurrentFrame();
	currentAnim->Update();
	App->render->Blit(playerTexture, x, y, &rect);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneMenu::CleanUp()
{
	App->textures->Unload(bgTexture);
	App->textures->Unload(playerTexture);

	App->fonts->UnLoad(fontId);

	return true;
}