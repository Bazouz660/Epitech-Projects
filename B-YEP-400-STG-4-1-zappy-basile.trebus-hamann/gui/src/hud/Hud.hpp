/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Hud
*/

#pragma once

#include "common.hpp"
#include "Button.hpp"
#include <map>

namespace zpy {

    class Hud {
        public:
            struct Text {
                std::string text;
                Vector2 pos;
                int size;
                Color color;
            };

            Hud() = default;
            ~Hud() = default;

            void update();
            void draw();

            void addButton(const std::string& id, sptr<Button> button);
            void addRect(const std::string& id, sptr<Rectangle> rect);
            void addText(const std::string& id, sptr<Text> text);

            void removeButton(const std::string& id);
            void removeRect(const std::string& id);
            void removeText(const std::string& id);

        private:
            std::map<std::string, sptr<Button>> _buttons;
            std::map<std::string, sptr<Rectangle>> m_rect;
            std::map<std::string, sptr<Text>> m_text;
    };

}