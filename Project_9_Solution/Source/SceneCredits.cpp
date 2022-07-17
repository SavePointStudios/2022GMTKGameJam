#include "SceneCredits.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h" 
#include "ModuleFonts.h"
#include "ModuleParticles.h"

SceneCredits::SceneCredits(bool startEnabled) : Module(startEnabled) {

}

SceneCredits::~SceneCredits() {

}

// Load assets
bool SceneCredits::Start() {
	LOG("Loading background assets");
	bool ret = true;

	//bgTexture = App->textures->Load("");

	//App->audio->PlayMusic("Assets/Music/Menu.ogg", 1.0f);
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	fontId = App->fonts->Load("Assets/Fonts/casino_font_black.png", lookupTable, 1);

	return ret;
}

Update_Status SceneCredits::Update() {
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->sceneMenu, 90);
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneCredits::PostUpdate() {
	// Draw everything --------------------------------------

	//App->render->Blit(bgTexture, App->render->camera.x, App->render->camera.y, NULL);

	return Update_Status::UPDATE_CONTINUE;
}