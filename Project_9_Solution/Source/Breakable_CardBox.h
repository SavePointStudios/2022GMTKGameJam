#ifndef __BREAKABLE_CARDBOX_H__
#define __BREAKABLE_CARDBOX_H__

#include "Breakable.h"

class Breakable_CardBox : public Breakable {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and the collider
	Breakable_CardBox(int x, int y, unsigned short version);

	void Update() override;

	void OnCollision(Collider* collider) override;

};

#endif // __BREAKABLE_CARDBOX_H__