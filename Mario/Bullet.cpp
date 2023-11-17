#include "Bullet.h"

void Bullet::PlayAnimation()
{
	SetTexture(ResourceManager::GetTexture("bullet_" + std::to_string(frame)));

	if (animToggle) frame--;
	else frame++;

	if (frame == 0 || frame == 3) animToggle = !animToggle; // change from 0 to 3 and back
}

void Bullet::Move(float dt)
{
	if (direction == DIR_RIGHT) position.x += speed * dt;
	else if (direction == DIR_LEFT) position.x -= speed * dt;

	if (isOnGround) Bounce();
}

void Bullet::Bounce()
{
	if (bounceCnt > 0) {
		bounceCnt--;

		vertSpeed = -bounceStrength;
	}
	else DeleteObject();
}


