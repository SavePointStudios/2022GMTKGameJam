#ifndef __BREAKABLE_DOOR_H__
#define __BREAKABLE_DOOR_H__

#include "Breakable.h"

class Breakable_Door : public Breakable {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and the collider
	Breakable_Door(int x, int y, unsigned short version);

	void Update() override;

	void OnCollision(Collider* collider) override;

};

#endif // __BREAKABLE_DOOR_H__