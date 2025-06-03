/*
** EPITECH PROJECT, 2025
** Commands.cpp
** File description:
** Commands implementation
*/

#include "Commands.hpp"
#include "Graphics.hpp"
#include "Logs.hpp"
#include <cstdlib>
#include <functional>
#include <unordered_map>

namespace Gui
{
    Commands::Commands(Graphics &graphical)
        : _graphical(graphical)
    {
        _commandHandlers = {
            {MSZ, [this](std::string &param) { handleMSZ(param); }},
            {BCT, [this](std::string &param) { handleBCT(param); }},
            {TNA, [this](std::string &param) { handleTNA(param); }},
            {PNW, [this](std::string &param) { handlePNW(param); }},
            {PPO, [this](std::string &param) { handlePPO(param); }},
            {PLV, [this](std::string &param) { handlePLV(param); }},
            {PIN, [this](std::string &param) { handlePIN(param); }},
            {PEX, [this](std::string &param) { handlePEX(param); }},
            {PBC, [this](std::string &param) { handlePBC(param); }},
            {PIC, [this](std::string &param) { handlePIC(param); }},
            {PIE, [this](std::string &param) { handlePIE(param); }},
            {PFK, [this](std::string &param) { handlePFK(param); }},
            {PDR, [this](std::string &param) { handlePDR(param); }},
            {PGT, [this](std::string &param) { handlePGT(param); }},
            {PDI, [this](std::string &param) { handlePDI(param); }},
            {ENW, [this](std::string &param) { handleENW(param); }},
            {EBO, [this](std::string &param) { handleEBO(param); }},
            {EDI, [this](std::string &param) { handleEDI(param); }},
            {SGT, [this](std::string &param) { handleSGT(param); }},
            {SST, [this](std::string &param) { handleSST(param); }},
            {SEG, [this](std::string &param) { handleSEG(param); }},
            {SMG, [this](std::string &param) { handleSMG(param); }},
            {SUC, [this](std::string &param) { handleSUC(param); }},
            {SDP, [this](std::string &param) { handleSDP(param); }}
        };
    }
    void Commands::handleCommand(std::shared_ptr<QueueManager> &queueManager)
    {
        while (queueManager->hasResponses()) {
            std::string response = queueManager->popResponse();
            size_t spacePos = response.find(' ');
            std::string command = (spacePos != std::string::npos) ? response.substr(0, spacePos) : response;
            std::string param = (spacePos != std::string::npos) ? response.substr(spacePos + 1) : "";

            if (_commandHandlers.contains(command)) {
                _commandHandlers[command](param);
            } else {
                ERROR << "Unknown command: " << command;
            }
        }
    }

    void Commands::handleMSZ(std::string &param)
    {
        DEBUG << "Handling MSZ command with param: " << param;

        std::istringstream iss(param);
        int width;
        int height;

        if (!(iss >> width >> height))
            ERROR << "Invalid parameters for MSZ command: " << param;

        if (width <= 0 || height <= 0)
            ERROR << "Invalid dimensions for MSZ command: " << width << "x" << height;

        DEBUG_CONCAT << "Map size set to: " << width << "x" << height;
        _graphical.getGame()->getMapSize() = {static_cast<float>(width), static_cast<float>(height)};

    }

    void Commands::handleBCT(std::string &param)
    {

    }

    void Commands::handleTNA(std::string &param)
    {
        DEBUG << "Handling TNA command with param: " << param;

        std::istringstream iss(param);
        std::string teamName;

        if (!(iss >> teamName))
            ERROR << "Invalid parameters for TNA command: " << param;

        if (teamName.empty())
            ERROR << "Team name cannot be empty for TNA command";

        DEBUG_CONCAT << "Team name set to: " << teamName;
    }

    void Commands::handlePNW(std::string &param)
    {

    }

    void Commands::handlePPO(std::string &param)
    {

    }

    void Commands::handlePLV(std::string &param)
    {
        DEBUG << "Handling PLV command with param: " << param;

        std::istringstream iss(param);
        std::string player;
        int playerId;
        int level;

        if (!(iss >> player >> level))
            ERROR << "Invalid parameters for PLV command: " << param;

        if (player.empty() || player[0] != '#' || player.size() < 2)
            ERROR << "Invalid player format for PLV command: " << player;

        if (level < 1 || level > 8)
            ERROR << "Invalid level for PLV command: " << level;

        playerId = std::stoi(player.substr(1));

        DEBUG_CONCAT << "Player #" << playerId << " level set to: " << level;
    }

    void Commands::handlePIN(std::string &param)
    {

    }

    void Commands::handlePEX(std::string &param)
    {
        DEBUG << "Handling PEX command with param: " << param;

        std::istringstream iss(param);
        std::string player;
        int playerId;

        if (!(iss >> player))
            ERROR << "Invalid parameters for PEX command: " << param;

        if (player.empty() || player[0] != '#' || player.size() < 2)
            ERROR << "Invalid player format for PEX command: " << player;

        playerId = std::stoi(player.substr(1));

        DEBUG_CONCAT << "Player #" << playerId << " has been expelled";
    }

    void Commands::handlePBC(std::string &param)
    {
        DEBUG << "Handling PBC command with param: " << param;

        std::istringstream iss(param);
        std::string player;
        int playerId;
        std::string message;

        if (!(iss >> player >> message))
            ERROR << "Invalid parameters for PBC command: " << param;

        if (player.empty() || player[0] != '#' || player.size() < 2)
            ERROR << "Invalid player format for PBC command: " << player;

        if (message.empty())
            ERROR << "Message cannot be empty for PBC command";

        playerId = std::stoi(player.substr(1));

        DEBUG << "Player #" << playerId << " message set to: " << message;
    }

    void Commands::handlePIC(std::string &param)
    {

    }

    void Commands::handlePIE(std::string &param)
    {
        DEBUG << "Handling PIE command with param: " << param;

        std::istringstream iss(param);
        std::string player;
        int playerId;
        int x;
        int y;
        int r;

        if (!(iss >> player >> x >> y >> r))
            ERROR << "Invalid parameters for PIE command: " << param;

        if (player.empty() || player[0] != '#' || player.size() < 2)
            ERROR << "Invalid player format for PIE command: " << player;

        if (x < 0 || y < 0 || r < 0)
            ERROR << "Invalid coordinates or radius for PIE command: " << x << ", " << y << ", " << r;

        playerId = std::stoi(player.substr(1));

        DEBUG_CONCAT << "Player #" << playerId << " position set to: (" << x << ", " << y << ") with incantation result " << r;
    }

    void Commands::handlePFK(std::string &param)
    {

    }

    void Commands::handlePDR(std::string &param)
    {

    }

    void Commands::handlePGT(std::string &param)
    {

    }

    void Commands::handlePDI(std::string &param)
    {

    }

    void Commands::handleENW(std::string &param)
    {

    }

    void Commands::handleEBO(std::string &param)
    {

    }

    void Commands::handleEDI(std::string &param)
    {

    }

    void Commands::handleSGT(std::string &param)
    {

    }

    void Commands::handleSST(std::string &param)
    {

    }

    void Commands::handleSEG(std::string &param)
    {

    }

    void Commands::handleSMG(std::string &param)
    {

    }

    void Commands::handleSUC(std::string &param)
    {

    }

    void Commands::handleSDP(std::string &param)
    {

    }
}
