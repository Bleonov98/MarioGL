#include "Mario.h"

// actions - - - - - - - - - - - - - - - - - - - -
void Mario::Action(float dt, MoveDirection direction)
{
	if (isDead) return;

	if (lastDir != direction) restartAnim = true;
	else restartAnim = false;

	if (direction != DUCK && ducked) {
		ducked = false;

		float prevSizeY = size.y;
		size.y *= 1.6f;
		position.y -= size.y - prevSizeY;
	}

	if (direction == STAND || direction == DUCK) {
		const std::string standDirection = (lastDir == DIR_RIGHT) ? "_right_stand" : "_left_stand";
		const std::string duckDirection = (lastDir == DIR_RIGHT) ? "_right_duck" : "_left_duck";
		
		if (direction == STAND && isOnGround) SetTexture(ResourceManager::GetTexture(GetSprite() + standDirection));
		else if (direction == DUCK && isOnGround && type >= BIG) {
			SetTexture(ResourceManager::GetTexture(GetSprite() + duckDirection));

			if (!ducked) {
				ducked = true;
				
				float prevSizeY = size.y;
				size.y /= 1.6f;
				position.y -= size.y - prevSizeY;
			}
		}

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
	if (isDead) return;

	SetTexture(ResourceManager::GetTexture("mario_death"));
	life--;
	isDead = true;
	skipCollision = true;
	isOnGround = false;

	vertSpeed = -jumpStrength;
}

void Mario::Spawn()
{
	position = glm::vec2(100.0f, 600.0f);

	isDead = false;
	skipCollision = false;
	isOnGround = false;
	vertSpeed = 0.0f;
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

		float prevSizeY = size.y;
		size.y *= 1.6f;
		position.y -= size.y - prevSizeY;

		type++;
	}
	else if (type == BIG) type++, ammo = 2;
}

void Mario::Hit()
{
	if (hitDelay) return;

	if (type == LITTLE) Death();
	else {
		type = LITTLE;
		ammo = 0;
		size.y /= 1.6f;

		hitDelay = true;
		std::thread hitDelayTimer([&]()
		{
			std::this_thread::sleep_for(std::chrono::seconds(2));
			this->hitDelay = false;
		});
		hitDelayTimer.detach();
	}
}

void Mario::Immortal()
{
	isImmortal = true;
	this->color = glm::vec3(1.0f, 0.5f, 0.5f);

	std::thread immortalDelay([&]() {
		std::this_thread::sleep_for(std::chrono::seconds(10));
		this->color = glm::vec3(1.0f);
		isImmortal = false;
	});
	immortalDelay.detach();
}

void Mario::CollectCoin()
{
	score += 200;
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
