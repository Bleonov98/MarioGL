#include "Mario.h"

// actions - - - - - - - - - - - - - - - - - - - -
void Mario::Action(float dt, MoveDirection direction)
{
	if (lastDir != direction) restartAnim = true;
	else restartAnim = false;

	if (direction == STAND || (direction == DUCK && type >= BIG)) {
		const std::string standDirection = (lastDir == DIR_RIGHT) ? "_right_stand" : "_left_stand";
		const std::string duckDirection = (lastDir == DIR_RIGHT) ? "_right_duck" : "_left_duck";
		
		if (direction == STAND && isOnGround) SetTexture(ResourceManager::GetTexture(GetSprite() + standDirection));
		else if (direction == DUCK && isOnGround) SetTexture(ResourceManager::GetTexture(GetSprite() + duckDirection)); // -> add resize

		if (inertia > 0.0f) {
			inertia -= 1.1f;
			if (inertia < 0.0f) inertia = 0.0f;
		}

		if (lastDir == DIR_RIGHT) {
			position.x += inertia * dt;
		}
		else if (lastDir == DIR_LEFT) {
			position.x -= inertia * dt;
		}
	}
	else if (direction == DIR_LEFT || direction == DIR_RIGHT) {
		if (inertia < 400.0f) inertia += 0.25f;

		if (lastDir != direction) inertia = 0.0f;
		lastDir = direction;

		if (direction == DIR_LEFT) {
			position.x -= (speed + inertia) * dt;
		}
		else if (direction == DIR_RIGHT) {
			position.x += (speed + inertia) * dt;
		}
	}

	animationTime += dt;
	if (animationTime >= 0.1f) {
		PlayAnimation();
		animationTime = 0.0f;
	}
}

void Mario::Jump(float dt, bool processed)
{
	if (isOnGround && !processed) {
		vertSpeed = -jumpStrength;
		position.y -= 5.0f;
	}
	else if (!isOnGround) {
		vertSpeed -= gravity / 3.0f;

		if (lastDir == DIR_LEFT) SetTexture(ResourceManager::GetTexture(GetSprite() + "_left_jump"));
		else if (lastDir == DIR_RIGHT) SetTexture(ResourceManager::GetTexture(GetSprite() + "_right_jump"));
	}
}

void Mario::Reload(std::vector<Bullet*> bullets)
{
	for (auto i : bullets)
	{
		if (i->IsDeleted()) ammo++;
	}
}

// animations - - - - - - - - - - - - - - - - - - - - - - -
void Mario::PlayAnimation()
{
	if (!restartAnim && lastDir == DIR_LEFT && isOnGround) SetTexture(ResourceManager::GetTexture(GetSprite() + "_left_" + std::to_string(frame)));
	else if (!restartAnim && lastDir == DIR_RIGHT && isOnGround) SetTexture(ResourceManager::GetTexture(GetSprite() + "_right_" + std::to_string(frame)));
	else if (restartAnim) {
		animToggle = false;
		frame = 0;
		return;
	}

	if (animToggle) frame--;
	else frame++;

	if (frame == 0 || frame == 2) animToggle = !animToggle; // change from 0 to 2 and back
}

void Mario::Death() 
{
	SetTexture(ResourceManager::GetTexture("mario_death"));
	isDead = true;
	skipCollision = true;
	isOnGround = false;

	vertSpeed = -jumpStrength / 2.0f;
}

bool Mario::ProcessTopCollision(GameObject& two)
{
	if (skipCollision) return false;

	if (TopCollision(two) && vertSpeed < 0.0f) {
		vertSpeed = 250.0f;
		return true;
	}
	else return false;
}

bool Mario::ProcessKillCollision(GameObject& two)
{
	if (skipCollision) return false;

	if (GroundCollision(two) && vertSpeed >= 0) {
		vertSpeed = -jumpStrength / 2.0f;
		return true;
	}
	else return false;
}

// items, collisions - - - - - - - - - - - - - - - - - - - -
void Mario::Upgrade()
{
	score += 1000;

	if (type == LITTLE) {
		size.y *= 2.0f;
		type++;
	}
	else if (type == BIG) type++;
	else if (type == CHIEF) ammo = 2;
}

void Mario::Hit()
{
	if (type == LITTLE) Death();
	else {
		type = LITTLE;
		ammo = 0;
	}
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
