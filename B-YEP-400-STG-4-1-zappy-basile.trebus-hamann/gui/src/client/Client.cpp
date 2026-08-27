/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4{-1-zappy-basile.trebus-hamann
** File description:
** Client
*/

#include "Client.hpp"
#include "Renderer.hpp"
#include "utils/parsing.hpp"
#include "string.h"
#include <fcntl.h>
#include <iomanip>

#define CHECK(exp, msg) Client::checkErr(exp, msg)

namespace zpy {

    static bool shouldRun = true;

    Client::Client(Renderer& renderer)
    : m_renderer(renderer), m_running(false)
    {
        initSignals();

        m_auth = false;
        m_maxSocket = 0;
        m_timeout.tv_sec = 0;
        m_timeout.tv_usec = 0;

        m_commands["msz"] = [this](const std::vector<std::string>& args) { msz(args); };
        m_commands["bct"] = [this](const std::vector<std::string>& args) { bct(args); };
        m_commands["tna"] = [this](const std::vector<std::string>& args) { tna(args); };
        m_commands["pnw"] = [this](const std::vector<std::string>& args) { pnw(args); };
        m_commands["ppo"] = [this](const std::vector<std::string>& args) { ppo(args); };
        m_commands["plv"] = [this](const std::vector<std::string>& args) { plv(args); };
        m_commands["pin"] = [this](const std::vector<std::string>& args) { pin(args); };
        m_commands["pex"] = [this](const std::vector<std::string>& args) { pex(args); };
        m_commands["pbc"] = [this](const std::vector<std::string>& args) { pbc(args); };
        m_commands["pic"] = [this](const std::vector<std::string>& args) { pic(args); };
        m_commands["pie"] = [this](const std::vector<std::string>& args) { pie(args); };
        m_commands["pfk"] = [this](const std::vector<std::string>& args) { pfk(args); };
        m_commands["pdr"] = [this](const std::vector<std::string>& args) { pdr(args); };
        m_commands["pgt"] = [this](const std::vector<std::string>& args) { pgt(args); };
        m_commands["pdi"] = [this](const std::vector<std::string>& args) { pdi(args); };
        m_commands["enw"] = [this](const std::vector<std::string>& args) { enw(args); };
        m_commands["ebo"] = [this](const std::vector<std::string>& args) { ebo(args); };
        m_commands["edi"] = [this](const std::vector<std::string>& args) { edi(args); };
        m_commands["sgt"] = [this](const std::vector<std::string>& args) { sgt(args); };
        m_commands["seg"] = [this](const std::vector<std::string>& args) { seg(args); };
        m_commands["smg"] = [this](const std::vector<std::string>& args) { smg(args); };
        m_commands["suc"] = [this](const std::vector<std::string>& args) { suc(args); };
        m_commands["sbp"] = [this](const std::vector<std::string>& args) { sbp(args); };
    }

    Client::~Client()
    {
        if (m_socket != -1)
            close(m_socket);
    }

    bool Client::shouldClose()
    {
        m_running = shouldRun;
        return !m_running;
    }

    void Client::checkErr(int exp, const std::string& msg)
    {
        if (exp == -1 && errno != EINPROGRESS)
            throw std::runtime_error(msg + ": " + strerror(errno) + " (" + std::to_string(errno) + ")"
            + "\nPlease check if the server is running, and if the host is correct.");
    }

    void Client::init(int port, const std::string& ip)
    {
        m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        m_addrSize = sizeof(m_sockaddrIn);

        m_ip = ip;
        m_port = port;

        CHECK(m_socket, "Socket creation failed");
        m_sockaddrIn.sin_family = AF_INET;
        CHECK(port, "Invalid port");
        m_sockaddrIn.sin_port = htons(port);

        if (ip == "localhost") {
            m_sockaddrIn.sin_addr.s_addr = inet_addr("127.0.0.1");
        } else {
            CHECK(inet_addr(ip.c_str()), "Invalid IP");
            m_sockaddrIn.sin_addr.s_addr = inet_addr(ip.c_str());
        }

        m_running = true;
    }

    void Client::connect()
    {
        fcntl(m_socket, F_SETFL, O_NONBLOCK);

        int short status;
        do {
            status = ::connect(m_socket, (struct sockaddr *)&m_sockaddrIn, m_addrSize);
            CHECK(status, "Connection failed");
        } while (status != 0);

        std::cerr << "connected to server" << std::endl;
    }

    void Client::authentify()
    {
        std::cout << std::setw(10) << std::left << "Waiting for authentification...\n" << std::flush;

        m_authTimeout.start();

	    while (!isAuthentified()) {
	    	update();

            std::cerr << "m_data: <" << m_data << ">" << std::endl;

            m_authTimeout.timeOut(5, [&]() {
                throw std::runtime_error("Authentification timeout");
            });

            if (!m_auth && m_data == "WELCOME") {
                m_auth = true;
                send("GRAPHIC\n\r");
                std::cerr << "-------------< Authentified >---------------" << std::endl;
            }
	    }
    }

    void Client::initSignals()
    {
        m_sigIntHandler.sa_handler = [](int) {
            std::cout << std::endl;
            shouldRun = false;
        };
        sigemptyset(&m_sigIntHandler.sa_mask);
        m_sigIntHandler.sa_flags = 0;
        sigaction(SIGINT, &m_sigIntHandler, NULL);
    }

    void Client::send(const std::string& msg)
    {
        std::string tmp = msg + "\n";
        CHECK(::send(m_socket, tmp.c_str(), tmp.size(), 0), "Send failed");
    }

    void Client::clearSet()
    {
        FD_ZERO(&m_fdSet);
        FD_SET(m_socket, &m_fdSet);
    }

    void Client::updateSet()
    {
        int sd = 0;

        for (int i = 0; i < 2; i++) {
            if (i == 0)
                sd = m_socket;
            else
                sd = 0;
            FD_SET(sd, &m_fdSet);
            if (sd > m_maxSocket)
                m_maxSocket = sd;
        }
    }

    void Client::selectSet()
    {
        if (select((m_maxSocket) + 1, &m_fdSet, NULL, NULL, &m_timeout) < 0) {
            close(m_socket);
            exit(0);
        }
    }

    std::string Client::receive()
    {
        const int BUFFER_SIZE = 1024;
        char buffer[BUFFER_SIZE];

        std::string receivedData;
        int bytesRead;

        while ((bytesRead = recv(m_socket, buffer, BUFFER_SIZE, 0)) > 0) {
            receivedData.append(buffer, bytesRead);
            if (receivedData.back() == '\n')
                break;
            if (bytesRead < BUFFER_SIZE)
                break;
        }

        if (bytesRead <= 0)
            throw std::runtime_error("Connection lost");

        receivedData.pop_back();

        //std::cerr << "receivedData: <" << receivedData << ">" << std::endl;

        return receivedData;
    }

    void Client::readData(int fd, std::string &msg)
    {
        if (fd == m_socket) {
            msg = receive();
        } else {
            std::string command;
            if (std::getline(std::cin, command))
                send(command);
        }
    }

    void Client::listenFd()
    {
        int fd;

        for (int i = 0; i < 2; i++) {
            if (i == 0)
                fd = m_socket;
            else
                fd = 0;
            if ((FD_ISSET(fd, &m_fdSet)))
                readData(fd, m_data);
        }
    }

    void Client::processCommand(const std::string& command, const std::vector<std::string>& args)
    {
        if (m_commands.find(command) != m_commands.end()) {
            CommandFunction function = m_commands[command];
            //std::cerr << "processing command: " << command << std::endl;
            function(args);
        } else {
            std::cerr << "Unknown command received from server: " << command << std::endl;
        }
    }

    void Client::handleData()
    {
        if (m_auth == false || m_data.empty())
            return;

        // split each line
        std::vector<std::string> lines = parsing::strSplit(m_data, "\n", false);

        for (const std::string& line : lines) {
            // split each word
            std::vector<std::string> words = parsing::strSplit(line, " ", true);

            if (words.size() > 0) {
                std::string command = words[0];
                words.erase(words.begin());
                processCommand(command, words);
            }
        }

        m_data.clear();
    }

    void Client::sendCommands()
    {
        if (m_auth == false)
            return;
    }

    void Client::update()
    {
        updateSet();
        selectSet();
        listenFd();
        handleData();
        sendCommands();
    }

    bool Client::isAuthentified()
    {
        return m_auth;
    }

    void Client::msz(std::vector<std::string> data)
    {
        if (data.size() != 2)
            throw std::runtime_error("Invalid msz command");

        Grid& grid = m_renderer.getGrid();

        grid.setDimension(Vec2(std::stoi(data[0]), std::stoi(data[1])));
        grid.init();
    }

    void Client::bct(std::vector<std::string> data)
    {
        if (data.size() != 9)
            throw std::runtime_error("Invalid bct command");

        Grid& grid = m_renderer.getGrid();

        Vec2 pos(std::stoi(data[0]), std::stoi(data[1]));
        Tile& tile = grid.getTile(pos);

        tile.setResource(Resources::FOOD, std::stoi(data[2]));
        tile.setResource(Resources::LINEMATE, std::stoi(data[3]));
        tile.setResource(Resources::DERAUMERE, std::stoi(data[4]));
        tile.setResource(Resources::SIBUR, std::stoi(data[5]));
        tile.setResource(Resources::MENDIANE, std::stoi(data[6]));
        tile.setResource(Resources::PHIRAS, std::stoi(data[7]));
        tile.setResource(Resources::THYSTAME, std::stoi(data[8]));
    }

    void Client::tna(std::vector<std::string> data)
    {
        if (data.size() != 1)
            throw std::runtime_error("Invalid tna command");

        try {
            m_renderer.addTeam(data[0]);
            m_renderer.updateHudInfo();
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void Client::pnw(std::vector<std::string> data)
    {
        if (data.size() != 6)
            throw std::runtime_error("Invalid pnw command");

        int id = std::stoi(data[0]);
        Vec2 pos(std::stoi(data[1]), std::stoi(data[2]));
        Trantorian::Orientation orient = static_cast<Trantorian::Orientation>(std::stoi(data[3]));
        int level = std::stoi(data[4]);
        std::string team = data[5];

        std::cerr << "adding player:"
            << "\nid: " << id
            << "\npos x: " << pos.x
            << "\npos y: " << pos.y
            << "\norient: " << orient
            << "\nlevel: " << level
            << "\nteam: " << team << std::endl;

        m_renderer.addPlayer(pos, orient, level, id, team);
    }

    void Client::ppo(std::vector<std::string> data)
    {
        if (data.size() != 4)
            throw std::runtime_error("Invalid ppo command");

        int id = std::stoi(data[0]);
        Vec2 pos(std::stoi(data[1]), std::stoi(data[2]));
        Trantorian::Orientation orient = static_cast<Trantorian::Orientation>(std::stoi(data[3]));

        sptr<Trantorian> player = m_renderer.getPlayer(id);

        if (player) {
            player->setOrientation(orient);
            player->setPos(pos);
        }
    }

    void Client::plv(std::vector<std::string> data)
    {
        if (data.size() != 2)
            throw std::runtime_error("Invalid plv command");

        int id = std::stoi(data[0]);
        int level = std::stoi(data[1]);

        sptr<Trantorian> player = m_renderer.getPlayer(id);

        if (player)
            player->setLevel(level);
    }

    void Client::pin(std::vector<std::string> data)
    {
        if (data.size() != 10)
            throw std::runtime_error("Invalid pin command");

        int id = std::stoi(data[0]);
        Vec2 pos(std::stoi(data[1]), std::stoi(data[2]));
        int food = std::stoi(data[3]);
        int linemate = std::stoi(data[4]);
        int deraumere = std::stoi(data[5]);
        int sibur = std::stoi(data[6]);
        int mendiane = std::stoi(data[7]);
        int phiras = std::stoi(data[8]);
        int thystame = std::stoi(data[9]);

        sptr<Trantorian> player = m_renderer.getPlayer(id);

        if (player == nullptr)
            throw std::runtime_error("pin: Player not found");

        Inventory& inv = player->getInventory();

        inv.setFood(food);
        inv.setLinemate(linemate);
        inv.setDeraumere(deraumere);
        inv.setSibur(sibur);
        inv.setMendiane(mendiane);
        inv.setPhiras(phiras);
        inv.setThystame(thystame);
    }

    void Client::pex(std::vector<std::string> data)
    {
    }

    void Client::pbc(std::vector<std::string> data)
    {
    }

    void Client::pic(std::vector<std::string> data)
    {
    }

    void Client::pie(std::vector<std::string> data)
    {
    }

    void Client::pfk(std::vector<std::string> data)
    {
    }

    void Client::pdr(std::vector<std::string> data)
    {
    }

    void Client::pgt(std::vector<std::string> data)
    {
    }

    void Client::pdi(std::vector<std::string> data)
    {
        if (data.size() != 1)
            throw std::runtime_error("Invalid pdi command");

        int id = std::stoi(data[0]);

        std::vector<sptr<Trantorian>>& players = m_renderer.getPlayers();

        for (auto it = players.begin(); it != players.end(); ++it) {
            if ((*it)->getId() == id) {
                players.erase(it);
                break;
            }
        }
    }

    void Client::enw(std::vector<std::string> data)
    {
    }

    void Client::ebo(std::vector<std::string> data)
    {
    }

    void Client::edi(std::vector<std::string> data)
    {
    }

    void Client::sgt(std::vector<std::string> data)
    {
        if (data.size() != 1)
            throw std::runtime_error("Invalid sgt command");

        unsigned int freq = std::stoi(data[0]);

        m_renderer.setTimeUnit(freq);
        std::cerr << "freq: " << freq << std::endl;
    }

    void Client::seg(std::vector<std::string> data)
    {
        if (data.size() != 1)
            throw std::runtime_error("Invalid seg command");

        std::string team = data[0];

        m_renderer.setWinnerTeam(team);
    }

    void Client::smg(std::vector<std::string> data)
    {
        std::cerr << "Server: " << data[0] << std::endl;
    }

    void Client::suc(std::vector<std::string> data)
    {
        std::cerr << "Server error: unknown command" << std::endl;
    }

    void Client::sbp(std::vector<std::string> data)
    {
        std::cerr << "Server error: bad command parameter" << std::endl;
    }

}