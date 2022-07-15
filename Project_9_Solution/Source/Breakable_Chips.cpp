#include "Breakable_Chips.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Breakable_Chips::Breakable_Chips(int x, int y, unsigned short version) : Breakable(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 32, 32 }, Collider::Type::BREAKABLE, (Module*)App->breakables);
	switch (version) {
	case 1:
		animation.PushBack({ 0,96,32,32 });
		break;
	case 2:
		animation.PushBack({ 32,96,32,32 });
		break;
	case 3:
		animation.PushBack({ 64,96,32,32 });
		break;
	case 4:
		animation.PushBack({ 96,96,32,32 });
		break;
	case 5:
		animation.PushBack({ 0,64,32,32 });
		break;
	case 6:
		animation.PushBack({ 32,64,32,32 });
		break;
	default:
		animation.PushBack({ 0,96,32,32 });
		break;
	}

	currentAnim = &animation;
}

void Breakable_Chips::Update() {
	Breakable::Update();
}

void Breakable_Chips::OnCollision(Collider* collider) {

}
