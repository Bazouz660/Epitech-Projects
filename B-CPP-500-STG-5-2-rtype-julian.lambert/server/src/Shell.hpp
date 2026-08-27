/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** Shell
*/

#ifndef RTYPE_SERVER_SHELL_HPP
#define RTYPE_SERVER_SHELL_HPP

#include <map>
#include <functional>
#include <vector>
#include <string>
#include <memory>
#include <thread>

namespace rtype {
    class Shell {
        public:
            Shell() = default;
            ~Shell();

            void start();
            void stop();

            void addCommand(const std::string &name, std::function<void(std::vector<std::string>)> command);
            std::vector<std::pair<std::string, std::function<void(std::vector<std::string>)>>> getCommands() const;

        private:
            std::thread m_commandThread;
            std::map<std::string, std::function<void(std::vector<std::string>)>> m_commands;

            void join();
    };
}

#endif //RTYPE_SERVER_SHELL_HPP