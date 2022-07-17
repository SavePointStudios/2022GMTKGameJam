#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::UP_WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::UP_WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::UP_WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::UP_WALL][Collider::Type::PLAYER_SHOT_BREAKER] = true;
	matrix[Collider::Type::UP_WALL][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::UP_WALL][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::UP_WALL][Collider::Type::POWERUP] = false;
	matrix[Collider::Type::UP_WALL][Collider::Type::BOSS] = false;


	matrix[Collider::Type::DOWN_WALL][Collider::Type::PLAYER] = true; 
	matrix[Collider::Type::DOWN_WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::DOWN_WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::DOWN_WALL][Collider::Type::PLAYER_SHOT_BREAKER] = true;
	matrix[Collider::Type::DOWN_WALL][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::DOWN_WALL][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::DOWN_WALL][Collider::Type::POWERUP] = false;
	matrix[Collider::Type::DOWN_WALL][Collider::Type::BOSS] = false;

	matrix[Collider::Type::RIGHT_WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::RIGHT_WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::RIGHT_WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::RIGHT_WALL][Collider::Type::PLAYER_SHOT_BREAKER] = true;
	matrix[Collider::Type::RIGHT_WALL][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::RIGHT_WALL][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::RIGHT_WALL][Collider::Type::POWERUP] = false;
	matrix[Collider::Type::RIGHT_WALL][Collider::Type::BOSS] = false;

	matrix[Collider::Type::LEFT_WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::LEFT_WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::LEFT_WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::LEFT_WALL][Collider::Type::PLAYER_SHOT_BREAKER] = true;
	matrix[Collider::Type::LEFT_WALL][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::LEFT_WALL][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::LEFT_WALL][Collider::Type::POWERUP] = false;
	matrix[Collider::Type::LEFT_WALL][Collider::Type::BOSS] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::UP_WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::DOWN_WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::RIGHT_WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::LEFT_WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT_BREAKER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BREAKABLE] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::POWERUP] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOSS] = false;
	
	matrix[Collider::Type::ENEMY][Collider::Type::UP_WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::DOWN_WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::RIGHT_WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::LEFT_WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT_BREAKER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::BREAKABLE] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::POWERUP] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::BOSS] = false;
	
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::UP_WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::DOWN_WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::RIGHT_WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::LEFT_WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT_BREAKER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BREAKABLE] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::POWERUP] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BOSS] = false;

	matrix[Collider::Type::PLAYER_SHOT_BREAKER][Collider::Type::UP_WALL] = false;
	matrix[Collider::Type::PLAYER_SHOT_BREAKER][Collider::Type::DOWN_WALL] = false;
	matrix[Collider::Type::PLAYER_SHOT_BREAKER][Collider::Type::RIGHT_WALL] = false;
	matrix[Collider::Type::PLAYER_SHOT_BREAKER][Collider::Type::LEFT_WALL] = false;
	matrix[Collider::Type::PLAYER_SHOT_BREAKER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT_BREAKER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT_BREAKER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT_BREAKER][Collider::Type::PLAYER_SHOT_BREAKER] = false;
	matrix[Collider::Type::PLAYER_SHOT_BREAKER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT_BREAKER][Collider::Type::BREAKABLE] = true;
	matrix[Collider::Type::PLAYER_SHOT_BREAKER][Collider::Type::POWERUP] = false;
	matrix[Collider::Type::PLAYER_SHOT_BREAKER][Collider::Type::BOSS] = false;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::UP_WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::DOWN_WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::RIGHT_WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::LEFT_WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT_BREAKER] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::BREAKABLE] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::POWERUP] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::BOSS] = false;

	matrix[Collider::Type::BREAKABLE][Collider::Type::UP_WALL] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::DOWN_WALL] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::RIGHT_WALL] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::LEFT_WALL] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::BREAKABLE][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::BREAKABLE][Collider::Type::PLAYER_SHOT_BREAKER] = true;
	matrix[Collider::Type::BREAKABLE][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::BREAKABLE][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::POWERUP] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::BOSS] = false;

	matrix[Collider::Type::POWERUP][Collider::Type::UP_WALL] = false;
	matrix[Collider::Type::POWERUP][Collider::Type::DOWN_WALL] = false;
	matrix[Collider::Type::POWERUP][Collider::Type::RIGHT_WALL] = false;
	matrix[Collider::Type::POWERUP][Collider::Type::LEFT_WALL] = false;
	matrix[Collider::Type::POWERUP][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::POWERUP][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::POWERUP][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::POWERUP][Collider::Type::PLAYER_SHOT_BREAKER] = false;
	matrix[Collider::Type::POWERUP][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::POWERUP][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::POWERUP][Collider::Type::POWERUP] = false;
	matrix[Collider::Type::POWERUP][Collider::Type::BOSS] = false;

	matrix[Collider::Type::BOSS][Collider::Type::UP_WALL] = false;
	matrix[Collider::Type::BOSS][Collider::Type::DOWN_WALL] = false;
	matrix[Collider::Type::BOSS][Collider::Type::RIGHT_WALL] = false;
	matrix[Collider::Type::BOSS][Collider::Type::LEFT_WALL] = false;
	matrix[Collider::Type::BOSS][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BOSS][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::BOSS][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::BOSS][Collider::Type::PLAYER_SHOT_BREAKER] = false;
	matrix[Collider::Type::BOSS][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::BOSS][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::BOSS][Collider::Type::POWERUP] = false;
	matrix[Collider::Type::BOSS][Collider::Type::BOSS] = false;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

Update_Status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;
	 
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if(matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);
				
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::PostUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}