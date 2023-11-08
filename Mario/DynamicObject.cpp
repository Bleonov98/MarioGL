#include "DynamicObject.h"

void DynamicObject::Drop(bool isOnGround)
{
	if (isOnGround) vertSpeed = 0.0f;
	else {
		vertSpeed += gravity;
		position.y += vertSpeed;
	}
}

bool DynamicObject::AnimationPlayed(float dt)
{
	animationTime += dt;
	if (animationTime >= 0.4f) {
		animationTime = 0.0f;
		return true;
	}
	return false;
}
