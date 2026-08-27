/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Button3d
*/

#pragma once

#include "common.hpp"
#include "Vec2.hpp"

namespace zpy
{
    class Button3d {
        public:
            Button3d() = default;
            Button3d(BoundingBox box, std::function<void(void)> callback = []() {});
            ~Button3d() = default;

            void draw() const;
            bool isHovered() const;
            bool isClicked() const;
            bool isReleased() const;
            void update();

            void setCallback(std::function<void(void)> callback) { m_callback = callback; }
            void setBox(BoundingBox box) { m_box = box; }

            BoundingBox getBox() const { return m_box; }
            std::function<void(void)> getCallback() const { return m_callback; }
        private:
            std::function<void(void)> m_callback;
            BoundingBox m_box;
            bool m_isPressed;
    };
}