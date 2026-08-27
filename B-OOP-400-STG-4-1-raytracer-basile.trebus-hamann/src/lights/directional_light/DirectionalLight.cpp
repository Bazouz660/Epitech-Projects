/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** DirectionalLight
*/

#include "DirectionalLight.hpp"

namespace RayTracer {

    DirectionalLight::DirectionalLight(const Math::Vector3<double> &position, const Color::RGB &color, double intensity)
        : ALight(position, color, intensity)
    {
    }

    void DirectionalLight::computeSpecular(Ray& hitRay, IPrimitive& obj) const
    {
        if (hitRay.getClosestHit().lights_info.at((ILight *)this)->isShadowed)
            return;

        if (obj.getMaterial().getShininess() == 0)
            return;

        double specular = 0.0;
        double shininess = 32;
        double shineIntensity = obj.getMaterial().getShininess();

        Math::Vector3<double> lightDirection = m_position.normalize().invert();
        Math::Vector3<double> normal = hitRay.getClosestHit().normal.normalize();
        Math::Vector3<double> reflection = 2 * normal.dot(lightDirection) * normal - lightDirection;
        Math::Vector3<double> view = hitRay.dir.normalize().invert();

        double specularAngle = std::max(0.0, reflection.dot(view));
        specular = m_intensity * std::pow(specularAngle, shininess) * shineIntensity;

        hitRay.m_finalColor += specular;
    }

    bool DirectionalLight::computeDropShadow(Ray& hitRay, IPrimitive& testObj,
        std::vector<sptr<IPrimitive>> objs) const
    {
        Ray::light_info_t info;

        Ray shadowRay(hitRay.getClosestHit().hitPosition, m_position.invert());

        info.isShadowed = false;

        for (auto &obj : objs) {
            if (&testObj == obj.get())
                continue;
            if (obj->hits(shadowRay)) {
                if (shadowRay.getHit().dist > m_position.distance(hitRay.getClosestHit().hitPosition))
                    continue;
                info.isShadowed = true;
                break;
            }
        }
        hitRay.getClosestHit().lights_info.emplace((ILight *)this, std::make_unique<Ray::light_info_t>(info));
        return info.isShadowed;
    }

    void DirectionalLight::computeDiffuse(Ray& hitRay, IPrimitive& obj) const
    {
        if (hitRay.getClosestHit().lights_info.at((ILight *)this)->isShadowed)
            return;

        float light_level = hitRay.getClosestHit().normal.dot(m_position.invert());

        if (light_level < 0)
            light_level = 0;

        double brightness = light_level * m_intensity;

        hitRay.m_finalColor += m_color * brightness;
    }
}
