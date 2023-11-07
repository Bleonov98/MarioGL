#ifndef CHARACTER_H
#define CHARACTER_H

#include "DynamicObject.h"

class Person : public DynamicObject
{
public:
	Person(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : DynamicObject(position, size, speed, angle, color) {};

	virtual void PlayAnimation() = 0;

	void Death() { isDead = true; }
	virtual void DeathAnimation(glm::vec2 screenPos, float height) = 0;

	bool IsDead() { return isDead; }

private:

	bool isDead = false;

};

#endif // !CHARACTER_H