/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Button
*/

#include "Button.hpp"

namespace zpy {

    Button::Button(const Vec2& pos, std::string text,
        std::function<void(void)> callback, unsigned int fontSize, Color color)
    {
        m_text = text;
        m_fontSize = fontSize;
        m_pos = pos;
        m_callback = callback;
        m_isPressed = false;

        float width = static_cast<float>(MeasureText(text.c_str(), fontSize));
        float height = static_cast<float>(fontSize);

        m_rect = {m_pos.x, m_pos.y, width, height};
        m_color = color;
    }

    void Button::setPos(const Vec2& pos)
    {
        m_pos = pos;
        m_rect.x = pos.x;
        m_rect.y = pos.y;
    }

    void Button::setText(std::string text)
    {
        m_text = text;
        m_rect.width = static_cast<float>(MeasureText(text.c_str(), m_fontSize));
    }

    void Button::draw() const
    {
        if (isHovered())
            DrawRectangleRec(m_rect, {255, 255, 255, 100});
        else if (m_isPressed)
            DrawRectangleRec(m_rect, {255, 255, 255, 200});
        DrawText(m_text.c_str(), m_pos.x, m_pos.y, m_fontSize, WHITE);
    }

    bool Button::isHovered() const
    {
        return CheckCollisionPointRec(GetMousePosition(), m_rect);
    }

    bool Button::isClicked() const
    {
        return isHovered() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }

    bool Button::isReleased() const
    {
        return isHovered() && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
    }

    void Button::update()
    {
        if (isClicked() && m_callback)
            m_isPressed = true;
        if (isReleased() && m_isPressed) {
            m_callback();
            m_isPressed = false;
        } else if (!isHovered())
            m_isPressed = false;
    }

}