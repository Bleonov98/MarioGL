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

	Brick(glm::vec2 position, glm::vec2 size, BrickType type = COMMON, BrickBonus bonus = NONE, bool animated = false, float speed = 300.0f, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) 
		: DynamicObject(position, size, animated, speed, angle, color) 
	{
		this->type = type, this->bonus = bonus, startPos = position;

		if (position.y > 900.0f) underGround = true;

		if (type == COMMON || type == MONEY) {
			if (underGround) SetTexture(ResourceManager::GetTexture("underbrick"));
			else SetTexture(ResourceManager::GetTexture("brick"));
		}
		else if (type == INVISIBLE) SetTexture(ResourceManager::GetTexture("test"));

		if (type == MONEY) bonus = COIN;
	};

	// animations
	void PlayAnimation() override;
	void DestroyAnimation(float dt);

	// movement
	void Move(float dt);
	void Push(bool destroy);

	// Get
	BrickType GetType() { return this->type; }
	BrickBonus GetBonusType() { return this->bonus; }
	bool IsMoving() { return isMoving; }
	bool IsDestroyed() { return destroyed; }

	virtual ~Brick() {}

private:

	BrickType type;
	BrickBonus bonus;

	bool isMoving = false, reached = false, underGround = false, destroyed = false;
	int coins = 10;
	glm::vec2 startPos;

};

#endif // !BRICK_H
