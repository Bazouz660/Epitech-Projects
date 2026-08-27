/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Fog
*/

#include "Fog.hpp"
#include "Vec4.hpp"

namespace zpy::shader {

    Fog::Fog()
    : m_density(0.05f), m_color({100, 100, 100, 255})
    {
    }

    Fog::~Fog()
    {
        if (m_isLoaded) {
            m_isLoaded = false;
            UnloadShader(m_shader);
        }
    }

    void Fog::init()
    {
        m_shader = LoadShader(TextFormat("gui/resources/shaders/lighting.vs"),
            TextFormat("gui/resources/shaders/fog.fs"));

        m_shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(m_shader, "matModel");
        m_shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(m_shader, "viewPos");

        // Ambient light level
        m_ambientLoc = GetShaderLocation(m_shader, "ambient");
        float value[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        SetShaderValue(m_shader, m_ambientLoc, value, SHADER_UNIFORM_VEC4);

        m_colorLoc = GetShaderLocation(m_shader, "fogColor");
        float cvalue[4] = {(float)m_color.r / 255.f, (float)m_color.g / 255.f,
            (float)m_color.b / 255.f, (float)m_color.a / 255.f};
        SetShaderValue(m_shader, m_colorLoc, cvalue, SHADER_UNIFORM_VEC4);

        m_density = 0.08f;
        m_densityLoc = GetShaderLocation(m_shader, "fogDensity");
        SetShaderValue(m_shader, m_densityLoc, &m_density, SHADER_UNIFORM_FLOAT);

        m_isLoaded = true;
    }

    void Fog::setDensity(float density)
    {
        m_density = density;
        SetShaderValue(m_shader, m_densityLoc, &m_density, SHADER_UNIFORM_FLOAT);
    }

    float Fog::getDensity() const
    {
        return m_density;
    }

    void Fog::setColor(const Color &color)
    {
        m_color = color;

        float cvalue[4] = {(float)m_color.r / 255.f, (float)m_color.g / 255.f,
            (float)m_color.b / 255.f, (float)m_color.a / 255.f};
        SetShaderValue(m_shader, m_colorLoc, cvalue, SHADER_UNIFORM_VEC4);
    }

    const Color& Fog::getColor() const
    {
        return m_color;
    }

    Shader& Fog::getHandle()
    {
        return m_shader;
    }
}