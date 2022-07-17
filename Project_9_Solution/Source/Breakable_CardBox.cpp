#include "Breakable_CardBox.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Breakable_CardBox::Breakable_CardBox(int x, int y, unsigned short version) : Breakable(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 32, 32 }, Collider::Type::BREAKABLE, (Module*)App->breakables);

	switch (version) {
	default:
		animation.PushBack({ 96,0,32,32 });
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
