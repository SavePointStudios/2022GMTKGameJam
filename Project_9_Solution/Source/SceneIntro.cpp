#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled) {

}

SceneIntro::~SceneIntro() {

}

// Load assets
bool SceneIntro::Start() {
	LOG("Loading background assets");

	bool ret = true;

	scene0 = App->textures->Load("Assets/Scenes/1.png");
	scene1 = App->textures->Load("Assets/Scenes/2.png");
	scene2 = App->textures->Load("Assets/Scenes/3.png");
	scene3 = App->textures->Load("Assets/Scenes/4.png");
	scene4 = App->textures->Load("Assets/Scenes/5.png");
	scene5 = App->textures->Load("Assets/Scenes/6.png");
	scene6 = App->textures->Load("Assets/Scenes/7.png");
	scene7 = App->textures->Load("Assets/Scenes/8.png");

	App->audio->PlayMusic("Assets/Music/Intro.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	currentScene = 0;
	return ret;
}

Update_Status SceneIntro::Update() {
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
		currentScene++;
	}
	if (currentScene >= 8) {
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate() {
	// Draw everything --------------------------------------
	switch (currentScene) {
	case 0:
		App->render->Blit(scene0, 0, 0, NULL);
		break;
	case 1:
		App->render->Blit(scene1, 0, 0, NULL);
		break;
	case 2:
		App->render->Blit(scene2, 0, 0, NULL);
		break;
	case 3:
		App->render->Blit(scene3, 0, 0, NULL);
		break;
	case 4:
		App->render->Blit(scene4, 0, 0, NULL);
		break;
	case 5:
		App->render->Blit(scene5, 0, 0, NULL);
		break;
	case 6:
		App->render->Blit(scene6, 0, 0, NULL);
		break;
	case 7:
		App->render->Blit(scene7, 0, 0, NULL);
		break;
	default:
		App->render->Blit(scene7, 0, 0, NULL);
		break;
	}
	

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	App->textures->Unload(scene0);
	App->textures->Unload(scene1);
	App->textures->Unload(scene2);
	App->textures->Unload(scene3);
	App->textures->Unload(scene4);
	App->textures->Unload(scene5);
	App->textures->Unload(scene6);
	App->textures->Unload(scene7);
	
	return true;
}