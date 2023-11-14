#include "Brick.h"

void Brick::PlayAnimation()
{
	SetTexture(ResourceManager::GetTexture("solid_" + std::to_string(frame)));

	if (animToggle) frame--;
	else frame++;

	if (frame == 0 || frame == 2) animToggle = !animToggle;
}

void Brick::DestroyAnimation(float dt)
{
	animationTime += dt;
	if (animationTime >= 0.11f) DeleteObject();
}

void Brick::Move(float dt)
{
	if (position.y > startPos.y - size.y / 2.0f && !reached) position.y -= speed * dt;
	else if (position.y <= startPos.y - size.y / 2.0f && !reached) reached = true;
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
		if (underGround) SetTexture(ResourceManager::GetTexture("destroyed_underbrick"));
		else SetTexture(ResourceManager::GetTexture("destroyed_brick"));
		destroyed = true;
	}
	else if (type == INVISIBLE) {
		type = SOLID;
		SetTexture(ResourceManager::GetTexture("destroyed_solid"));
	}
	else if (type == SOLID) {
		animated = false;
		SetTexture(ResourceManager::GetTexture("destroyed_solid"));
	}
	else if (type == MONEY) {
		isMoving = true;
		if (coins > 0) coins--;
		else SetTexture(ResourceManager::GetTexture("destroyed_solid"));
	}
}
