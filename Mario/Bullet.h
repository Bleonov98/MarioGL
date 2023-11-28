#ifndef BULLET_H
#define BULLET_H

#include "DynamicObject.h"
class Bullet : public DynamicObject
{
public:
	Bullet(glm::vec2 position, glm::vec2 size, MoveDirection direction, bool animated = false, float speed = 0.0f, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : DynamicObject(position, size, animated, speed, angle, color) {
		this->direction = direction;
		
		SetTexture(ResourceManager::GetTexture("bullet_0"));
		swapTime = 0.1f;
	}

	void Move(float dt);
	void Bounce();

	void PlayAnimation() override;

private:

	int bounceCnt = 2;
	float bounceStrength = 400.0f;

};

#endif // !BULLET_H