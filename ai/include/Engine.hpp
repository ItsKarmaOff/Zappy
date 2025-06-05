/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "Parser.hpp"

class Engine {
    public:
        Engine(Parser &parser);
        ~Engine();
        void run();
    protected:
    private:
        Parser _parser;
};

#endif /* !ENGINE_HPP_ */
