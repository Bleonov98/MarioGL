#include "Plant.h"

void Plant::Sprout(float dt)
{
	if (position.y > startPos.y - size.y) {
		vertSpeed = 0;
		position.y -= speed * dt;
	}
	else isSprouted = true;
}

void Plant::Move(float dt)
{
	if (direction == DIR_RIGHT) position.x += speed * dt;
	else if (direction == DIR_LEFT) position.x -= speed * dt;
}

void Plant::PlayAnimation()
{
	SetTexture(ResourceManager::GetTexture("plant_" + std::to_string(frame)));

	if (animToggle) frame--;
	else frame++;

	if (frame == 0 || frame == 3) animToggle = !animToggle; // change from 0 to 3 and back
}
