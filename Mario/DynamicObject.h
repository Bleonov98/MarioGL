#ifndef DYNAMIC_H
#define DYNAMIC_H

#include "GameObject.h"
#include "ResourceManager.h"

class DynamicObject : public GameObject
{
public:

	DynamicObject(glm::vec2 position, glm::vec2 size, bool animated = false, float speed = 0.0f, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : GameObject(position, size, angle, color) {
		this->speed = speed, this->animated = animated;
	};

	virtual void PlayAnimation() = 0;
	void StopAnimation() { animated = false; }
	bool AnimationPlayed(float dt);

	void Drop(float dt);
	bool ProcessGroundCollision(GameObject& two);
	bool ProcessSideCollision(GameObject& two);

	bool IsAnimated() { return animated; }
	bool IsOnGround() { return isOnGround; }
	float GetSpeed() { return speed; }

	virtual ~DynamicObject() {}

protected:

	float speed, gravity = 1.8f, vertSpeed = 0.0f, animationTime = 0.0f;
	int frame = 0;
	bool animToggle = false, isOnGround = false, animated = false;
};

#endif // !DYNAMIC_H


