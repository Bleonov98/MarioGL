#include "Bullet.h"

void Bullet::PlayAnimation()
{
	SetTexture(ResourceManager::GetTexture("bullet_" + std::to_string(frame)));

	if (animToggle) frame--;
	else frame++;

	if (frame == 0 || frame == 3) animToggle = !animToggle; // change from 0 to 2 and back
}

void Bullet::Move()
{
}


