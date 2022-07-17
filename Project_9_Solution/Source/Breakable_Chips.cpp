#include "Breakable_Chips.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Breakable_Chips::Breakable_Chips(int x, int y, unsigned short version) : Breakable(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 32, 32 }, Collider::Type::BREAKABLE, (Module*)App->breakables);

	switch (version) {
	default:
		animation.PushBack({ 128,0,32,32 });
		break;
	}

	currentAnim = &animation;
}

void Breakable_Chips::Update() {
	Breakable::Update();
}

void Breakable_Chips::OnCollision(Collider* collider) {
	//App->particles->AddParticle();
	Breakable::OnCollision(collider);
}
