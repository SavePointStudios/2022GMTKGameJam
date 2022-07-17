#ifndef __ENEMY_QK_H__
#define __ENEMY_QK_H__

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

	void initAnimations();

	void deathAnimation();
private:
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation attackRight;
	Animation attackLeft;
	Animation attackUp;
	Animation attackDown;

	Path path; //(Needed)

	//Timers for the attack
	int startTimer = 0;
	int currentTime = 0;
	bool attacking = false;

	ushort attackdir = 0;

	int QK_health = 200;
};

#endif // __ENEMY_QK_H__