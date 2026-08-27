/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** parsing
*/

#ifndef PARSING_HPP_
    #define PARSING_HPP_

    #include "common.hpp"

    namespace zpy::parsing {

        static std::string removeExtension(const std::string& filename) {
            size_t lastdot = filename.find_last_of(".");
            if (lastdot == std::string::npos) return filename;
            return filename.substr(0, lastdot);
        }

        static std::vector<std::string> strSplit(const std::string& str,
            const std::string& separators, bool keepInQuotes)
        {
            std::vector<std::string> words;
            bool inQuotes = false;
            std::string word;

            for (char c : str) {
                bool isSep = separators.find(c) != std::string::npos;
                if (c == '"' && keepInQuotes) {
                    inQuotes = !inQuotes;
                    continue;
                }
                if (isSep && !inQuotes) {
                    if (!word.empty()) {
                        words.push_back(word);
                        word.clear();
                    }
                } else
                    word += c;
            }
            if (!word.empty())
                words.push_back(word);
            return words;
        }

    }

#endif /* !PARSING_HPP_ */
