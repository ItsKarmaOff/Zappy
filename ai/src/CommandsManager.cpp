/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Commands
*/

#include "CommandsManager.hpp"

CommandsManager::CommandsManager(std::shared_ptr<Lib::Socket> clientSocket)
    : _clientSocket(clientSocket)
{
}

CommandsManager::~CommandsManager()
{
}

void CommandsManager::broadcast(const std::string &message)
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "broadcast " + message + "\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::eject()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "eject\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::fork()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "fork\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::inventory()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "inventory\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::look()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "look\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::forward()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "forward\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::right()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "right\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::left()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "left\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::connect_nbr()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "connect_nbr\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::take(const std::string &item)
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "take " + item + "\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::set(const std::string &item)
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "set " + item + "\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::incantation()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "incantation\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}