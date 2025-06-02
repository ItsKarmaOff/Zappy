/*
** EPITECH PROJECT, 2025
** Commands.cpp
** File description:
** Commands implementation
*/

#include "Commands.hpp"
#include "Graphics.hpp"
#include "Logs.hpp"
#include <functional>
#include <unordered_map>

namespace Gui
{
    Commands::Commands()
    {
        _commandHandlers = {
            {MSZ, [this](std::string param) { handleMSZ(param); }},
            {BCT, [this](std::string param) { handleBCT(param); }},
            {TNA, [this](std::string param) { handleTNA(param); }},
            {PNW, [this](std::string param) { handlePNW(param); }},
            {PPO, [this](std::string param) { handlePPO(param); }},
            {PLV, [this](std::string param) { handlePLV(param); }},
            {PIN, [this](std::string param) { handlePIN(param); }},
            {PEX, [this](std::string param) { handlePEX(param); }},
            {PBC, [this](std::string param) { handlePBC(param); }},
            {PIC, [this](std::string param) { handlePIC(param); }},
            {PIE, [this](std::string param) { handlePIE(param); }},
            {PFK, [this](std::string param) { handlePFK(param); }},
            {PDR, [this](std::string param) { handlePDR(param); }},
            {PGT, [this](std::string param) { handlePGT(param); }},
            {PDI, [this](std::string param) { handlePDI(param); }},
            {ENW, [this](std::string param) { handleENW(param); }},
            {EBO, [this](std::string param) { handleEBO(param); }},
            {EDI, [this](std::string param) { handleEDI(param); }},
            {SGT, [this](std::string param) { handleSGT(param); }},
            {SST, [this](std::string param) { handleSST(param); }},
            {SEG, [this](std::string param) { handleSEG(param); }},
            {SMG, [this](std::string param) { handleSMG(param); }},
            {SUC, [this](std::string param) { handleSUC(param); }},
            {SDP, [this](std::string param) { handleSDP(param); }}
        };
    }
    void Commands::handleCommand(std::shared_ptr<QueueManager> &queueManager, Graphics &graphics)
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

    void Commands::handleMSZ(std::string param)
    {

    }

    void Commands::handleBCT(std::string param)
    {

    }

    void Commands::handleTNA(std::string param)
    {

    }

    void Commands::handlePNW(std::string param)
    {

    }

    void Commands::handlePPO(std::string param)
    {

    }

    void Commands::handlePLV(std::string param)
    {

    }

    void Commands::handlePIN(std::string param)
    {

    }

    void Commands::handlePEX(std::string param)
    {

    }

    void Commands::handlePBC(std::string param)
    {

    }

    void Commands::handlePIC(std::string param)
    {

    }

    void Commands::handlePIE(std::string param)
    {

    }

    void Commands::handlePFK(std::string param)
    {

    }

    void Commands::handlePDR(std::string param)
    {

    }

    void Commands::handlePGT(std::string param)
    {

    }

    void Commands::handlePDI(std::string param)
    {

    }

    void Commands::handleENW(std::string param)
    {

    }

    void Commands::handleEBO(std::string param)
    {

    }

    void Commands::handleEDI(std::string param)
    {

    }

    void Commands::handleSGT(std::string param)
    {

    }

    void Commands::handleSST(std::string param)
    {

    }

    void Commands::handleSEG(std::string param)
    {

    }

    void Commands::handleSMG(std::string param)
    {

    }

    void Commands::handleSUC(std::string param)
    {

    }

    void Commands::handleSDP(std::string param)
    {

    }
}
