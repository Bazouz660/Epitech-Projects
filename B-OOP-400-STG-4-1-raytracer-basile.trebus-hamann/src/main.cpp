/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** main
*/

#include "Camera.hpp"
#include "Sphere.hpp"
#include "Color.hpp"
#include "Plane.hpp"
#include "Renderer.hpp"
#include "Parser.hpp"

void print_help()
{
    std::cerr << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
    std::cerr << "  SCENE_FILE: scene configuration" << std::endl;
}

int main(int ac, char **av)
{
    if (ac != 2 || (std::string(av[1]) == "--help")) {
        print_help();
        return (84);
    }
    RayTracer::Parser parser(av[1]);
    RayTracer::Renderer& renderer = parser.getRenderer();
    try {
        renderer.setMacrosampling(2);
        renderer.render();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}