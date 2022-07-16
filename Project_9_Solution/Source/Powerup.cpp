#include "Powerup.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Powerup::Powerup(int x, int y) : position(x, y) {
	spawnPos = position;
	// pickUpFx = App->audio->LoadFx("sounds/sfx/165.wav");
}

Powerup::~Powerup() {
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Powerup::GetCollider() const {
	return collider;
}

void Powerup::Update() {
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Powerup::Draw() {
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}
