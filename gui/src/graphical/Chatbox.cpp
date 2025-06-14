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
        // Draw the chatbox background
        DrawRectangleV(position, size, CLITERAL(Color){ 80, 80, 80, 125 });

        // Draw the messages
        Vector2 textPosition = { position.x + 10, position.y + 10 };
        
        for (const auto &message : _messages) {
            DrawText(message.content.c_str(), textPosition.x, textPosition.y, fontSize, message.color);
            textPosition.y += fontSize + 5;
        }
    }
}
