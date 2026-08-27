/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** sound
*/

#ifndef RTYPE_SOUNDCOMP_HPP
#define RTYPE_SOUNDCOMP_HPP

#include <SFML/Audio.hpp>
#include <memory>

namespace rtype::comp {

    struct Sound {
        std::shared_ptr<sf::Sound> sound;
    };

}

#endif // !RTYPE_SOUNDCOMP_HPP