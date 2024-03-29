#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	bool CleanUp();

public:
	//Life unit points
	int lifePlayer = 1;
	
	// Position of the player in the map
	iPoint position;

	// Direction of the player in the map
	int direction = 3;
	int movementPlayer = 4;
	
	// The speed in which we move the player (pixels per frame)
	int speed = 2;

	//DAMAGES
	//Basic attack damage
	int basicAttack = 25;

	//Ability damage
	int ability = 50;

	// The spritesheets loaded into an SDL_Texture
	SDL_Texture* diceTexture = nullptr;
	SDL_Texture* diceHandTexture = nullptr;
	
	// The pointer to the current animation
	// It will be switched depending on the movement direction
	Animation* currentDiceAnimation = nullptr;
	Animation* currentDiceHandAnimation = nullptr;

	// A set of animations
	Animation idleAnimRight;
	Animation idleAnimLeft;
	Animation idleAnimDown;
	Animation idleAnimUp;

	Animation leftAnim;
	Animation rightAnim;
	Animation upAnim;
	Animation downAnim;

	Animation specialLeftAnim;
	Animation specialRightAnim;
	Animation specialUpAnim;
	Animation specialDownAnim;

	Animation idleHandAnimRight;
	Animation idleHandAnimLeft;
	Animation idleHandAnimDown;
	Animation idleHandAnimUp;

	Animation handRightAttackAnim;
	Animation handLeftAttackAnim;
	Animation handDownAttackAnim;
	Animation handUpAttackAnim;

	Animation handRightSpecialAnim;
	Animation handLeftSpecialAnim;
	Animation handDownSpecialAnim;
	Animation handUpSpecialAnim;


	// The player's collider
	Collider* collider = nullptr;

	//STATES

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	//A flag  to detetct when thw player is throwing his diceAbility
	bool stateAbility = false;

	//A flag  to detetct when thw player is throwing his diceAbility
	bool stateBasicAttack = false;

	//A flag  to detetct when thw player is throwing his diceAbility
	bool rollTheDice = false;

	// Sound effects indices
	uint shootFx = 0;
	uint specialLoadFx = 0;
	uint dieFx = 0;
	uint hitFx = 0;
	uint AllInFx = 0;

	// Font variables
	int Font = -1;
	char Text[10] = { "\0" };

	int abilityDelay = 100;
	int basicAttackDelay = 20;

};

#endif //!__MODULE_PLAYER_H__