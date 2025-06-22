/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Algo.cpp - Version Simplifiée
*/

#include "Algo.hpp"
#include "Player.hpp"
#include "Lib.hpp"

Algo::Algo() : _player(nullptr), _testCounter(0)
{
}

Algo::~Algo()
{
}

void Algo::setPlayer(Player* player)
{
    _player = player;
}

void Algo::run()
{
    if (!_player) {
        ERROR << "Player not set in Algo::run()";
        return;
    }

    DEBUG << "Starting simple test algorithm...";
    
    _player->inventory();
    
    for (int i = 0; i < 10000000 && _player->isAlive(); ++i) {
    }
    
    _player->look();
    
    for (int i = 0; i < 10000000 && _player->isAlive(); ++i) {
    }
    
    _player->forward();
    
    for (int i = 0; i < 10000000 && _player->isAlive(); ++i) {
    }
    
    DEBUG << "Simple test completed.";
    
    while (_player->isAlive()) {
        for (int i = 0; i < 100000000 && _player->isAlive(); ++i) {
        }
    }
}

void Algo::testMovementCommands()
{
    logTest("Movement Commands");

    DEBUG << "Testing forward command...";
    _player->forward();

    DEBUG << "Testing right turn...";
    _player->right();

    DEBUG << "Testing left turn...";
    _player->left();

    DEBUG << "Testing another forward...";
    _player->forward();
}

void Algo::testLookCommand()
{
    logTest("Look Command");
    DEBUG << "Testing look command...";
    _player->look();
}

void Algo::testInventoryCommand()
{
    logTest("Inventory Command");
    DEBUG << "Testing inventory command...";
    _player->inventory();
}

void Algo::testTakeSetCommands()
{
    logTest("Take/Set Commands");

    std::vector<std::string> resources = {
        "food", "linemate", "deraumere", "sibur", 
        "mendiane", "phiras", "thystame"
    };

    for (const auto& resource : resources) {
        DEBUG << "Testing take command for: " << resource;
        _player->take(resource);
    }

    for (const auto& resource : resources) {
        DEBUG << "Testing set command for: " << resource;
        _player->set(resource);
    }
}

void Algo::testBroadcastCommand()
{
    logTest("Broadcast Command");
    DEBUG << "Testing broadcast command...";
    _player->broadcast("Hello from AI test!");
}

void Algo::testConnectNbrCommand()
{
    logTest("Connect_nbr Command");
    DEBUG << "Testing connect_nbr command...";
    _player->connect_nbr();
}

void Algo::testEjectCommand()
{
    logTest("Eject Command");
    DEBUG << "Testing eject command...";
    _player->eject();
}

void Algo::testForkCommand()
{
    logTest("Fork Command");
    DEBUG << "Testing fork command...";
    _player->fork();
}

void Algo::testIncantationCommand()
{
    logTest("Incantation Command");
    DEBUG << "Testing incantation command...";
    _player->incantation();
}

void Algo::logTest(const std::string& testName)
{
    _testCounter++;
    DEBUG << "=== TEST " << _testCounter << ": " << testName << " ===";
}