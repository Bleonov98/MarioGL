#ifndef MARIO_H
#define MARIO_H

#include "Person.h"

enum MarioAction {
	STAND,
	MOVELEFT,
	MOVERIGHT,
	DUCK
};

enum MarioType {
	LITTLE,
	BIG,
	CHIEF
};

class Mario : public Person
{
public:

	Mario(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : Person(position, size, speed, angle, color) {
		startSize = size;
	};

	void CollectCoin();
	int GetCoins() { return coins; }

	void Move(float dt, MarioAction direction);
	void Jump(float dt);
	void Fire();

	void PlayAnimation() override;
	void DeathAnimation(glm::vec2 screenPos, float height) override;
	std::string GetSprite();

	void Upgrade();
	void Hit();
	
private:

	std::string marioType;
	glm::vec2 startSize;

	int type = BIG, coins = 0, life = 3;
	float inertia = 0.0f;

	MarioAction lastDir = MOVERIGHT;
	bool restartAnim = false;
};

#endif // !MARIO_H