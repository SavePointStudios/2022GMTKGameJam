#include "Breakable_Goblet.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

Breakable_Goblet::Breakable_Goblet(int x, int y, unsigned short version) : Breakable(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 32, 32 }, Collider::Type::BREAKABLE, (Module*)App->breakables);

	switch (version) {
	default:
		// default
		animation.PushBack({ 64,0,32,32 });
		break;
	}

	currentAnim = &animation;
}

void Breakable_Goblet::Update() {
	Breakable::Update();
}

void Breakable_Goblet::OnCollision(Collider* collider) {
	//App->particles->AddParticle();
	Breakable::OnCollision(collider);
}
