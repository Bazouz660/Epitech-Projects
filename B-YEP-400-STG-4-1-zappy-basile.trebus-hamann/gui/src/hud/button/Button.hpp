/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Button
*/

#pragma once

#include "common.hpp"
#include "Vec2.hpp"

namespace zpy
{
    class Button {
        public:
            Button(const Vec2& pos, std::string text, std::function<void(void)> callback = []() {},
                unsigned int fontSize = 20, Color color = {255, 255, 255, 0});
            ~Button() = default;

            void draw() const;
            bool isHovered() const;
            bool isClicked() const;
            bool isReleased() const;
            void update();

            void setPos(const Vec2& pos);
            void setCallback(std::function<void(void)> callback) { m_callback = callback; }
            void setText(std::string text);
            void setColor(Color color) { m_color = color; }

            std::function<void(void)> getCallback() const { return m_callback; }
            Vec2 getPos() const { return m_pos; }
            Rectangle getRect() const { return m_rect; }
            std::string getText() const { return m_text; }
            Color getColor() const { return m_color; }
        private:
            std::function<void(void)> m_callback;
            Vec2 m_pos;
            Rectangle m_rect;
            std::string m_text;
            unsigned int m_fontSize;
            bool m_isPressed;
            Color m_color;
    };
}