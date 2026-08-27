/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Hud
*/

#include "Hud.hpp"

namespace zpy {

    void Hud::update()
    {
        for (auto &[id, button] : _buttons)
            button->update();
    }

    void Hud::draw()
    {
        Vec2 wSize = {static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};

        for (auto &[id, rect] : m_rect)
            DrawRectangleRec(*rect, GRAY);
        for (auto &[id, text] : m_text)
            DrawText(text->text.c_str(), text->pos.x, text->pos.y, text->size, text->color);
        for (auto &[id, button] : _buttons)
            button->draw();

        DrawFPS(10, wSize.y - 30);
    }

    void Hud::addButton(const std::string& id, sptr<Button> button)
    {
        if (_buttons.find(id) != _buttons.end()) {
            _buttons[id]->setCallback(button->getCallback());
            _buttons[id]->setPos(button->getPos());
            _buttons[id]->setText(button->getText());
            _buttons[id]->setColor(button->getColor());
            return;
        }
        _buttons[id] = button;
    }

    void Hud::addRect(const std::string& id, sptr<Rectangle> rect)
    {
        if (m_rect.find(id) != m_rect.end()) {
            m_rect[id]->x = rect->x;
            m_rect[id]->y = rect->y;
            m_rect[id]->width = rect->width;
            m_rect[id]->height = rect->height;
            return;
        }
        m_rect[id] = rect;
    }

    void Hud::addText(const std::string& id, sptr<Text> text)
    {
        if (m_text.find(id) != m_text.end()) {
            m_text[id]->text = text->text;
            m_text[id]->pos = text->pos;
            m_text[id]->size = text->size;
            m_text[id]->color = text->color;
            return;
        }
        m_text[id] = text;
    }

    void Hud::removeButton(const std::string& id)
    {
        if (_buttons.find(id) != _buttons.end())
            _buttons.erase(id);
    }

    void Hud::removeRect(const std::string& id)
    {
        if (m_rect.find(id) != m_rect.end())
            m_rect.erase(id);
    }

    void Hud::removeText(const std::string& id)
    {
        if (m_text.find(id) != m_text.end())
            m_text.erase(id);
    }

}