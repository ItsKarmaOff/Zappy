/*
** EPITECH PROJECT, 2025
** Chatbox.hpp
** File description:
** Chatbox declaration
*/


#ifndef CHATBOX_HPP
    #define CHATBOX_HPP

#include <queue>
#include <raylib.h>
#include <string>
#include <chrono>


typedef struct message {
    std::string content;
    std::string sender;
    std::chrono::steady_clock::time_point timestamp;
    Color color;
} message_t;

namespace Gui {
    class Chatbox {
        public:
            Chatbox();
            ~Chatbox() = default;

            void addMessage(const std::string &content, const std::string &sender, Color color = WHITE);
            void draw(Vector2 position, Vector2 size, int fontSize = 20);
        private:
            size_t _maxMessages;
            std::deque<message_t> _messages;

    };
}

#endif // CHATBOX_HPP