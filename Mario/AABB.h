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

    bool Intersects(const AABB& other) const {
        return (min.x <= other.max.x && max.x >= other.min.x &&
            min.y <= other.max.y && max.y >= other.min.y);
    }

    bool IntersectPoint(const glm::vec2 point) const {
        return (min.x <= point.x && max.x >= point.x &&
                min.y <= point.y && max.y >= point.y);
    }

    void IntersectSide(spriteSide side) const {
        
    }

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