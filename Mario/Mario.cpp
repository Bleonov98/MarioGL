#include "Mario.h"

void Mario::Move(float dt, MarioDirection direction)
{
	if (lastDir != direction) restartAnim = true;
	else restartAnim = false;

	if (direction == STAND) {
		if (lastDir == MOVERIGHT) SetTexture(ResourceManager::GetTexture("mario_right_stand"));
		else if (lastDir == MOVELEFT) SetTexture(ResourceManager::GetTexture("mario_left_stand"));
	}
	else if (direction == MOVELEFT) {
		position.x -= speed * dt;
		lastDir = direction;
	}
	else if (direction == MOVERIGHT) {
		position.x += speed * dt;
		lastDir = direction;
	}
	else if (direction == DUCK && type == BIG) {
		// texture duck and -size, last direction
	}

	PlayAnimation();
}

void Mario::PlayAnimation()
{
	if (!restartAnim && lastDir == MOVELEFT) SetTexture(ResourceManager::GetTexture("mario_left_" + std::to_string(frame)));
	else if (!restartAnim && lastDir == MOVERIGHT) SetTexture(ResourceManager::GetTexture("mario_right_" + std::to_string(frame)));
	else if (restartAnim) {
		animToggle = false;
		frame = 0;
		return;
	}

	if (animToggle) frame--;
	else frame++;

	if (frame == 0 || frame == 2) animToggle = !animToggle; // change from 0 to 2 and back
}

void Mario::DeathAnimation(glm::vec2 screenPos, float height)
{
}
