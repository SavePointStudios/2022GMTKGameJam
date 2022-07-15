#ifndef __BREAKABLE_H__
#define __BREAKABLE_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Breakable {
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Breakable(int x, int y);

	// Destructor
	virtual ~Breakable();

	// Returns the breakable's collider
	const Collider* GetCollider() const;

	// Called from inhering breakable' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleBreakables' Update
	virtual void Draw();

	// Collision response
	virtual void OnCollision(Collider* collider);

public:
	// The current position in the world
	iPoint position;

	// The breakable's texture
	SDL_Texture* texture = nullptr;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// Breakable animation
	Animation animation;

	// The breakable's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;

};

#endif // __BREAKABLE_H__