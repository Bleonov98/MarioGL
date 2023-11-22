#pragma once
#include "DynamicObject.h"
class Star : public DynamicObject
{
public:
	Star(glm::vec2 position, glm::vec2 size, bool animated, float speed = 400.0f, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : DynamicObject(position, size, animated, speed, angle, color) 
	{
		this->startPos = position;
		this->direction = DIR_RIGHT;

		SetTexture(ResourceManager::GetTexture("star_0"));
	};

	void PlayAnimation() override;

	void Sprout(float dt);
	bool IsSprouted() { return isSprouted; }
	
	void Move(float dt);

private:

	glm::vec2 startPos;
	bool isSprouted = false;
	float bounceStrength = 600.0f;

};

