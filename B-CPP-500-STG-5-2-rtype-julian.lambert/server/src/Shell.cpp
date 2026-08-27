/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** Shell
*/

#include "Shell.hpp"
#include <iostream>
#include <sstream>
#include "logger.hpp"

#include <atomic>

namespace rtype {

    std::atomic<bool> shouldStop = false;

    Shell::~Shell()
    {
        stop();
        join();
    }

    void Shell::join()
    {
        if (m_commandThread.joinable())
            m_commandThread.join();
    }

    void Shell::addCommand(const std::string &name, std::function<void(std::vector<std::string>)> command)
    {
        m_commands[name] = command;
    }

    void Shell::start()
    {
        m_commandThread = std::thread([this](){
            std::string line;
            while (!shouldStop) {
                if (!std::getline(std::cin, line))
                    break;

                if (line.empty())
                    continue;

                std::vector<std::string> args;
                std::istringstream iss(line);
                std::string arg;
                while (iss >> arg)
                    args.push_back(arg);
                if (args.size() > 0 && m_commands.find(args[0]) != m_commands.end())
                    m_commands[args[0]](args);
                else
                    exng::logger::error() << args[0] << ": command not found";

                if (shouldStop)
                    break;
            }
        });
    }

    void Shell::stop()
    {
        shouldStop = true;
    }

    std::vector<std::pair<std::string, std::function<void(std::vector<std::string>)>>> Shell::getCommands() const
    {
        std::vector<std::pair<std::string, std::function<void(std::vector<std::string>)>>> commands;
        for (auto &command : m_commands)
            commands.push_back(command);
        return commands;
    }
}