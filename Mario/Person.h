#ifndef PERSON_H
#define PERSON_H

#include "DynamicObject.h"

class Person : public DynamicObject
{
public:
	Person(glm::vec2 position, glm::vec2 size, float speed, bool animated = false, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : DynamicObject(position, size, speed, animated, angle, color) {};

	virtual void PlayAnimation() = 0;

	void Death() { isDead = true; }
	virtual void DeathAnimation(float dt, glm::vec2 screenPos, float height) = 0;

	bool IsDead() { return isDead; }

private:

	bool isDead = false;

};

#endif // !PERSON_H