#pragma once
#include "Person.h"
class Goomba : public Person
{
public:
	
	Goomba(glm::vec2 position, glm::vec2 size, bool animated = false, float speed = 100.0f, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : Person(position, size, animated, speed, angle, color) {
		this->direction = DIR_LEFT;
		SetTexture(ResourceManager::GetTexture("goomba_0"));
	};

	void Move(float dt);

	void PlayAnimation() override;

	void Death() override;
	void DeathAnimation(float dt, glm::vec2 screenPos, float height) override;

private:

	bool textureChanged = false;

};

