/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Parser
*/

#include <iostream>
#include "Parser.hpp"
#include "PrimitiveFactory.hpp"
#include "LightFactory.hpp"
#include "Color.hpp"
#include "OBJparser.hpp"

namespace RayTracer
{
    Parser::Parser(const std::string& filepath)
    {
        try {
            _cfg.readFile(filepath.c_str());
        } catch (const libconfig::FileIOException& ex) {
            std::cerr << "File reading error: " << ex.what() << std::endl;
            std::exit(84);
        } catch (const libconfig::ParseException& ex) {
            std::cerr << "Parsing error: " << ex.getError() << std::endl;
            std::exit(84);
        }
        buildCamera();
        buildRenderer();
    }

    void Parser::buildCamera()
    {
        Camera camCfg;
        const libconfig::Setting& camStg = _cfg.lookup("camera");
        camCfg.setFov(camStg["fieldOfView"]);
        const libconfig::Setting& screenStg = camStg.lookup("resolution");
        camCfg.setWidth(screenStg["width"]);
        camCfg.setHeight(screenStg["height"]);
        const libconfig::Setting& originStg = camStg.lookup("position");
        camCfg.setOrigin(Math::Vector3<double>(originStg["x"], originStg["y"], originStg["z"]));
        const libconfig::Setting& rotationStg = camStg.lookup("rotation");
        camCfg.setRotation(Math::Vector3<double>(rotationStg["x"], rotationStg["y"], rotationStg["z"]));
        _cam = camCfg;
    }

    Color::RGB Parser::getColor(const libconfig::Setting& setting)
    {
        return Color::RGB(
            setting["r"],
            setting["g"],
            setting["b"]
        );
    }

    Material Parser::getMaterial(const libconfig::Setting& setting)
    {
        return Material(
            setting["a"],
            setting["r"],
            setting["t"],
            setting["i"]
        );
    }

    void Parser::buildRenderer()
    {
        const libconfig::Setting& renderSetting = _cfg.lookup("render");
        _renderer = Renderer(_cam,
            renderSetting["macrosampling"], renderSetting["multithreaded"]);
        const libconfig::Setting& primitivesSetting = _cfg.lookup("primitives");
        if (primitivesSetting.exists("spheres"))
            addSpheres(primitivesSetting);
        if (primitivesSetting.exists("planes"))
            addPlanes(primitivesSetting);
        if (primitivesSetting.exists("models"))
            addModels(primitivesSetting);
        if (primitivesSetting.exists("ucylinders"))
            addCylinders(primitivesSetting);

        const libconfig::Setting& lightsSetting = _cfg.lookup("lights");
        if (lightsSetting.exists("points"))
            addPointLights(lightsSetting);
        if (lightsSetting.exists("directionals"))
            addDirectionalLights(lightsSetting);
    }

    void Parser::addSpheres(const libconfig::Setting& primitivesSetting)
    {
        const libconfig::Setting& spheresSetting = primitivesSetting["spheres"];

        for (int i = 0; i < spheresSetting.getLength(); ++i) {
            const libconfig::Setting& sphereSetting = spheresSetting[i];
            double x = sphereSetting["x"];
            double y = sphereSetting["y"];
            double z = sphereSetting["z"];
            _renderer.addObject(
                PrimitiveFactory::createSphere()
                    ->setCenter(x, y, z)
                    .setRadius(sphereSetting["radius"])
                    .setColor(getColor(sphereSetting["color"]))
                    .setMaterial(getMaterial(sphereSetting["material"]))
                    .build()
            );
        }
    }

    void Parser::addCylinders(const libconfig::Setting& primitivesSetting)
    {
        const libconfig::Setting& cylindersSetting = primitivesSetting["ucylinders"];

        for (int i = 0; i < cylindersSetting.getLength(); ++i) {
            const libconfig::Setting& cylinderSetting = cylindersSetting[i];
            double x = cylinderSetting["x"];
            double y = cylinderSetting["y"];
            double z = cylinderSetting["z"];
            _renderer.addObject(
                PrimitiveFactory::createCylinder()
                    ->setCenter(x, y, z)
                    .setRadius(cylinderSetting["radius"])
                    .setHeight(cylinderSetting["height"])
                    .setAxis(cylinderSetting["axis"]["x"], cylinderSetting["axis"]["y"], cylinderSetting["axis"]["z"])
                    .setColor(getColor(cylinderSetting["color"]))
                    .setMaterial(getMaterial(cylinderSetting["material"]))
                    .build()
            );
        }
    }

    void Parser::addPlanes(const libconfig::Setting& primitivesSetting)
    {
        const libconfig::Setting& planesSetting = primitivesSetting["planes"];
        for (int i = 0; i < planesSetting.getLength(); ++i) {
            const libconfig::Setting& planeSetting = planesSetting[i];

            double normalX = planeSetting["normal"]["x"];
            double normalY = planeSetting["normal"]["y"];
            double normalZ = planeSetting["normal"]["z"];

            double originX = planeSetting["origin"]["x"];
            double originY = planeSetting["origin"]["y"];
            double originZ = planeSetting["origin"]["z"];

            _renderer.addObject(
                PrimitiveFactory::createPlane()
                    ->setNormal(normalX, normalY, normalZ)
                    .setOrigin(originX, originY, originZ)
                    .setColor(getColor(planeSetting["color"]))
                    .setMaterial(getMaterial(planeSetting["material"]))
                    .build()
            );
        }
    }

    void Parser::addModels(const libconfig::Setting& primitivesSetting)
    {
        const libconfig::Setting& modelsSetting = primitivesSetting["models"];

        for (int i = 0; i < modelsSetting.getLength(); ++i) {
            const libconfig::Setting& modelSetting = modelsSetting[i];
            std::string path = modelSetting["path"];
            double x = modelSetting["x"];
            double y = modelSetting["y"];
            double z = modelSetting["z"];
            auto obj = OBJparser::parse(path);
            obj->translate(Math::Vector3(x, y, z));
            obj->setMaterial(getMaterial(modelSetting["material"]));
            _renderer.addObject(obj);
        }
    }

    void Parser::addPointLights(const libconfig::Setting& lightsSetting)
    {
        const libconfig::Setting& pointsSetting = lightsSetting["points"];

        for (int i = 0; i < pointsSetting.getLength(); i++) {
            const libconfig::Setting& pointSetting = pointsSetting[i];
            double x = pointSetting["x"];
            double y = pointSetting["y"];
            double z = pointSetting["z"];

            _renderer.addLight(
                LightFactory::createPoint()
                    ->setPosition(x, y, z)
                    .setColor(getColor(pointSetting["color"]))
                    .setIntensity(pointSetting["intensity"])
                    .setFalloff(pointSetting["falloff"])
                    .setRadius(pointSetting["radius"])
                    .build()
            );
        }
    }

    void Parser::addDirectionalLights(const libconfig::Setting& lightsSetting)
    {
        const libconfig::Setting& directionalLights = lightsSetting["directionals"];

        for (int i = 0; i < directionalLights.getLength(); i++) {
            const libconfig::Setting& directionalLight = directionalLights[i];
            double x = directionalLight["x"];
            double y = directionalLight["y"];
            double z = directionalLight["z"];
            _renderer.addLight(
                LightFactory::createDirectional()
                    ->setDirection(x, y, z)
                    .setIntensity(directionalLight["intensity"])
                    .setColor(getColor(directionalLight["color"]))
                    .build()
            );
        }
    }

    Renderer& Parser::getRenderer()
    {
        return _renderer;
    }
}
