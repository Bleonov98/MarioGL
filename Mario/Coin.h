#pragma once
#include "DynamicObject.h"
class Coin : public DynamicObject
{
public:
	Coin(glm::vec2 position, glm::vec2 size, float speed = 100.0f, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : DynamicObject(position, size, speed, angle, color) {
		startPos = position;
	}

	void PlayAnimation() override;

	void FlipAnimation();

	void Move(float dt) override;

	virtual ~Coin() {}

private:

	bool isMoving = false, reached = false, madeOnce = false;
	glm::vec2 startPos;
};

