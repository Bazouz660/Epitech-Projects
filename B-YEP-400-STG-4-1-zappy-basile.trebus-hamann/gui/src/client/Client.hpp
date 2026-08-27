/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Client
*/

#pragma once

#include "common.hpp"
#include "Chrono.hpp"
#include <map>

#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <sys/select.h>
#include <signal.h>

namespace zpy {

    class Renderer;

    class Client {
        public:
            typedef std::function<void(const std::vector<std::string>&)> CommandFunction;

            Client(Renderer& renderer);
            ~Client();

            void init(int port, const std::string& ip);
            void connect();
            void authentify();
            void update();
            bool isAuthentified();
            bool shouldClose();

        private:
            void initSignals();
            void checkErr(int val, const std::string& msg);
            void updateSet();
            void clearSet();
            void selectSet();
            void listenFd();
            void readData(int fd, std::string &msg);
            std::string receive();
            void send(const std::string& msg);

            void handleData();
            void processCommand(const std::string& command, const std::vector<std::string>& args);

            void sendCommands();

        // commands
        private:
            // map size
            void msz(std::vector<std::string> args);
            // tile content
            void bct(std::vector<std::string> args);
            // name of all teams
            void tna(std::vector<std::string> args);
            // connection of a new player
            void pnw(std::vector<std::string> args);
            // player position
            void ppo(std::vector<std::string> args);
            // player level
            void plv(std::vector<std::string> args);
            // player inventory
            void pin(std::vector<std::string> args);
            // explusion
            void pex(std::vector<std::string> args);
            // broadcast
            void pbc(std::vector<std::string> args);
            // start of incantation (by the first player)
            void pic(std::vector<std::string> args);
            // end of incantation
            void pie(std::vector<std::string> args);
            // egg laying by player (fork)
            void pfk(std::vector<std::string> args);
            // resource dropping
            void pdr(std::vector<std::string> args);
            // resource collecting
            void pgt(std::vector<std::string> args);
            // death of a player
            void pdi(std::vector<std::string> args);
            // an egg was laid by player
            void enw(std::vector<std::string> args);
            // player connected for an egg
            void ebo(std::vector<std::string> args);
            // death of an egg
            void edi(std::vector<std::string> args);
            // time unit request
            void sgt(std::vector<std::string> args);
            // end of game
            void seg(std::vector<std::string> args);
            // message from server
            void smg(std::vector<std::string> args);
            // unknown command
            void suc(std::vector<std::string> args);
            // bad parameter
            void sbp(std::vector<std::string> args);

        private:
            bool m_running;
            int m_socket;
            int m_port;
            int m_maxSocket;
            std::string m_ip;
            struct sockaddr_in m_sockaddrIn;
            size_t m_addrSize;
            fd_set m_fdSet;

            struct sigaction m_sigIntHandler;

            struct timeval m_timeout;
            Chrono m_authTimeout;

            std::map<std::string, CommandFunction> m_commands;

            bool m_auth;
            std::string m_data;

            Renderer& m_renderer;
    };

}