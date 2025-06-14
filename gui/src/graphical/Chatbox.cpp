/*
** EPITECH PROJECT, 2025
** Chatbox.cpp
** File description:
** Chatbox in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "Chatbox.hpp"

namespace Gui {

    Chatbox::Chatbox()
    {
        _maxMessages = 10;
        _font = LoadFont("assets/minecraft.otf");
    }

    void Chatbox::addMessage(const std::string &content, const std::string &sender, Color color)
    {
        message_t newMessage;
        newMessage.content = content;
        newMessage.sender = sender;
        newMessage.timestamp = std::chrono::steady_clock::now();
        newMessage.color = color;

        if (_messages.size() >= _maxMessages)
            _messages.pop_back();
        _messages.push_front(newMessage);
    }

    void Chatbox::draw(Vector2 position, Vector2 size, int fontSize)
    {
        DrawRectangleV(position, size, CLITERAL(Color){ 80, 80, 80, 125 });

        Vector2 textPosition = { position.x + 10, position.y + size.y - fontSize };
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

        for (const auto &message : _messages) {
            if (textPosition.y < position.y) {
                _messages.pop_back();
                break;
            }
            if (message.timestamp + std::chrono::seconds(10) < now) {
                // it's necessarily the last message in the list, so we can pop back
                _messages.pop_back();
                continue;
            }
            std::string fullMessage = "[" + message.sender + "]: " + message.content;
            // DrawText(fullMessage.c_str(), textPosition.x, textPosition.y, fontSize, message.color);
            DrawTextEx(_font, fullMessage.c_str(), textPosition, fontSize, 1, message.color);
            textPosition.y -= fontSize - 5;
        }
    }
}
