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
	int GetCoins() { return this->coins; }
	int GetScore() { return this->score; }

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
	
	void Death() override;

	bool ProcessTopCollision(GameObject& two);
	bool ProcessKillCollision(GameObject& two);

	// types and actions
	std::string GetSprite();
	int GetMarioType() { return this->type; }

	void Upgrade();
	void Hit();
	
private:

	std::string marioType;
	glm::vec2 startSize;

	int type = LITTLE, coins = 0, life = 3, score = 0, ammo = 2;
	float inertia = 0.0f, jumpStrength = 900.0f, startSpeed;

	MoveDirection lastDir = DIR_RIGHT;
	bool restartAnim = false;
};

#endif // !MARIO_H