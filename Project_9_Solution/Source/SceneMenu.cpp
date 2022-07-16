#include "SceneMenu.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h" 
#include "ModuleFonts.h"

SceneMenu::SceneMenu(bool startEnabled) : Module(startEnabled) {

}

SceneMenu::~SceneMenu() {

}

// Load assets
bool SceneMenu::Start() {
	LOG("Loading background assets");

	bool ret = true;

	//bgTexture = App->textures->Load("Assets/Sprites/startScreen.png");
	//App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	fontId = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	selection = 0;
	return ret;
}

Update_Status SceneMenu::Update() {
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->fonts->BlitText(250, 25, 0, "just dice"); // need to change game title
	App->fonts->BlitText(50, 75, 0, "start");
	App->fonts->BlitText(50, 100, 0, "credits");
	App->fonts->BlitText(50, 125, 0, "exit");

	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN) {
		if (selection == 2) {
			selection = 0;
		} else {
			selection++;
		}
		
	}
	if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN) {
		if (selection == 0) {
			selection = 2;
		} else {
			selection--;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
		switch (selection) {
		case 0:
			App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
			break;
		case 1:
			// should go to the credits scene
			//App->fade->FadeToBlack(this, (Module*)App->sceneCredits, 90);
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
	//App->render->Blit(bgTexture, 0, 0, NULL);
	switch (selection) {
	case 0:
		rect.x = 25;
		rect.y = 65;
		App->render->DrawQuad(rect, 0, 255, 0, 80);
		break;
	case 1:
		rect.x = 25;
		rect.y = 90;
		App->render->DrawQuad(rect, 0, 255, 0, 80);
		break;
	case 2:
		rect.x = 25;
		rect.y = 115;
		App->render->DrawQuad(rect, 0, 255, 0, 80);
		break;
	default:
		break;
	}

	return Update_Status::UPDATE_CONTINUE;
}