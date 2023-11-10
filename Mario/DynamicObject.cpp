#include "DynamicObject.h"

void DynamicObject::Drop(float dt)
{
	if (isOnGround) vertSpeed = 10.0f;
	else {
		vertSpeed += gravity;
		position.y += vertSpeed * dt;
	}
}

bool DynamicObject::ProccesGroundCollision(GameObject& two)
{
	if (GroundCollision(two)) { 
		position.y = two.GetPos().y - size.y;
		isOnGround = true;
		vertSpeed = speed;
	}
	else isOnGround = false;

	return isOnGround;
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
