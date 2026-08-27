/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Parser
*/

#pragma once

#include <libconfig.h++>
#include "Renderer.hpp"

namespace RayTracer
{
    class Parser {
        private:
            libconfig::Config _cfg;
            Camera _cam;
            Renderer _renderer;
            void buildCamera();
            void buildRenderer();
            Color::RGB getColor(const libconfig::Setting&);
            Material getMaterial(const libconfig::Setting&);
            void addSpheres(const libconfig::Setting&);
            void addPlanes(const libconfig::Setting&);
            void addCylinders(const libconfig::Setting&);
            void addModels(const libconfig::Setting&);
            void addPointLights(const libconfig::Setting&);
            void addDirectionalLights(const libconfig::Setting&);

        public:
            Parser(const std::string&);
            Renderer& getRenderer();
    };
}
