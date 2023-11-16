#ifndef BULLET_H
#define BULLET_H

#include "DynamicObject.h"
class Bullet : public DynamicObject
{
public:
	Bullet(glm::vec2 position, glm::vec2 size, bool animated = false, float speed = 0.0f, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : DynamicObject(position, size, animated, speed, angle, color) {}

	void Move();
	void PlayAnimation() override;

private:



};

#endif // !BULLET_H