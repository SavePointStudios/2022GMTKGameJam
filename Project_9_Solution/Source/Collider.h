#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 5

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		UP_WALL,
		DOWN_WALL,
		LEFT_WALL,
		RIGHT_WALL,
		PLAYER,
		ENEMY,
		PLAYER_SHOT,
		PLAYER_SHOT_BREAKER,
		ENEMY_SHOT,
		BREAKABLE,
		POWERUP,
		BOSS,
		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__

