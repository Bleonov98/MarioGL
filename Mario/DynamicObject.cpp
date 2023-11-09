#include "DynamicObject.h"

void DynamicObject::Drop(float dt, bool isOnGround)
{
	if (isOnGround) vertSpeed = 5.0f;
	else {
		vertSpeed += gravity;
		position.y += vertSpeed * dt;
		this->isOnGround = false;
	}
}

bool DynamicObject::GroundCollision(GameObject& two)
{
	if (hBox.IntersectGround(two.GetSpriteSide(TOP))) { // -> change 
		position.y = two.GetSpriteSide(TOP).first.y - size.y;
		isOnGround = true;
		return true; 
	}
	return false;
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
