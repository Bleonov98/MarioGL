#include "Goomba.h"

void Goomba::Move(float dt, bool appear)
{
	if (!isAppear) {
		isAppear = appear;
		return;
	}

	if (direction == DIR_LEFT) position.x -= speed * dt;
	else if (direction == DIR_RIGHT) position.x += speed * dt;
}

void Goomba::PlayAnimation()
{
	SetTexture(ResourceManager::GetTexture("goomba_" + std::to_string(frame)));

	if (animToggle) frame--;
	else frame++;

	if (frame == 0 || frame == 1) animToggle = !animToggle; // change from 0 to 1 and back 
}

void Goomba::Death()
{
	isDead = true;
}

void Goomba::DeathAnimation(float dt)
{
	if (!textureChanged) {
		StopAnimation();
		SetTexture(ResourceManager::GetTexture("goomba_death"));
		textureChanged = true;
		animationTime = 0.0f;
	}
	
	animationTime += dt;
	if (animationTime >= 0.20f) DeleteObject();
}
