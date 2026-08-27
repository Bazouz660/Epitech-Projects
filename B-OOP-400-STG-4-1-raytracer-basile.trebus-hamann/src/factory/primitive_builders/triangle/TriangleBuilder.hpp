/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** TriangleBuilder
*/

#pragma once

#include "APrimitiveBuilder.hpp"
#include "Triangle.hpp"

namespace RayTracer {

    class TriangleBuilder : public APrimitiveBuilder {
        public:
            TriangleBuilder() = default;
            virtual ~TriangleBuilder() = default;

            TriangleBuilder &setA(double x, double y, double z);
            TriangleBuilder &setA(Math::Vector3<double> a);

            TriangleBuilder &setB(double x, double y, double z);
            TriangleBuilder &setB(Math::Vector3<double> b);

            TriangleBuilder &setC(double x, double y, double z);
            TriangleBuilder &setC(Math::Vector3<double> c);

            TriangleBuilder &setNA(double x, double y, double z);
            TriangleBuilder &setNA(Math::Vector3<double> nA);

            TriangleBuilder &setNB(double x, double y, double z);
            TriangleBuilder &setNB(Math::Vector3<double> nB);

            TriangleBuilder &setNC(double x, double y, double z);
            TriangleBuilder &setNC(Math::Vector3<double> nC);

            sptr<IPrimitive> build() override;

        private:
            Math::Vector3<double> m_a;
            Math::Vector3<double> m_b;
            Math::Vector3<double> m_c;

            Math::Vector3<double> m_nA;
            Math::Vector3<double> m_nB;
            Math::Vector3<double> m_nC;
    };

}