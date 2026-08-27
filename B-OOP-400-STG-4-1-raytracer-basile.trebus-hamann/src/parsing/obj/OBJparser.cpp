/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** OBJparser
*/

#include "OBJparser.hpp"
#include "PrimitiveFactory.hpp"
#include <fstream>
#include <regex>
#include "utils.hpp"
#include <queue>

namespace RayTracer {

    void OBJparser::parseFace(const std::string& line,
        const std::vector<sptr<Math::Vector3<double>>>& vertices,
        const std::vector<sptr<Math::Vector3<double>>>& normals,
        std::vector<sptr<Face>>& faces)
    {
        if (line.front() != 'f')
            return;

        static std::queue<std::string> tokenQueue;
        std::vector<std::string> tokens = Utils::split(line, " ");
        tokens.erase(tokens.begin());
        for (auto& token : tokens)
            tokenQueue.push(token);

        //std::cerr << "tokens: " << tokens.size() << std::endl;
        //for (auto& token : tokens)
        //    std::cerr << " " << "-" << token << "-" << std::endl;

        // create faces from tokens (we package 3 tokens into a face and keep the rest in the buffer)
        sptr<Face> face = std::make_shared<Face>();

        // each token represents a vertex/normal/uv
        //std::cerr << "reading new face" << std::endl;
        for (int i = 0; i < 3; i++)
        {
            std::string token = tokenQueue.front();
            tokenQueue.pop();

            std::string vertexStr = token.substr(0, token.find('/'));
            std::string uvStr = token.substr(token.find('/') + 1, token.find_last_of('/') - token.find('/') - 1);
            std::string normalStr = token.substr(token.find_last_of('/') + 1);

            //std::cerr << "vertex: " << vertexStr << std::endl;
            //std::cerr << "uv: " << uvStr << std::endl;
            //std::cerr << "normal: " << normalStr << std::endl;

            face->vertices.push_back(vertices[std::stoi(vertexStr) - 1]);
            face->normals.push_back(normals[std::stoi(normalStr) - 1]);
        }
        faces.push_back(std::move(face));
    }

    sptr<Scene> OBJparser::parse(const std::string& path)
    {
        std::ifstream file(path);
        std::string line;

        if (!file.is_open())
            throw std::runtime_error(path + ": File not found");

        std::vector<sptr<Math::Vector3<double>>> vertices;
        std::vector<sptr<Math::Vector3<double>>> normals;
        std::vector<sptr<Face>> faces;

        // v 0.102948 1.611722 0.042643
        std::regex vertexRegex(R"(v\s+(-?\d+\.\d+)\s+(-?\d+\.\d+)\s+(-?\d+\.\d+))");
        std::regex normalRegex(R"(vn\s+(-?\d+\.\d+)\s+(-?\d+\.\d+)\s+(-?\d+\.\d+))");

        while (std::getline(file, line)) {
            std::smatch match;
            if (line.back() == '\n')
                line.pop_back();
            if (line.back() == '\r')
                line.pop_back();

            if (std::regex_match(line, match, vertexRegex)) {
                // blender uses Z as up axis, so we swap Y and Z, also, Y is inverted
                vertices.push_back(std::make_shared<Math::Vector3<double>>(
                    std::stod(match[1]), std::stod(match[2]) * -1, std::stod(match[3])));
            }
            if (std::regex_match(line, match, normalRegex)) {
                normals.push_back(std::make_shared<Math::Vector3<double>>(
                    std::stod(match[1]), std::stod(match[2]) * -1, std::stod(match[3])));
            }
            parseFace(line, vertices, normals, faces);
        }

        std::cerr << "found " << faces.size() << " faces" << std::endl;

        return buildFromData(vertices, normals, faces);
    }

    sptr<Scene> OBJparser::buildFromData(
        const std::vector<sptr<Math::Vector3<double>>>& vertices,
        const std::vector<sptr<Math::Vector3<double>>>& normals,
        const std::vector<sptr<Face>>& faces)
    {
        sptr<Scene> scene = std::make_shared<Scene>();

        int i = 0;
        for (auto& face : faces) {
            //std::cerr << "Face: " << i << std::endl;
            //std::cerr << "  vA: " << face->vA << std::endl;
            //std::cerr << "  vB: " << face->vB << std::endl;
            //std::cerr << "  vC: " << face->vC << std::endl;

            //Color::RGB color = Color::RGB(Utils::randBetween(0, 255), Utils::randBetween(0, 255), Utils::randBetween(0, 255));

            sptr<IPrimitive> triangle = PrimitiveFactory::createTriangle()
                ->setA(*face->vertices[0].get())
                .setB(*face->vertices[1].get())
                .setC(*face->vertices[2].get())
                .setNA(*face->normals[0].get())
                .setNB(*face->normals[1].get())
                .setNC(*face->normals[2].get())
                .setColor(Color::RGB(255, 255, 255))
                .build();

            scene->addObject(triangle);
            i++;
        }

        return scene;
    }

}