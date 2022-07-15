#ifndef __BREAKABLE_FENCE_H__
#define __BREAKABLE_FENCE_H__

#include "Breakable.h"

class Breakable_Fence : public Breakable {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and the collider
	Breakable_Fence(int x, int y, unsigned short version);

	void Update() override;

	void OnCollision(Collider* collider) override;

};

#endif // __BREAKABLE_FENCE_H__