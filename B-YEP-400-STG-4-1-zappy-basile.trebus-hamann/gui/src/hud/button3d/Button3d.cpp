/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Button3d
*/

#include "Button3d.hpp"
#include "context.hpp"

namespace zpy {

    Button3d::Button3d(BoundingBox box, std::function<void(void)> callback)
        : m_box(box), m_callback(callback), m_isPressed(false)
    {
    }

    void Button3d::draw() const
    {
        if (m_isPressed)
            DrawBoundingBox(m_box, {0, 255, 0, 100});
        else
            DrawBoundingBox(m_box, {255, 0, 0, 100});
    }

    bool Button3d::isHovered() const
    {
        RayCollision col = GetRayCollisionBox(GetMouseRay(GetMousePosition(), context::getCamera().get()), m_box);

        return col.hit;
    }

    bool Button3d::isClicked() const
    {
        return isHovered() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }

    bool Button3d::isReleased() const
    {
        return isHovered() && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
    }

    void Button3d::update()
    {
        if (isClicked())
            m_isPressed = true;
        else if (isReleased() && m_isPressed) {
            m_callback();
            m_isPressed = false;
        } else if (!isHovered())
            m_isPressed = false;
    }

}