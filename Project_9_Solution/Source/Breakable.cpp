#include "Breakable.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Breakable::Breakable(int x, int y) : position(x, y) {
	spawnPos = position;
}

Breakable::~Breakable() {
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Breakable::GetCollider() const {
	return collider;
}

void Breakable::Update() {
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Breakable::Draw() {
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Breakable::OnCollision(Collider* collider) {

}