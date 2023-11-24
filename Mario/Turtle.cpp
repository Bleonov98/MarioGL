#include "Turtle.h"

void Turtle::Move(float dt)
{
	if (!hidden) {
		if (direction == DIR_LEFT) position.x -= speed * dt;
		else if (direction == DIR_RIGHT) position.x += speed * dt;
	}
}

void Turtle::Hide()
{
	SetTexture(ResourceManager::GetTexture("turtle_hidden"));
	StopAnimation();
	hidden = true;
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
	angle = 180.0f;

	position.y -= 10.0f;
}

void Turtle::DeathAnimation(float dt, glm::vec2 screenPos, float height)
{
}
