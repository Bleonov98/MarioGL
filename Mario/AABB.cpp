#include "AABB.h"

spriteSide AABB::GetSide(Side side)
{
    spriteSide sidePair;

    if (side == TOP) sidePair = std::make_pair(min, glm::vec2(max.x, min.y));
    if (side == RIGHT) sidePair = std::make_pair(glm::vec2(max.x, min.y), max);
    if (side == BOTTOM) sidePair = std::make_pair(glm::vec2(min.x, max.y), max);
    if (side == LEFT) sidePair = std::make_pair(min, glm::vec2(min.x, max.y));

    return sidePair;
}