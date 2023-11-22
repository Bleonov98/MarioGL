#ifndef PLANT_H
#define PLANT_H

enum PlantType {
	MUSHROOM_UPGRADE,
	MUSHROOM_LIFE,
	PLANT_UPGRADE
};

#include "DynamicObject.h"
class Plant : public DynamicObject
{
public:

	Plant(glm::vec2 position, glm::vec2 size, PlantType type, bool animated = false, float speed = 0.0f, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f))
		: DynamicObject(position, size, animated, speed, angle, color) 
	{
		this->plantType = type;
		this->startPos = position;
		this->direction = DIR_RIGHT;

		if (type == MUSHROOM_UPGRADE) SetTexture(ResourceManager::GetTexture("mushroom_upgrade"));
		else if (type == MUSHROOM_LIFE) SetTexture(ResourceManager::GetTexture("mushroom_life"));
		else SetTexture(ResourceManager::GetTexture("plant_0"));
	};

	void Sprout(float dt);
	bool IsSprouted() { return isSprouted; }

	void Move(float dt);

	void PlayAnimation() override;

	void SetMushroomType(PlantType plantType) { this->plantType = plantType; }
	PlantType GetPlantType() { return this->plantType; }

private:

	glm::vec2 startPos;
	PlantType plantType;
	bool isSprouted = false;

};

#endif // !PLANT_H