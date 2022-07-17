#ifndef __ENEMY_J_H__
#define __ENEMY_J_H__

#include "Enemy.h"

class Enemy_J : public Enemy {
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_J(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:

	// The enemy animation
	Animation idleAnim;

	int timerSpawn = 0;
};

#endif // __ENEMY_J_H__

