#ifndef SPRITE_H
#define SPRITE_H

#include "basic_transform.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>

class Sprite {  // could derive from sf::Drawable if you're willing to pay for a vptr, but not
                // necessary.
public:
    Sprite(const sf::Texture& texture) {
        // TODO
        mTexture = &texture;
        mMinPointTex = sf::Vector2f(0.f, 0.f);
        mMaxPointTex = static_cast<sf::Vector2f>(texture.getSize()); 
        mOrigin = sf::Vector2f((mMaxPointTex.x - mMinPointTex.x) / 2.f, (mMaxPointTex.y - mMinPointTex.y) / 2.f);
        mTransform.scale = sf::Vector2f(1.f, 1.f);
        mTransform.translation = sf::Vector2f(0.f, 0.f);
        mVertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
        mVertexArray.resize(6);

    }

    Sprite(const sf::Texture& texture, const sf::Vector2f& texMinPoint,
           const sf::Vector2f& texMaxPoint) {
        mTexture = &texture;
        mMaxPointTex = texMaxPoint;
        mMinPointTex = texMinPoint;
        mOrigin = sf::Vector2f((mMaxPointTex.x - mMinPointTex.x) / 2.f, (mMaxPointTex.y - mMinPointTex.y) / 2.f);
        mTransform.scale = sf::Vector2f(1.f, 1.f);
        mTransform.translation = sf::Vector2f(0.f, 0.f);
        mVertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
        mVertexArray.resize(6);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // TODO
        recomputeVertexArray();
        states.texture = mTexture;
        states.transform.translate(mTransform.translation);
        states.transform.scale(mTransform.scale);
        target.draw(mVertexArray, states);
    }

    sf::Vector2f& position() { return mTransform.translation; }
    const sf::Vector2f& position() const { return mTransform.translation; }
    sf::Vector2f& scale() { return mTransform.scale; }
    const sf::Vector2f& scale() const { return mTransform.scale; }
    sf::Vector2f& origin() { return mOrigin; }
    const sf::Vector2f& origin() const { return mOrigin; }

private:
    // It may help you to write this, which is an array of 6 vertices:
    //   - the first 3 correspond to the vertices of the top-left triangle of a "default rectangle"
    //     ranging from [0, 1] in both dimensions.
    //   - the next 3 correspond to the vertices of the bottom-right triangle. of the default
    //     rectangle.
    static constexpr std::array<sf::Vector2f, 6> DEFAULT_VERTICES = {{
        {0.f, 0.f},
        {0.f, 1.f},
        {1.f, 0.f},

        {1.f, 0.f},
        {0.f, 1.f},
        {1.f, 1.f}
    }};  // TODO

    // if mTexture is valid, recomputes the positions and coords of sf::Vertex for each
    // of 6 possible entries in mVertexArray.
    void recomputeVertexArray() const {
        // TODO
        sf::Vector2f validArea = mMaxPointTex - mMinPointTex;
        for (int i = 0; i < mVertexArray.getVertexCount(); i++) {
            sf::Vector2f p = DEFAULT_VERTICES[i];
            sf::Vector2f temp(p.x * validArea.x, p.y * validArea.y);
            mVertexArray[i].texCoords = mMinPointTex + temp;
            mVertexArray[i].position = temp - mOrigin;
        }

    }

    const sf::Texture* mTexture;
    mutable sf::VertexArray mVertexArray;  // geometry, uv coords -- mutable means it can be changed
                                           //  even in const methods.
    sf::Vector2f mMinPointTex;             // AABB for subtexture min point along both x, y
    sf::Vector2f mMaxPointTex;             // AABB for subtexture max point along both x, y
    sf::Vector2f mOrigin;  // position in tex coords of the sprite origin, relative to minPoint
    BasicTransform mTransform;
};

#endif
