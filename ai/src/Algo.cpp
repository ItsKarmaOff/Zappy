/*
** EPITECH PROJECT, 2024
** zappy [WSL: Ubuntu]
** File description:
** Algo.cpp
*/

#include "Algo.hpp"
#include "Player.hpp"
#include "Lib.hpp"

Algo::Algo() : _playerPtr(nullptr), _testCounter(0)
{
}

Algo::~Algo()
{
}

void Algo::setPlayer(std::shared_ptr<Player> player)
{
    _player = player;
}

void Algo::setPlayer(Player* player)
{
    _playerPtr = player;
}

void Algo::run()
{
    Player* player = _player ? _player.get() : _playerPtr;
    
    if (!player) {
        ERROR << "Player not set in Algo::run()";
        return;
    }

    DEBUG << "Starting command testing algorithm...";
    testLookCommand();
    testInventoryCommand();
    testMovementCommands();
    testBroadcastCommand();
    testConnectNbrCommand();
    testTakeSetCommands();
    testEjectCommand();
    testForkCommand();
    testIncantationCommand();
    
    DEBUG << "All command tests completed. Starting continuous cycle...";
    
    int cycleCount = 0;
    while (player->isAlive()) {
        cycleCount++;
        DEBUG << "=== Cycle " << cycleCount << " ===";
        player->look();
        player->inventory();
        player->forward();
        player->right();
        player->take("food");
    }
}

void Algo::testMovementCommands()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Movement Commands");
    
    DEBUG << "Testing forward command...";
    player->forward();
    
    DEBUG << "Testing right turn...";
    player->right();
    
    DEBUG << "Testing left turn...";
    player->left();
    
    DEBUG << "Testing another forward...";
    player->forward();
}

void Algo::testLookCommand()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Look Command");
    DEBUG << "Testing look command...";
    player->look();
}

void Algo::testInventoryCommand()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Inventory Command");
    DEBUG << "Testing inventory command...";
    player->inventory();
}

void Algo::testTakeSetCommands()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Take/Set Commands");
    
    std::vector<std::string> resources = {
        "food", "linemate", "deraumere", "sibur", 
        "mendiane", "phiras", "thystame"
    };
    
    for (const auto& resource : resources) {
        DEBUG << "Testing take command for: " << resource;
        player->take(resource);
    }
    
    for (const auto& resource : resources) {
        DEBUG << "Testing set command for: " << resource;
        player->set(resource);
    }
}

void Algo::testBroadcastCommand()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Broadcast Command");
    DEBUG << "Testing broadcast command...";
    player->broadcast("Hello from AI test!");
}

void Algo::testConnectNbrCommand()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Connect_nbr Command");
    DEBUG << "Testing connect_nbr command...";
    player->connect_nbr();
}

void Algo::testEjectCommand()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Eject Command");
    DEBUG << "Testing eject command...";
    player->eject();
}

void Algo::testForkCommand()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Fork Command");
    DEBUG << "Testing fork command...";
    player->fork();
}

void Algo::testIncantationCommand()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Incantation Command");
    DEBUG << "Testing incantation command...";
    player->incantation();
}

void Algo::logTest(const std::string& testName)
{
    _testCounter++;
    DEBUG << "=== TEST " << _testCounter << ": " << testName << " ===";
}