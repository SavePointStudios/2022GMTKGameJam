#include "Powerup_Dice.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Powerup_Dice::Powerup_Dice(int x, int y) : Powerup(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 32, 32 }, Collider::Type::POWERUP, (Module*)App->powerups);
	animation.PushBack({ 0, 132, 22, 23 });
	currentAnim = &animation;

}

void Powerup_Dice::Update() {
	Powerup::Update();
}

void Powerup_Dice::OnCollision(Collider* collider) {
	//App->audio->PlayFx(pickUpFx);
	// code behaviour on player
}
