// maybe something here...
#include "vector_util.h"
#include <SFML/System/Vector2.hpp>

struct BasicTransform {
    // methods...

    sf::Vector2f applyVector(const sf::Vector2f& p) {
        return sf::Vector2f(p.x * scale.x, p.y * scale.y);
    }

    sf::Vector2f applyPoint(const sf::Vector2f& p) {
        sf::Vector2f scaleRes(p.x * scale.x, p.y * scale.y);
        return {scaleRes.x + translation.x, scaleRes.y + translation.y};
    }

    bool operator==(const BasicTransform& other) {
        return (scale.x == other.scale.x && scale.y == other.scale.y) && (translation.x == other.translation.x && translation.y == other.translation.y);
    }



    sf::Vector2f scale;
    sf::Vector2f translation;
};
