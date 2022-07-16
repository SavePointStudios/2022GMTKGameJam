#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Powerup {
public:
	Powerup(int x, int y);
	virtual ~Powerup();
	const Collider* GetCollider() const;

	virtual void Update();
	virtual void Draw();
	virtual void OnCollision(Collider* collider) = 0;

public:
	iPoint position;
	SDL_Texture* texture = nullptr;
	int pickUpFx = 0;

protected:
	Animation* currentAnim = nullptr;
	Animation animation;
	Collider* collider = nullptr;
	iPoint spawnPos;

};

#endif