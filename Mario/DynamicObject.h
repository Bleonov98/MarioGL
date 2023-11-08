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

	void Drop(bool isOnGround);
	bool GroundCollision(AABB& one, AABB& two) { return hBox.IntersectSide(one.GetSide(BOTTOM), two.GetSide(TOP)); };

	float GetSpeed() { return speed; }
	bool AnimationPlayed(float dt);

	virtual ~DynamicObject() {}

protected:

	float speed, gravity = 0.5f, vertSpeed = 0.0f, animationTime = 0.0f;
	int frame = 0;
	bool animToggle = false;

};

#endif // !DYNAMIC_H


