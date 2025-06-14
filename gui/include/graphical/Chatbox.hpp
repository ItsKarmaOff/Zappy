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
            std::vector<std::string> wrapText(const std::string& text, int maxWidth, int fontSize, Font font);
            void draw(Vector2 position, Vector2 size, int fontSize = GetScreenHeight() / 30);
        private:
            size_t _maxMessages;
            std::deque<message_t> _messages;
            Font _font;

    };
}

#endif // CHATBOX_HPP