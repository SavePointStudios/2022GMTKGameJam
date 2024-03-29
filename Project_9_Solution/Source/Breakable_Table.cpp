#include "Breakable_Table.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

Breakable_Table::Breakable_Table(int x, int y, unsigned short version) : Breakable(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 48, 24 }, Collider::Type::BREAKABLE, (Module*)App->breakables);

	switch (version) {
	case 1:
		// horizontal
		animation.PushBack({ 0,64,32,32 });
		break;

	default:
		// vertical default
		animation.PushBack({ 0,32,32,32 });
		break;
	}

	destroyedFx = App->audio->LoadFx("Assets/Fx/Props/table break.wav");

	currentAnim = &animation;
}

void Breakable_Table::Update() {
	Breakable::Update();
}

void Breakable_Table::OnCollision(Collider* collider) {
	//App->particles->AddParticle();
	Breakable::OnCollision(collider);
}
