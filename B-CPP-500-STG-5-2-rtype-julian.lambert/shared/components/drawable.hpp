#pragma once

#include "common.hpp"

namespace rtype::comp {

struct zIndex
{
    unsigned int zIndex = 0;
};

struct Drawable
{
    enum Type {
        RECTANGLE,
        CIRCLE,
        SPRITE,
        TEXT,
        VERTEX_BUFFER
    };

    Type type = RECTANGLE;

    struct Rectangle
    {
        sf::RectangleShape shape;
    } rectangle;

    struct Circle
    {
        sf::CircleShape shape;
    } circle;

    struct Sprite
    {
        sf::Sprite shape;
    } sprite;

    struct Text
    {
        sf::Text shape;
    } text;

    struct VertexBuffer
    {
        sf::VertexBuffer shape;
    } vertexBuffer;

    Drawable() = default;
};

}
