#include "Brick.h"

void Brick::PlayAnimation()
{
	SetTexture(ResourceManager::GetTexture("solid_" + std::to_string(frame)));

	if (frame < 3) frame++;
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
		SetTexture(ResourceManager::GetTexture("destroyed"));
		DeleteObject();
	}
}
