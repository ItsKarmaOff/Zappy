/*
** EPITECH PROJECT, 2024
** zappy [WSL: Ubuntu]
** File description:
** Algo.hpp
*/

#ifndef ALGO_HPP_
#define ALGO_HPP_

#include <memory>
#include <chrono>
#include <thread>

class Player;

class Algo {
public:
    Algo();
    ~Algo();

    void run();
    void setPlayer(std::shared_ptr<Player> player);
    void setPlayer(Player* player);

private:
    void testMovementCommands();
    void testLookCommand();
    void testInventoryCommand();
    void testTakeSetCommands();
    void testBroadcastCommand();
    void testConnectNbrCommand();
    void testEjectCommand();
    void testForkCommand();
    void testIncantationCommand();
    
    void waitForCommand(int seconds = 1);
    void logTest(const std::string& testName);

    std::shared_ptr<Player> _player;
    Player* _playerPtr;
    int _testCounter;
};

#endif