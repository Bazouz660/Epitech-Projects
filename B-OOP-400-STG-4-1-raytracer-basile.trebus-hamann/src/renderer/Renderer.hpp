/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Renderer
*/

#pragma once

#include "Camera.hpp"
#include "IPrimitive.hpp"
#include "ILight.hpp"
#include "Scene.hpp"
#include "Octree.hpp"

namespace RayTracer {

    class Renderer {

        public:
            Renderer();
            Renderer(const Camera&, int, bool);
            ~Renderer() = default;

            void addObject(sptr<IPrimitive> obj);
            void addLight(sptr<ILight> light);
            void render();
            void setMacrosampling(unsigned int macrosampling);

        private:
            void init();
            void renderRegion(unsigned int startX, unsigned int startY);
            void bufferToOutput();
            void applyPostProcessing();
            void averageUncomputedPixels();
            void applyBlur(unsigned int passes);
            void computeColor(Ray& ray, unsigned int x, unsigned int y);
            void renderMultiThreaded(unsigned int threadCount);
            void renderSingleThreaded();
            Color::RGB getNeigboringColor(unsigned int x, unsigned int y, bool includeSelf);

            void printProgress();

        private:
            typedef struct buffer_s {
                Color::RGB color;
                bool computed = false;
            } buffer_t;

            unsigned int m_macrosampling = 1;
            bool m_multithreaded = false;

            float m_progress = 0;

            buffer_t *m_buffer;
            std::string m_output;

            float m_ambientLight;
            std::vector<sptr<ILight>> m_lights;

            Scene m_scene;
            sptr<Space::Octree> m_octree;

            unsigned int m_resX;
            unsigned int m_resY;

            unsigned int m_baseResX;
            unsigned int m_baseResY;

            Camera m_camera;
    };

}