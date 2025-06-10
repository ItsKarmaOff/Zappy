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
    std::string command = "Broadcast " + message + "\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::eject()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Eject\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::fork()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Fork\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::inventory()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Inventory\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::look()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Look\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::forward()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Forward\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::right()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Right\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::left()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Left\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::connect_nbr()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Connect_nbr\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::take(const std::string &item)
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Take " + item + "\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::set(const std::string &item)
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Set " + item + "\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}

void CommandsManager::incantation()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Incantation\n";
    send(_clientSocket->getSocket(), command.c_str(), command.size(), 0);
}