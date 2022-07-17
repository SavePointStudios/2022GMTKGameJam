#include "Breakable_Chips.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Breakable_Chips::Breakable_Chips(int x, int y, unsigned short version) : Breakable(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::BREAKABLE, (Module*)App->breakables);
	//destroyedFx = App->audio->LoadFx();
	switch (version) {
	// in case if we want different chips with diff texture
	case 1:
		animation.PushBack({ 0,96,32,32 });
		break;
	default:
		animation.PushBack({ 5,72,21,22 });
		break;
	}
	
	// Fx
	// destroyedFx = App->audio->LoadFx("Assets/Fx/Props/chip break.wav");
	
	currentAnim = &animation;
}

void Breakable_Chips::Update() {
	Breakable::Update();
}

void Breakable_Chips::OnCollision(Collider* collider) {
	//App->particles->AddParticle();
	Breakable::OnCollision(collider);
}
