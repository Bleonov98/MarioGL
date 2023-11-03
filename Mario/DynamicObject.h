#ifndef DYNAMIC_H
#define DYNAMIC_H

#include "GameObject.h"
#include "ResourceManager.h"

class DynamicObject : public GameObject
{
public:

	DynamicObject(glm::vec2 position, glm::vec2 size, float speed = 0.0f, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : GameObject(position, size, angle, color) {
		this->speed = speed;
	};

	virtual void PlayAnimation() = 0;

	virtual void Move(float dt) = 0;

	float GetSpeed() { return speed; }

	virtual ~DynamicObject() {}

protected:

	float speed;
	int frame = 0;

};

#endif // !DYNAMIC_H


