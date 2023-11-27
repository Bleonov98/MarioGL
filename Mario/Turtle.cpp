#include "Turtle.h"

void Turtle::Move(float dt, bool appear)
{
	if (!isAppear) {
		isAppear = appear;
		return;
	}

	if (direction == DIR_LEFT) position.x -= speed * dt;
	else if (direction == DIR_RIGHT) position.x += speed * dt;
}

void Turtle::Hide()
{
	SetTexture(ResourceManager::GetTexture("turtle_hidden"));
	StopAnimation(); 
	hidden = true;
	speed += 400.0f;
	direction = STAND;
}

void Turtle::PlayAnimation()
{
	if (lastDir != direction) animToggle = 0;
	lastDir = direction;

	if (direction == DIR_LEFT) {
		SetTexture(ResourceManager::GetTexture("turtle_left_" + std::to_string(frame)));

		if (animToggle) frame--;
		else frame++;

		if (frame == 0 || frame == 1) animToggle = !animToggle; // change from 0 to 1 and back 
	}
	else if (direction == DIR_RIGHT) {
		SetTexture(ResourceManager::GetTexture("turtle_right_" + std::to_string(frame)));

		if (animToggle) frame--;
		else frame++;

		if (frame == 0 || frame == 1) animToggle = !animToggle; // change from 0 to 1 and back 
	}
}

void Turtle::Death()
{
	isDead = true;
	skipCollision = true;
	isOnGround = false;

	angle = 180.0f;
	vertSpeed = -400.0f;
}
