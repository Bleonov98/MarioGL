#include "DynamicObject.h"

void DynamicObject::Drop(float dt)
{
	if (isOnGround) vertSpeed = 0.0f;
	else {
		if (vertSpeed <= 1500.0f) vertSpeed += gravity;
		position.y += vertSpeed * dt;
	}
}

bool DynamicObject::ProcessGroundCollision(GameObject& two)
{
	if (SideCollision(two, BOTTOM)) { 
		position.y = two.GetPos().y - size.y;
		isOnGround = true;
		vertSpeed = speed;
	}
	else isOnGround = false;

	return isOnGround;
}

bool DynamicObject::ProcessSideCollision(GameObject& two)
{
	if (SideCollision(two, LEFT)) {
		position.x = two.GetPos().x + two.GetSize().x + 0.1f;
		return true;
	}
	else if (SideCollision(two, RIGHT)) {
		position.x = two.GetPos().x - size.x - 0.1f;
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
