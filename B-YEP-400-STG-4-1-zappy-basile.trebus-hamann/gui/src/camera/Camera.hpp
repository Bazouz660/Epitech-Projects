/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Camera
*/

#pragma once

#include "common.hpp"
#include "Vec3.hpp"

namespace zpy {

    class Camera {

        public:
            Camera(float fov = 90, CameraProjection projection = CAMERA_PERSPECTIVE);
            ~Camera();

            Vec3 getPosition() const { return m_rayCam.position; }

            Vector3& getPosition() { return m_rayCam.position; }

            void update();

            ::Camera3D& get() { return m_rayCam; }

        private:
            ::Camera3D m_rayCam;
    };

}