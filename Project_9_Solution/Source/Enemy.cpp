#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

#include <math.h>

Enemy::Enemy(int x, int y) : position(x, y)
{
	position.x = 424; position.y = 242; //provisional so that it spawns inside the map
	spawnPos = position;
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	lookAtPlayer();

	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Enemy::lookAtPlayer()
{
   	distance.x = App->player->position.x + 16 - this->position.x - 16;
	distance.y = App->player->position.y + 16 - this->position.y - 32;

	alpha = atan2(distance.y, distance.x);

	degrees = alpha / (M_PI / 180.0f);

	if (degrees < 0)
		degrees += 360.0f;
}

void Enemy::OnCollision(Collider* collider)
{

	if (collider->type == Collider::Type::UP_WALL)
	{
		position.y += 2   ;
	}
	else if (collider->type == Collider::Type::DOWN_WALL)
	{
		position.y -= 1;
	}
	else if (collider->type == Collider::Type::RIGHT_WALL)
	{
		position.x -= 1;
	}
	else if (collider->type == Collider::Type::LEFT_WALL)
	{
		position.x += 2;
	}

	if (collider->type == Collider::Type::PLAYER_SHOT || collider->type == Collider::Type::PLAYER)
	{
		/*App->particles->AddParticle(App->particles->explosion, position.x, position.y);
		App->audio->PlayFx(destroyedFx);*/

		SetToDelete();
	}

}

void Enemy::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}