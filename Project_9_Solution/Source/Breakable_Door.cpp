#include "Breakable_Door.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Breakable_Door::Breakable_Door(int x, int y, unsigned short version) : Breakable(x, y) {
	
	//destroyedFx = App->audio->LoadFx();
	switch (version) {
		// in case if we want different doors with diff texture
	case 1:
		// horizontal
		collider = App->collisions->AddCollider({ 0, 0, 48, 24 }, Collider::Type::BREAKABLE, (Module*)App->breakables);
		animation.PushBack({ 0,96,32,32 });
		break;

	default:
		// vertical default
		collider = App->collisions->AddCollider({ 0, 0, 24, 48 }, Collider::Type::BREAKABLE, (Module*)App->breakables);
		animation.PushBack({ 5,72,21,22 });
		break;
	}
	
	// Fx
	// destroyedFx = App->audio->LoadFx("Assets/Fx/Props/door break.wav");
	
	currentAnim = &animation;
}

void Breakable_Door::Update() {
	Breakable::Update();
}

void Breakable_Door::OnCollision(Collider* collider) {
	//App->particles->AddParticle();
	Breakable::OnCollision(collider);
}
