/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Camera
*/

#include "Camera.hpp"

namespace RayTracer
{
    Camera::Camera()
    {
        m_fov = 90;
        m_origin = Math::Vector3<double>(0, 0, 0);
    }

    Camera::Camera(unsigned int fov, unsigned int width, unsigned int height)
    {
        m_fov = fov;
        m_origin = Math::Vector3<double>(0, 0, -3);
        m_screenResX = width;
        m_screenResY = height;
    }

    Camera::~Camera()
    {
    }

    unsigned int Camera::getFov() const
    {
        return m_fov;
    }

    unsigned int Camera::getWidth() const
    {
        return m_screenResX;
    }

    unsigned int Camera::getHeight() const
    {
        return m_screenResY;
    }

    void Camera::setFov(unsigned int fov)
    {
        m_fov = fov;
    }

    void Camera::setWidth(unsigned int width)
    {
        m_screenResX = width;
    }

    void Camera::setHeight(unsigned int height)
    {
        m_screenResY = height;
    }

    void Camera::setOrigin(Math::Vector3<double> origin)
    {
        m_origin = origin;
    }

    void Camera::setRotation(Math::Vector3<double> rotation)
    {
        m_rotation = rotation;
    }

    Ray Camera::ray(double u, double v) const
    {
        // set fov and aspect ratio
        double fov = m_fov;
        double aspectRatio = (double)m_screenResX / (double)m_screenResY;

        // compute camera space coordinates of the ray origin
        double theta = fov * M_PI / 180;
        double halfHeight = tan(theta / 2);
        double halfWidth = aspectRatio * halfHeight;

        // compute the direction of the ray, using the camera space coordinates and the rotation
        Math::Vector3<double> direction = Math::Vector3<double>(2 * u * halfWidth, 2 * v * halfHeight, 1);
        direction = direction.normalize();
        direction = direction.rotate(m_rotation);

        return Ray(m_origin, direction);
    }

}