/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** Label
*/

#include "Label.hpp"
#include "core/resource_manager/ResourceManager.hpp"

namespace exng::gui
{
    Label::Label(const sf::Vector2f &position, const std::string &text, int size)
    {
        // an sf::Text without a font draws nothing at all
        m_text.setFont(ResourceManager::getFont("font", "upheavtt"));
        m_text.setPosition(position);
        m_text.setString(text);
        m_text.setCharacterSize(size);
    }

    void Label::setString(const std::string &text)
    {
        m_text.setString(text);
    }

    void Label::centerOrigin()
    {
        auto bounds = m_text.getLocalBounds();
        m_text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    }

    void Label::render(Window &window)
    {
        window.draw(m_text);
    }

    void Label::update()
    {
    }

    void Label::handleEvent(const sf::Event &event)
    {
    }

    sf::Text &Label::getText()
    {
        return m_text;
    }

    void Label::setPosition(const sf::Vector2f &position)
    {
        m_text.setPosition(position);
        m_shape.setPosition(position);
    }
}