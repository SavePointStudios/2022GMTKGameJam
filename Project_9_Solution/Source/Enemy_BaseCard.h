#ifndef __ENEMY_BASECARD_H__
#define __ENEMY_BASECARD_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_BaseCard : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_BaseCard(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void updateMovement();
	void startAttack();
	void attack();

	void initAnimations();

private:
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation walk;

	//Timers for the attack
	int startTimer = 0;
	int currentTime = 0;
	bool attacking = false;

	ushort attackdir = 0;

	int movSpeed = 2;
};

#endif // __ENEMY_BASECARD_H__