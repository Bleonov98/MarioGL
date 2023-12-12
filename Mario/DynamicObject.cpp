#include "DynamicObject.h"

void DynamicObject::Drop(float dt) 
{
	if (isOnGround) vertSpeed = 0.0f;
	else {
		vertSpeed += gravity * dt;
		position.y += vertSpeed * dt;
	}
}

bool DynamicObject::ProcessGroundCollision(GameObject& two)
{
	if (skipCollision) return false;

	if (GroundCollision(two) && vertSpeed >= 0) { 
		position.y = two.GetPos().y - size.y;
		isOnGround = true;
		vertSpeed = speed;
	}
	else isOnGround = false;

	return isOnGround;
}

bool DynamicObject::ProcessSideCollision(GameObject& two)
{
	if (skipCollision) return false;

	if (LeftCollision(two)) {
		position.x = two.GetPos().x + two.GetSize().x + 0.5f;
		return true;
	}
	else if (RightCollision(two)) {
		position.x = two.GetPos().x - size.x - 0.5f;
		return true;
	}
	return false;
}

bool DynamicObject::AnimationPlayed(float dt)
{
	animationTime += dt;
	if (animationTime >= swapTime) {
		animationTime = 0.0f;
		return true;
	}
	return false;
}
