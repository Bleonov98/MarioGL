#ifndef BRICK_H
#define BRICK_H

#include "DynamicObject.h"

enum BrickType {
	COMMON,
	SOLID,
	INVISIBLE,
	MONEY
};

class Brick : public DynamicObject
{
public:

	Brick(glm::vec2 position, glm::vec2 size, BrickType type = COMMON, float speed = 50.0f, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : DynamicObject(position, size, speed, angle, color) {
		this->type = type, startPos = position;

		if (type == COMMON || type == MONEY) SetTexture(ResourceManager::GetTexture("brick"));
		else if (type == SOLID) SetTexture(ResourceManager::GetTexture("solid_1"));
	};

	void PlayAnimation() override;

	void Move(float dt) override;

	void Push(bool destroy);

	BrickType GetType() { return this->type; }
	bool IsMove() { return isMoving; }

private:

	BrickType type;
	bool isMoving = false, reached = false;
	glm::vec2 startPos;

};

#endif // !BRICK_H
