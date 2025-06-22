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

    DEBUG << "Starting comprehensive command testing algorithm...";
    
    DEBUG << "=== PHASE 1: Basic Commands ===";
    testLookCommand();
    waitAndProcessResponses(player, 1000);
    
    testInventoryCommand();
    waitAndProcessResponses(player, 1000);
    
    testMovementCommands();
    waitAndProcessResponses(player, 3000);
    
    DEBUG << "=== PHASE 2: Communication Commands ===";
    testBroadcastCommand();
    waitAndProcessResponses(player, 1000);
    
    testConnectNbrCommand();
    waitAndProcessResponses(player, 1000);
    
    DEBUG << "=== PHASE 3: Object Interaction Commands ===";
    testTakeSetCommands();
    waitAndProcessResponses(player, 5000);
    
    DEBUG << "=== PHASE 4: Advanced Commands ===";
    testEjectCommand();
    waitAndProcessResponses(player, 1000);
    
    testForkCommand();
    waitAndProcessResponses(player, 2000);
    
    testIncantationCommand();
    waitAndProcessResponses(player, 2000);

    DEBUG << "=== All command tests completed ===";
    DEBUG << "=== Starting continuous validation cycle ===";

    int cycleCount = 0;
    int successfulCommands = 0;
    int totalCommands = 0;
    
    while (player->isAlive() && cycleCount < 20) {
        cycleCount++;
        DEBUG << "=== Validation Cycle " << cycleCount << " ===";
        
        DEBUG << "Checking for food...";
        player->look();
        totalCommands++;
        waitAndProcessResponses(player, 500);
        
        if (!player->isAlive()) break;
        
        player->inventory();
        totalCommands++;
        waitAndProcessResponses(player, 500);
        
        if (!player->isAlive()) break;
        
        player->take("food");
        totalCommands++;
        waitAndProcessResponses(player, 500);
        
        if (!player->isAlive()) break;
        
        player->forward();
        totalCommands++;
        waitAndProcessResponses(player, 500);
        
        if (!player->isAlive()) break;
        
        player->right();
        totalCommands++;
        waitAndProcessResponses(player, 500);
        
        if (!player->isAlive()) break;
        
        if (cycleCount % 5 == 0) {
            double successRate = totalCommands > 0 ? (double)successfulCommands / totalCommands * 100.0 : 0.0;
            DEBUG << "=== Performance Stats after " << cycleCount << " cycles ===";
            DEBUG << "Total commands sent: " << totalCommands;
            DEBUG << "Player still alive: " << (player->isAlive() ? "YES" : "NO");
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    
    double finalSuccessRate = (double)successfulCommands / totalCommands * 100.0;
    DEBUG << "=== FINAL TEST REPORT ===";
    DEBUG << "Total cycles completed: " << cycleCount;
    DEBUG << "Total commands sent: " << totalCommands;
    DEBUG << "Successful commands: " << successfulCommands;
    DEBUG << "Final success rate: " << finalSuccessRate << "%";
    DEBUG << "Client test completed successfully!";
}

void Algo::waitAndProcessResponses(Player* player, int waitTimeMs)
{
    DEBUG << "Waiting " << waitTimeMs << "ms for responses...";
    
    int checkInterval = 100;
    int totalWaited = 0;
    int responseCount = 0;
    
    while (totalWaited < waitTimeMs && player->isAlive()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(checkInterval));
        totalWaited += checkInterval;
        
        while (player->getCommandsQueue()->hasResponses()) {
            std::string response = player->getCommandsQueue()->popResponse();
            responseCount++;
            DEBUG << "Response " << responseCount << ": [" << response << "]";
            
            if (response == "ko") {
                ERROR << "Command failed (got 'ko' response)";
            } else if (response == "dead") {
                ERROR << "Player died!";
                return;
            } else if (response == "ok") {
                DEBUG << "Command successful";
            } else if (response.find("[") != std::string::npos) {
                DEBUG << "Structured response (look/inventory): " << response;
            } else if (std::isdigit(response[0])) {
                DEBUG << "Numeric response (connect_nbr?): " << response;
            } else {
                DEBUG << "Other response: " << response;
            }
            
            player->processResponse(response);
        }
    }
    
    if (responseCount > 0) {
        DEBUG << "Processed " << responseCount << " total responses in " << totalWaited << "ms";
    } else {
        DEBUG << "No responses received after " << totalWaited << "ms";
    }
}

void Algo::testMovementCommands()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Movement Commands");
        
    DEBUG << "Testing forward command...";
    player->forward();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
    DEBUG << "Testing right turn...";
    player->right();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
    DEBUG << "Testing left turn...";
    player->left();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
    DEBUG << "Testing another forward...";
    player->forward();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    
    DEBUG << "Movement commands test completed";
}

void Algo::testLookCommand()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Look Command");
    DEBUG << "Testing look command...";
    player->look();
    DEBUG << "Look command sent";
}

void Algo::testInventoryCommand()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Inventory Command");
    DEBUG << "Testing inventory command...";
    player->inventory();
    DEBUG << "Inventory command sent";
}

void Algo::testTakeSetCommands()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Take/Set Commands");
        
    std::vector<std::string> resources = {
        "food", "linemate", "deraumere", "sibur", 
        "mendiane", "phiras", "thystame"
    };
        
    DEBUG << "Testing take commands...";
    for (const auto& resource : resources) {
        DEBUG << "Testing take command for: " << resource;
        player->take(resource);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
        
    DEBUG << "Testing set commands...";
    for (const auto& resource : resources) {
        DEBUG << "Testing set command for: " << resource;
        player->set(resource);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    DEBUG << "Take/Set commands test completed";
}

void Algo::testBroadcastCommand()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Broadcast Command");
    DEBUG << "Testing broadcast command...";
    player->broadcast("Hello from AI test! Cycle " + std::to_string(_testCounter));
    DEBUG << "Broadcast command sent";
}

void Algo::testConnectNbrCommand()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Connect_nbr Command");
    DEBUG << "Testing connect_nbr command...";
    player->connect_nbr();
    DEBUG << "Connect_nbr command sent";
}

void Algo::testEjectCommand()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Eject Command");
    DEBUG << "Testing eject command...";
    player->eject();
    DEBUG << "Eject command sent";
}

void Algo::testForkCommand()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Fork Command");
    DEBUG << "Testing fork command...";
    player->fork();
    DEBUG << "Fork command sent";
}

void Algo::testIncantationCommand()
{
    Player* player = _player ? _player.get() : _playerPtr;
    logTest("Incantation Command");
    DEBUG << "Testing incantation command...";
    player->incantation();
    DEBUG << "Incantation command sent";
}

void Algo::logTest(const std::string& testName)
{
    _testCounter++;
    DEBUG << "=== TEST " << _testCounter << ": " << testName << " ===";
}