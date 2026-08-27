/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** TriangleBuilder
*/

#include "TriangleBuilder.hpp"

RayTracer::TriangleBuilder &RayTracer::TriangleBuilder::setA(
    double x, double y, double z)
{
    m_a = Math::Vector3<double>(x, y, z);
    return *this;
}

RayTracer::TriangleBuilder &RayTracer::TriangleBuilder::setA(
    Math::Vector3<double> a)
{
    m_a = a;
    return *this;
}

RayTracer::TriangleBuilder &RayTracer::TriangleBuilder::setB(
    double x, double y, double z)
{
    m_b = Math::Vector3<double>(x, y, z);
    return *this;
}

RayTracer::TriangleBuilder &RayTracer::TriangleBuilder::setB(
    Math::Vector3<double> b)
{
    m_b = b;
    return *this;
}

RayTracer::TriangleBuilder &RayTracer::TriangleBuilder::setC(
    double x, double y, double z)
{
    m_c = Math::Vector3<double>(x, y, z);
    return *this;
}

RayTracer::TriangleBuilder &RayTracer::TriangleBuilder::setC(
    Math::Vector3<double> c)
{
    m_c = c;
    return *this;
}

RayTracer::TriangleBuilder &RayTracer::TriangleBuilder::setNA(
    double x, double y, double z)
{
    m_nA = Math::Vector3<double>(x, y, z);
    return *this;
}

RayTracer::TriangleBuilder &RayTracer::TriangleBuilder::setNA(
    Math::Vector3<double> nA)
{
    m_nA = nA;
    return *this;
}

RayTracer::TriangleBuilder &RayTracer::TriangleBuilder::setNB(
    double x, double y, double z)
{
    m_nB = Math::Vector3<double>(x, y, z);
    return *this;
}

RayTracer::TriangleBuilder &RayTracer::TriangleBuilder::setNB(
    Math::Vector3<double> nB)
{
    m_nB = nB;
    return *this;
}

RayTracer::TriangleBuilder &RayTracer::TriangleBuilder::setNC(
    double x, double y, double z)
{
    m_nC = Math::Vector3<double>(x, y, z);
    return *this;
}

RayTracer::TriangleBuilder &RayTracer::TriangleBuilder::setNC(
    Math::Vector3<double> nC)
{
    m_nC = nC;
    return *this;
}

sptr<RayTracer::IPrimitive> RayTracer::TriangleBuilder::build()
{
    return std::make_shared<Triangle>(m_a, m_b, m_c, m_nA, m_nB, m_nC, m_color, m_name, m_material);
}