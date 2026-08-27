/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** PointLight
*/

#include "PointLight.hpp"

namespace RayTracer {

    PointLight::PointLight(const Math::Vector3<double> &position, double radius,
    double falloff, const Color::RGB &color, double intensity)
        : ALight(position, color, intensity)
    {
        m_radius = radius;
        m_falloff = falloff;
    }

    void PointLight::computeSpecular(Ray& hitRay, IPrimitive& obj) const
    {
        if (hitRay.getClosestHit().lights_info.at((ILight *)this)->isShadowed)
            return;

        if (obj.getMaterial().getShininess() == 0)
            return;

        double specular = 0.0;
        double shininess = 32;
        double shineIntensity = obj.getMaterial().getShininess();

        Math::Vector3<double> lightDirection = (m_position - hitRay.getClosestHit().hitPosition).normalize();
        Math::Vector3<double> normal = hitRay.getClosestHit().normal.normalize();
        Math::Vector3<double> reflection = 2 * normal.dot(lightDirection) * normal - lightDirection;

        Math::Vector3<double> view = hitRay.dir.normalize().invert();
        double specularAngle = std::max(0.0, reflection.dot(view));
        specular = m_intensity * std::pow(specularAngle, shininess) * shineIntensity;

        hitRay.m_finalColor += specular;
    }

    bool PointLight::computeDropShadow(Ray& hitRay, IPrimitive& testObj, std::vector<sptr<IPrimitive>> objs) const
    {
        Ray::light_info_t info;

        Ray shadowRay(hitRay.getClosestHit().hitPosition, m_position - hitRay.getClosestHit().hitPosition);

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

    void PointLight::computeDiffuse(Ray& hitRay, IPrimitive& obj) const
    {
        if (hitRay.getClosestHit().lights_info.at((ILight *)this)->isShadowed) {
            return;
        }

        double diffuseFactor = hitRay.getClosestHit().normal.dot(m_position - hitRay.getClosestHit().hitPosition);
        double dist = m_position.distance(hitRay.getClosestHit().hitPosition);

        if (diffuseFactor < 0)
            diffuseFactor = 0;

        // computes brightness based on falloff, radius and distance.
        // The radius is the reach of the light and the falloff is the rate at wich it dims out.
        double brightness = diffuseFactor * m_intensity / (dist * m_falloff) * (m_radius / dist);

        hitRay.m_finalColor += (m_color * brightness);
    }
}