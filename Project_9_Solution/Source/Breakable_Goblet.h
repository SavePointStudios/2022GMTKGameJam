#ifndef __BREAKABLE_GOBLET_H__
#define __BREAKABLE_GOBLET_H__

#include "Breakable.h"

class Breakable_Goblet : public Breakable {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and the collider
	Breakable_Goblet(int x, int y, unsigned short version);

	void Update() override;

	void OnCollision(Collider* collider) override;

};

#endif // __BREAKABLE_GOBLET_H__