#ifndef MARIO_H
#define MARIO_H

#include "Person.h"
#include "Bullet.h"

enum MarioType {
	LITTLE,
	BIG,
	CHIEF
};

class Mario : public Person
{
public:

	Mario(glm::vec2 position, glm::vec2 size, float speed, bool animated = false, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : Person(position, size, speed, animated, angle, color) {
		startSize = size, startSpeed = speed;
	};

	// items interactions
	void CollectCoin();
	void CollectLife() { this->life++, score += 1000; }
	void AddScore(int score) { this->score += score; }
	void Upgrade();
	void Hit();
	void Immortal();

	int GetCoins() { return this->coins; }
	int GetScore() { return this->score; }
	int GetLifes() { return this->life; }
	bool HitDelay() { return this->hitDelay; }
	bool IsImmortal() { return this->isImmortal; }

	// movement, animation
	void Action(float dt, MoveDirection direction);
	void Jump(float dt, bool processed);

	bool IsReload() { return ammo > 0; }
	void Reload(std::vector<Bullet*> bullets);
	void Fire() { if (ammo > 0) ammo--; }
	MoveDirection GetLastDirection() { return lastDir; }

	void Accelerate(bool pressed) {
		if (pressed) speed = startSpeed + 120.0f;
		else speed = startSpeed;
	}
	float GetInertia() { return this->inertia; }

	void PlayAnimation() override;
	void PlayEndAnimation(float dt);

	void Death() override;
	void Spawn();

	bool ProcessTopCollision(GameObject& two);
	bool ProcessKillCollision(GameObject& two);

	// types and actions
	std::string GetSprite();
	int GetMarioType() { return this->type; }
	
private:

	std::string marioType;
	glm::vec2 startSize;

	int type = LITTLE, coins = 0, life = 3, score = 0, ammo = 0;
	float inertia = 0.0f, jumpStrength = 1000.0f, startSpeed;

	MoveDirection lastDir = DIR_RIGHT;
	bool restartAnim = false, isImmortal = false, hitDelay = false, ducked = false;
};

#endif // !MARIO_H