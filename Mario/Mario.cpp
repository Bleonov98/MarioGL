#include "Mario.h"

// actions - - - - - - - - - - - - - - - - - - - -
void Mario::Move(float dt, MarioAction direction)
{
	if (lastDir != direction) restartAnim = true;
	else restartAnim = false;

	if (direction == STAND || (direction == DUCK && type >= BIG)) {
		const std::string standDirection = (lastDir == MOVERIGHT) ? "_right_stand" : "_left_stand";
		const std::string duckDirection = (lastDir == MOVERIGHT) ? "_right_duck" : "_left_duck";
		
		if (direction == STAND) SetTexture(ResourceManager::GetTexture(GetSprite() + standDirection));
		else if (direction == DUCK) SetTexture(ResourceManager::GetTexture(GetSprite() + duckDirection)); // -> add resize

		if (inertia > 0.0f) {
			inertia -= 1.5f;
			if (inertia < 0.0f) inertia = 0.0f;
		}

		if (lastDir == MOVERIGHT) {
			position.x += inertia * dt;
		}
		else if (lastDir == MOVELEFT) {
			position.x -= inertia * dt;
		}
	}
	else if (direction == MOVELEFT || direction == MOVERIGHT) {
		if (inertia < 600.0f) inertia += 0.5f;
		lastDir = direction;

		if (direction == MOVELEFT) {
			position.x -= speed * dt;
		}
		else if (direction == MOVERIGHT) {
			position.x += speed * dt;
		}
	}


	animationTime += dt;
	if (animationTime >= 0.1f) {
		PlayAnimation();
		animationTime = 0.0f;
	}
}

void Mario::Jump(float dt)
{
}

// animations - - - - - - - - - - - - - - - - - - - - - - -
void Mario::PlayAnimation()
{
	if (!restartAnim && lastDir == MOVELEFT) SetTexture(ResourceManager::GetTexture(GetSprite() + "_left_" + std::to_string(frame)));
	else if (!restartAnim && lastDir == MOVERIGHT) SetTexture(ResourceManager::GetTexture(GetSprite() + "_right_" + std::to_string(frame)));
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

// items, collisions - - - - - - - - - - - - - - - - - - - -
void Mario::Upgrade()
{
	if (type == LITTLE) {
		size.y *= 2.0f;
		type++;
	}
	else if (type == BIG) type++;
}

void Mario::Hit()
{
	if (type == LITTLE) Death();
	else type = LITTLE;
}

void Mario::CollectCoin()
{
	if (coins >= 100) life++, coins = 0;
	else coins++;
}

// tools  - - - - - - - - - - - - - - - - - - - - - - - -
std::string Mario::GetSprite()
{
	if (type == LITTLE) return marioType = "mario";
	else if (type == BIG) return marioType = "big";
	else if (type == CHIEF) return marioType = "chief";
}
