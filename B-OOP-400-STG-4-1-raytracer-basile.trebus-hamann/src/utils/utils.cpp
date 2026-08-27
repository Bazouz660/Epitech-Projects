/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** utils
*/

#include "utils.hpp"

namespace RayTracer
{
    namespace Utils
    {
        bool equal(double a, double b) {
            if (a - b < 0.0001 && a - b > -0.0001)
                return true;
            return false;
        }

        int randBetween(int minNum, int maxNum)
        {
            int result = 0;
            int lowNum = 0;
            int hiNum = 0;

            if (minNum < maxNum) {
                lowNum = minNum;
                hiNum = maxNum + 1;
            } else {
                lowNum = maxNum + 1;
                hiNum = minNum;
            }
            result = (rand() % (hiNum - lowNum)) + lowNum;
            return result;
        }

        std::vector<std::string> split(const std::string& line, const std::string& delim) {
            std::vector<std::string> tokens;
            std::string token;
            for (char c : line) {
                if (delim.find(c) == std::string::npos) {
                    token += c;
                } else {
                    if (!token.empty()) {
                        tokens.push_back(token);
                        token.clear();
                    }
                }
            }
            if (!token.empty())
                tokens.push_back(token);
            return tokens;
        }

    }
}