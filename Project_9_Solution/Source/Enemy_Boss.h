#ifndef __ENEMY_BOSS_H__
#define __ENEMY_BOSS_H__

#include "Enemy.h"

class Enemy_Boss : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Boss(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:

	// The enemy animation
	Animation idleAnim;
	Animation spinAnim;
	Animation deathAnim;

public:
	// Sound effect indices
	uint idleFx = 0;
	uint attackFx = 0;
};

#endif // __ENEMY_BOSS_H__

