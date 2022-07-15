#include "ModuleDebug.h"
//Este es el nuevo
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "Enemy.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"
#include <string>
using namespace std;

ModuleDebug::ModuleDebug(bool startEnabled) : Module(startEnabled) {
	debug = false;
}
ModuleDebug::~ModuleDebug() {
}

bool ModuleDebug::Start() {

	debug = false;
	return true;
}

Update_Status ModuleDebug::Update() {

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN)
		return Update_Status::UPDATE_STOP;

	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN)
		debug = !debug;

	if (debug) {
		//Funcionalidad debug (esto es el update, aqui no se dibuja nada)
		if (App->input->keys[SDL_SCANCODE_V] == KEY_DOWN)
			variables = !variables;
		if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN)
			camLimits = !camLimits;
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleDebug::PostUpdate() {
	if (debug)
		DebugDraw();

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleDebug::DebugDraw() {

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (App->collisions->colliders[i] == nullptr)
			continue;

		switch (App->collisions->colliders[i]->type) {
		case Collider::Type::NONE: // white (Ejemplo de caja debug)
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::WALL: // blue
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::PLAYER: // green
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::ENEMY: // red
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::PLAYER_SHOT: // yellow
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case Collider::Type::ENEMY_SHOT: // magenta
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case Collider::Type::BREAKABLE:
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 255, 0, 0, alpha);
			break;
		default:
			break;
		}

	}

	//App->fonts->BlitText(0, 0, 0, "ola q tal");

	//Pa cuando tengamos enemigos
	/*for (size_t i = 0; i < MAX_ENEMIES; i++) {
		if (App->enemies->enemies[i] != nullptr) {
			App->render->DrawLine(App->enemies->enemies[i]->position.x + 16,
				App->enemies->enemies[i]->position.y + 32,
				App->enemies->enemies[i]->position.x + 16 + 20 * cos(App->enemies->enemies[i]->degrees * (M_PI / 180)),
				App->enemies->enemies[i]->position.y + 32 + 20 * sin(App->enemies->enemies[i]->degrees * (M_PI / 180)),
				0, 255, 0, 255);
		}
	}*/

	//Camera limits debug

	if (camLimits) {
		//Left offset
		App->render->DrawLine(App->render->camera.x + SCREEN_WIDTH / 3,
			App->render->camera.y,
			App->render->camera.x + SCREEN_WIDTH / 3,
			App->render->camera.y + SCREEN_HEIGHT,
			255, 255, 50, 255, 0.5 * SCREEN_SIZE, true);

		//Right offset
		App->render->DrawLine(App->render->camera.x + SCREEN_WIDTH / 1.5,
			App->render->camera.y,
			App->render->camera.x + SCREEN_WIDTH / 1.5,
			App->render->camera.y + SCREEN_HEIGHT,
			255, 255, 50, 255, 0.5 * SCREEN_SIZE, true);

		//Upper offset
		App->render->DrawLine(App->render->camera.x,
			(App->render->camera.y + SCREEN_HEIGHT / 2) - 60,
			App->render->camera.x + SCREEN_WIDTH,
			(App->render->camera.y + SCREEN_HEIGHT / 2) - 60,
			255, 255, 50, 255, 0.5 * SCREEN_SIZE, true);
		//Lower offset
		App->render->DrawLine(App->render->camera.x,
			(App->render->camera.y + SCREEN_HEIGHT / 2) + 60,
			App->render->camera.x + SCREEN_WIDTH,
			(App->render->camera.y + SCREEN_HEIGHT / 2) + 60,
			255, 255, 50, 255, 0.5 * SCREEN_SIZE, true);
	}

	//Variables debug
	if (variables) {
		//Ejemplo del debug de las variables
		//App->fonts->BlitText(0, 0, 0, "-GOD MODE");
		App->fonts->BlitText(0, 0, 0, std::to_string(App->player->position.x).c_str());
		App->fonts->BlitText(0, 10, 0, std::to_string(App->player->position.y).c_str());

		App->fonts->BlitText(0, 30, 0, std::to_string(App->player->collider->rect.x).c_str());
		App->fonts->BlitText(0, 40, 0, std::to_string(App->player->collider->rect.y).c_str());
	}
}