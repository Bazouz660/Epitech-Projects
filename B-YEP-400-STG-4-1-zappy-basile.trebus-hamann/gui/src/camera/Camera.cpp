/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Camera
*/

#include "Camera.hpp"
#include "Vec3.hpp"

namespace zpy {

Camera::Camera(float fov, CameraProjection projection)
{
    m_rayCam.position = Vec3(10.0f, 10.0f, 10.0f);
    m_rayCam.target = Vec3(0.0f, 0.0f, 0.0f);
    m_rayCam.up = Vec3(0.0f, 1.0f, 0.0f);
    m_rayCam.fovy = fov;
    m_rayCam.projection = projection;
}

Camera::~Camera()
{
}

void Camera::update()
{
    UpdateCamera(&m_rayCam, CAMERA_THIRD_PERSON);
}

}