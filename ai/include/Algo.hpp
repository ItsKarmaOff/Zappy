/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Algo
*/

#ifndef ALGO_HPP_
#define ALGO_HPP_

#include "Lib.hpp"

class Player;

class Algo {
    public:
        Algo();
        ~Algo();
        void setPlayer(std::shared_ptr<Player> player);
        void setPlayer(Player* player);
        void run();

    protected:
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
        void logTest(const std::string& testName);
        void waitAndProcessResponses(Player* player, int waitTimeMs);

        std::shared_ptr<Player> _player;
        Player* _playerPtr;
        int _testCounter;
};

#endif /* !ALGO_HPP_ */