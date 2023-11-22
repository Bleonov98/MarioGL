#ifndef AABB_H
#define AABB_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

typedef std::pair<glm::vec2, glm::vec2> spriteSide;

enum Side {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

class AABB {
public:

    // general
    bool Intersects(const AABB& other) const {
        return (min.x <= other.max.x && max.x >= other.min.x &&
                min.y <= other.max.y && max.y >= other.min.y);
    }

    bool Intersects(const glm::vec2 otherPos, const glm::vec2 otherSize) const {
        return (min.x <= otherPos.x + otherSize.x && max.x >= otherPos.x &&
            min.y <= otherPos.y + otherSize.y && max.y >= otherPos.y);
    }

    bool IntersectPoint(const glm::vec2 point) const {
        return (min.x <= point.x && max.x >= point.x &&
            min.y <= point.y && max.y >= point.y);
    }

    // sides
    bool IntersectBottom(const AABB& other) {
        return (min.x <= other.max.x - 5.0f && max.x >= other.min.x + 5.0f &&
                max.y >= other.min.y && max.y <= other.min.y + 7.0f);
    }

    bool IntersectTop(const AABB& other) {
        return (min.x <= other.max.x - 5.0f && max.x >= other.min.x + 5.0f &&
                min.y <= other.max.y && min.y >= other.max.y - 7.0f);
    }

    bool IntersectLeft(const AABB& other) {
        return (min.x <= other.max.x && min.x >= other.max.x - 7.0f &&
                min.y <= other.max.y - 5.0f && max.y >= other.min.y + 5.0f);
    }
    
    bool IntersectRight(const AABB& other) {
        return (max.x <= other.min.x + 7.0f && max.x >= other.min.x &&
                min.y <= other.max.y - 5.0f && max.y >= other.min.y + 5.0f);
    }

    // basics
    void SetBorder(const glm::vec2& newMin, const glm::vec2& newMax) {
        min = newMin;
        max = newMax;
    }

    glm::vec2 GetMin() { return min; }
    glm::vec2 GetMax() { return max; }
    spriteSide GetSide(Side side);

private:
    glm::vec2 min;
    glm::vec2 max;
};

#endif // !AABB_H