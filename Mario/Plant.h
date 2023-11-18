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
	};

	void Arise(float dt);
	void Move(float dt);

	void PlayAnimation() override;

	void SetMushroomType(PlantType plantType) { this->plantType = plantType; }
	PlantType GetMushroomType() { return this->plantType; }

private:

	PlantType plantType;

};

#endif // !PLANT_H