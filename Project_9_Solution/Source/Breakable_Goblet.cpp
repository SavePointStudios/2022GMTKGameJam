#include "Breakable_Goblet.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

Breakable_Goblet::Breakable_Goblet(int x, int y, unsigned short version) : Breakable(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 48, 24 }, Collider::Type::BREAKABLE, (Module*)App->breakables);
	//destroyedFx = App->audio->LoadFx();
	switch (version) {
		// in case if we want different goblets with diff texture
	case 1:
		animation.PushBack({ 0,64,32,32 });
		break;
	default:
		// default
		animation.PushBack({ 0,32,21,22 });
		break;
	}

	currentAnim = &animation;
}

void Breakable_Goblet::Update() {
	Breakable::Update();
}

void Breakable_Goblet::OnCollision(Collider* collider) {
	// would be good to show wood/metal/plastic particles dropping
	// play fx
}
