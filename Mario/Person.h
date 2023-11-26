#ifndef PERSON_H
#define PERSON_H

#include "DynamicObject.h"

class Person : public DynamicObject
{
public:
	Person(glm::vec2 position, glm::vec2 size, bool animated = false, float speed = 100.0f, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : DynamicObject(position, size, animated, speed, angle, color) {};

	virtual void PlayAnimation() = 0;

	virtual void Death() = 0;

	bool IsDead() { return isDead; }

protected:

	bool isDead = false;

};

#endif // !PERSON_H