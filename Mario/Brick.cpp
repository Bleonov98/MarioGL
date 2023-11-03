#include "Brick.h"

void Brick::PlayAnimation()
{
	SetTexture(ResourceManager::GetTexture("solid_" + std::to_string(frame)));

	if (frame < 2) frame++;
	else frame = 0;
}

void Brick::Move(float dt)
{
	if (position.y > position.y - size.y / 2.0f && !reached) position.y -= speed * dt;
	else if (position.y <= position.y - size.y / 2.0f) reached = true;
	else if (position.y <= startPos.y && reached) position.y += speed * dt;
	else if (position.y >= startPos.y && reached) {
		position.y = startPos.y;
		reached = false, isMoving = false;
	}
}

void Brick::Push(bool destroy)
{
	if (type == COMMON && !destroy) isMoving = true;
	else if (type == COMMON && destroy) {
		if (position.y > 900.0f) SetTexture(ResourceManager::GetTexture("destroyed_brick_under"));
		else SetTexture(ResourceManager::GetTexture("destroyed_brick"));
		DeleteObject();
	}
	else if (type == INVISIBLE) SetTexture(ResourceManager::GetTexture("destroyed_solid"));
	else if (type == MONEY) {
		isMoving = true;
		if (coins > 0) coins--;
		else SetTexture(ResourceManager::GetTexture("destroyed_solid"));
	}
}
