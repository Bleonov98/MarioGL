#ifndef COIN_H
#define COIN_H

#include "DynamicObject.h"

enum CoinType {
	COIN_REGULAR,
	COIN_BRICK
};

class Coin : public DynamicObject
{
public:
	Coin(glm::vec2 position, glm::vec2 size, float speed = 100.0f, bool animated = false, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : DynamicObject(position, size, speed, animated, angle, color) {
		startPos = position;
	}

	void PlayAnimation() override;

	void FlipAnimation();

	void Move(float dt);

	void SetCoinType(CoinType coinType) { this->coinType = coinType; }
	CoinType GetCoinType() { return this->coinType; }

	virtual ~Coin() {}

private:

	CoinType coinType = COIN_REGULAR;
	bool isMoving = false, reached = false, madeOnce = false;
	glm::vec2 startPos;
};

#endif // !COIN_H