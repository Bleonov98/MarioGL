#pragma once
#include "Person.h"
class Goomba : public Person
{
public:
	
	Goomba(glm::vec2 position, glm::vec2 size, float speed, bool animated = false, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : Person(position, size, speed, animated, angle, color) {
		SetTexture(ResourceManager::GetTexture("goomba_left_0"));
	};

	void Move(float dt);

	void PlayAnimation() override;
	void DeathAnimation(float dt, glm::vec2 screenPos, float height) override;

private:

	bool textureChanged = false;

};

