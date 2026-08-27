/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** OBJparser
*/

#pragma once

#include "common.hpp"
#include "Scene.hpp"

namespace RayTracer {

    class OBJparser {
        public:
            OBJparser() = default;
            ~OBJparser() = default;

            static sptr<Scene> parse(const std::string& path);

        private:
            typedef struct face_s {
                std::vector<sptr<Math::Vector3<double>>> vertices;
                std::vector<sptr<Math::Vector3<double>>> normals;
            } Face;

        private:
            static void parseFace(const std::string& line,
                const std::vector<sptr<Math::Vector3<double>>>& vertices,
                const std::vector<sptr<Math::Vector3<double>>>& normals,
                std::vector<sptr<Face>>& faces);

            static sptr<Scene> buildFromData(
                const std::vector<sptr<Math::Vector3<double>>>& vertices,
                const std::vector<sptr<Math::Vector3<double>>>& normals,
                const std::vector<sptr<Face>>& faces);
    };
}
