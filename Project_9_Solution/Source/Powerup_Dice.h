#ifndef __POWERUP_DICE_H__
#define __POWERUP_DICE_H__

#include "Powerup.h"

class Powerup_Dice : public Powerup {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and the collider
	Powerup_Dice(int x, int y);

	void Update() override;

	void OnCollision(Collider* collider) override;
	//void Draw() override;
	//int deadFx;
	//int idleFx;
//protected:
//	Animation* currentAnimBot = nullptr;
//
//	Animation idleAnimTop, idleAnimBot;
//	Animation pickUpAnimTop, pickUpAnimBot;
//
//private:
//	uint idleFxCooldown = 0;

};

#endif // __POWERUP_DICE_H__