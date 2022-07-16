#include "Breakable_CardBox.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Breakable_CardBox::Breakable_CardBox(int x, int y, unsigned short version) : Breakable(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 48, 24 }, Collider::Type::BREAKABLE, (Module*)App->breakables);
	//destroyedFx = App->audio->LoadFx();
	switch (version) {
		// in case if we want different cardboxes with diff texture
	case 1:
		animation.PushBack({ 0,96,32,32 });
		break;
	default:
		// default
		animation.PushBack({ 5,72,21,22 });
		break;
	}

	currentAnim = &animation;
}

void Breakable_CardBox::Update() {
	Breakable::Update();
}

void Breakable_CardBox::OnCollision(Collider* collider) {
	//App->particles->AddParticle();
	Breakable::OnCollision(collider);
	
}
