#ifndef __BREAKABLE_TABLE_H__
#define __BREAKABLE_TABLE_H__

#include "Breakable.h"

class Breakable_Table : public Breakable {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and the collider
	Breakable_Table(int x, int y, unsigned short version);

	void Update() override;

	void OnCollision(Collider* collider) override;

};

#endif // __BREAKABLE_TABLE_H__