/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Renderer
*/

#include "Renderer.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "PrimitiveFactory.hpp"
#include "LightFactory.hpp"
#include "DirectionalLight.hpp"
#include "OBJparser.hpp"
#include <iomanip>

namespace RayTracer {

    Renderer::Renderer() : m_camera(Camera())
    {
    }

    Renderer::Renderer(const Camera& cam, int macrosampling, bool multithreaded)
    {
        m_resX = cam.getWidth();
        m_resY = cam.getHeight();
        m_ambientLight = 0.2;
        m_camera = cam;
        m_macrosampling = macrosampling;
        m_multithreaded = multithreaded;
        m_resX *= m_macrosampling;
        m_resY *= m_macrosampling;
    }

    void Renderer::bufferToOutput()
    {
        for (unsigned int xy = 0; xy < m_resX * m_resY; xy++) {
            m_output += m_buffer[xy].color.toString() + "\n";
        }
    }

    Color::RGB Renderer::getNeigboringColor(unsigned int x, unsigned int y, bool includeSelf)
    {
        Color::RGB c = m_buffer[y * m_resX + x].color;

        double r = 0;
        double g = 0;
        double b = 0;

        if (includeSelf) {
            r = c.r;
            g = c.g;
            b = c.b;
        }

        if (x > 0 && y > 0) {
            r += m_buffer[(y - 1) * m_resX + (x - 1)].color.r;
            g += m_buffer[(y - 1) * m_resX + (x - 1)].color.g;
            b += m_buffer[(y - 1) * m_resX + (x - 1)].color.b;
        }
        if (y > 0) {
            r += m_buffer[(y - 1) * m_resX + x].color.r;
            g += m_buffer[(y - 1) * m_resX + x].color.g;
            b += m_buffer[(y - 1) * m_resX + x].color.b;
        }
        if (x < m_resX - 1 && y > 0) {
            r += m_buffer[(y - 1) * m_resX + (x + 1)].color.r;
            g += m_buffer[(y - 1) * m_resX + (x + 1)].color.g;
            b += m_buffer[(y - 1) * m_resX + (x + 1)].color.b;
        }
        if (x > 0) {
            r += m_buffer[y * m_resX + (x - 1)].color.r;
            g += m_buffer[y * m_resX + (x - 1)].color.g;
            b += m_buffer[y * m_resX + (x - 1)].color.b;
        }
        if (x < m_resX - 1) {
            r += m_buffer[y * m_resX + (x + 1)].color.r;
            g += m_buffer[y * m_resX + (x + 1)].color.g;
            b += m_buffer[y * m_resX + (x + 1)].color.b;
        }
        if (x > 0 && y < m_resY - 1) {
            r += m_buffer[(y + 1) * m_resX + (x - 1)].color.r;
            g += m_buffer[(y + 1) * m_resX + (x - 1)].color.g;
            b += m_buffer[(y + 1) * m_resX + (x - 1)].color.b;
        }
        if (y < m_resY - 1) {
            r += m_buffer[(y + 1) * m_resX + x].color.r;
            g += m_buffer[(y + 1) * m_resX + x].color.g;
            b += m_buffer[(y + 1) * m_resX + x].color.b;
        }
        if (x < m_resX - 1 && y < m_resY - 1) {
            r += m_buffer[(y + 1) * m_resX + (x + 1)].color.r;
            g += m_buffer[(y + 1) * m_resX + (x + 1)].color.g;
            b += m_buffer[(y + 1) * m_resX + (x + 1)].color.b;
        }

        if (includeSelf) {
            return Color::RGB(r / 9, g / 9, b / 9);
        }
        return Color::RGB(r / 8, g / 8, b / 8);
    }

    void Renderer::applyPostProcessing()
    {
        averageUncomputedPixels();
        applyBlur(1);
    }

    void Renderer::averageUncomputedPixels()
    {
        // guess the color of the pixels that were not computed, restores the image
        for (unsigned int y = 0; y < m_resY; y++) {
            for (unsigned int x = 0; x < m_resX; x++) {
                if (m_buffer[y * m_resX + x].computed == false)
                    m_buffer[y * m_resX + x].color = getNeigboringColor(x, y, false);
            }
        }
    }

    void Renderer::applyBlur(unsigned int passes)
    {
        // blur the image to make it smoother (form of simple anti-aliasing)
        for (int m = 0; m < passes; m++) {
            for (unsigned int y = 0; y < m_resY; y++) {
                for (unsigned int x = 0; x < m_resX; x++) {
                    m_buffer[y * m_resX + x].color = getNeigboringColor(x, y, true);
                }
            }
        }
    }

    void Renderer::computeColor(Ray &ray, unsigned int x, unsigned int y)
    {
        // if we hit something, compute the color, else set the color to a dark gray
        if (ray.getClosestHit().obj == nullptr) {
            m_buffer[y * m_resX + x].color = Color::RGB(50, 50, 50);
            return;
        }

        ray.m_finalColor = ray.getClosestHit().obj->getColor();
        ray.m_finalColor *= m_ambientLight;

        // compute the lighting of the pixel
        for (auto &light : m_lights)
            light->computeDropShadow(ray, *ray.getClosestHit().obj, m_scene.getObjects());
        for (auto &light : m_lights) {
            light->computeDiffuse(ray, *ray.getClosestHit().obj);
            light->computeSpecular(ray, *ray.getClosestHit().obj);
        }

        ray.m_finalColor /= (m_lights.size() + 1);
        ray.m_finalColor.adjustSaturation(2.2);

        // store the color in the buffer
        m_buffer[y * m_resX + x].color = ray.m_finalColor;
        m_buffer[y * m_resX + x].computed = true;
    }

    void Renderer::renderSingleThreaded()
    {
        for (unsigned int y = 0; y < m_resY; y++) {
            for (unsigned int x = 0; x < m_resX; x++) {
                if (x % 2 == 0 && y % 2 == 0)
                    continue;
                double u = (double(x) * 2 / (m_resX - 1)) - 1;
                double v = (double(y) * 2 / (m_resY - 1)) - 1;
                Ray ray = m_camera.ray(u, v);
                m_scene.hits(ray);
                computeColor(ray, x, y);
                m_progress++;
            }
        }
    }

    void Renderer::renderRegion(unsigned int startX, unsigned int endX)
    {
        for (unsigned int y = 0; y < m_resY; y++) {
            for (unsigned int x = startX; x < endX; x++) {
                double u = (double(x) * 2 / (m_resX - 1)) - 1;
                double v = (double(y) * 2 / (m_resY - 1)) - 1;
                RayTracer::Ray ray = m_camera.ray(u, v);
                m_scene.hits(ray);
                computeColor(ray, x, y);
                m_progress++;
            }
        }
    }

    void Renderer::renderMultiThreaded(unsigned int threadCount)
    {
        std::vector<std::thread> threads;
        int startX;
        int endX;

        for (unsigned int i = 0; i < threadCount; i++) {
            // push a new thread with the renderRegion function
            startX = (m_resX / threadCount) * i;
            endX = (m_resX / threadCount) * (i + 1);
            threads.push_back(std::thread(&Renderer::renderRegion, this, startX, endX));
        }
        for (auto &thread : threads) {
            thread.join();
        }
    }

    void Renderer::printProgress()
    {
        while (m_progress < m_resX * m_resY) {
            std::cerr << "\r" << std::setprecision(2) << std::fixed << (double(m_progress) / (m_resX * m_resY)) * 100 << "%";
            if (m_progress == m_resX * m_resY)
                break;
        }
        std::cerr << "\r100.00%\n";
    }

    void Renderer::render()
    {
        std::string debugLog;

        // init output
        m_output = "P3\n" + std::to_string(m_resX) + " " + std::to_string(m_resY) + "\n255\n";
        m_buffer = new buffer_t[m_resX * m_resY];

        // init octree
        /* std::vector<sptr<IPrimitive>> objects = m_scene.getPrimitives();
        std::cerr << "found " << objects.size() << " objects" << std::endl;
        std::cerr << "building octree... ";
        m_octree = std::make_unique<Space::Octree>(Space::Octree(m_scene.getBoundsFinite()));
        for (auto &obj : objects)
            m_octree->insert(obj);
        std::cerr << "done" << std::endl;

        std::cerr << "res: x = " << m_resX << ", y = " << m_resY << std::endl; */

        // init threads
        std::thread progressThread(&Renderer::printProgress, this);

        unsigned int threadCount = std::thread::hardware_concurrency();
        // loop through all pixels
        if (threadCount == 1 || !m_multithreaded)
            renderSingleThreaded();
        else
            renderMultiThreaded(threadCount);

        m_progress = m_resX * m_resY;
        progressThread.join();

        applyPostProcessing();
        std::cerr << "writing to buffer..." << std::endl;
        bufferToOutput();

        std::cerr << debugLog;
        std::cout << m_output;
        std::cerr << "Done" << std::endl;
    }

    void Renderer::setMacrosampling(unsigned int macrosampling)
    {
        m_macrosampling = macrosampling;
    }

    void Renderer::addLight(sptr<ILight> light)
    {
        m_lights.push_back(std::move(light));
    }

    void Renderer::addObject(sptr<IPrimitive> object)
    {
        m_scene.addObject(std::move(object));
    }

}