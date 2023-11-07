#ifndef BRICK_H
#define BRICK_H

#include "DynamicObject.h"

enum BrickType {
	COMMON,
	SOLID,
	INVISIBLE,
	MONEY
};

enum BrickBonus {
	NONE,
	COIN,
	UPGRADE,
	LIFE,
	STAR
};

class Brick : public DynamicObject
{
public:

	Brick(glm::vec2 position, glm::vec2 size, BrickType type = COMMON, BrickBonus bonus = NONE, float speed = 100.0f, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : DynamicObject(position, size, speed, angle, color) {
		this->type = type, this->bonus = bonus, startPos = position;

		if (type == COMMON || type == MONEY) {
			if (position.y > 900.0f) SetTexture(ResourceManager::GetTexture("underbrick"));
			else SetTexture(ResourceManager::GetTexture("brick"));
		}
		else if (type == INVISIBLE) SetTexture(ResourceManager::GetTexture("test"));

		if (type == MONEY) bonus = COIN;
	};

	void PlayAnimation() override;

	void Move(float dt);

	void Push(bool destroy);

	BrickType GetType() { return this->type; }
	BrickBonus GetBonusType() { return this->bonus; }
	bool IsMove() { return isMoving; }

	virtual ~Brick() {}

private:

	BrickType type;
	BrickBonus bonus;

	bool isMoving = false, reached = false;
	int coins = 10;
	glm::vec2 startPos;

};

#endif // !BRICK_H
