#ifndef MARIO_H
#define MARIO_H

#include "Person.h"

enum MarioAction {
	STAND,
	MOVELEFT,
	MOVERIGHT,
	DUCK,
	JUMP
};

enum MarioType {
	LITTLE,
	BIG,
	CHIEF
};

class Mario : public Person
{
public:

	Mario(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : Person(position, size, speed, angle, color) {};

	void Move(float dt, MarioAction direction);
	void Jump(float dt);
	void Fire();

	void PlayAnimation() override;
	void DeathAnimation(glm::vec2 screenPos, float height) override;
	
	void Upgrade();
	void Hit();
	
private:

	MarioType type = LITTLE;
	MarioAction lastDir = MOVERIGHT;

	float inertia = 0.0f;

	bool restartAnim = false;
};

#endif // !MARIO_H