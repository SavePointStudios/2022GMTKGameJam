#ifndef __BREAKABLE_CHIPS_H__
#define __BREAKABLE_CHIPS_H__

#include "Breakable.h"

class Breakable_Chips : public Breakable {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and the collider
	Breakable_Chips(int x, int y, unsigned short version);

	void Update() override;

	void OnCollision(Collider* collider) override;

};

#endif // __BREAKABLE_CHIPS_H__