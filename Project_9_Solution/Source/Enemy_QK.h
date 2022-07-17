#ifndef __Enemy_QK_H__
#define __Enemy_QK_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleDebug.h"

struct SDL_Texture;
struct Collider;

class Enemy_QK : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_QK(int x, int y);
	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void QKstartAttack();
	void QKattack();
	void QKtrackPlayer();

	void QKinitAnimations();
	void deathAnimation();

private:
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation attackRight;
	Animation attackLeft;
	Animation attackUp;
	Animation attackDown;

	Path path; //(Needed)
	Animation *idleAnimation;
	Animation *shot;

	iPoint shotSpawn = position;
	iPoint shotPos = position;

	//Timers for the attack
	int startTimer = 0;
	int currentTime = 0;
	bool QKattacking = false;
	int timerSpawn = 0;

	ushort attackdir = 0;

};

#endif // __ENEMY_H__ 