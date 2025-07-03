/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The Chatbox class implementation
*/
/**
 * @file Chatbox.cpp
 * @brief The Chatbox class implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
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

    std::vector<std::string> Chatbox::wrapText(const std::string& text,
        int maxWidth, int fontSize, Font font)
        {
        std::vector<std::string> lines;
        std::string line;
        std::istringstream stream(text);
        std::string word;

        while (stream >> word) {
            std::string testLine = line.empty() ? word : line + " " + word;
            Vector2 size = MeasureTextEx(font, testLine.c_str(), fontSize, 5);
            if (size.x > maxWidth) {
                if (!line.empty()) {
                    lines.push_back(line);
                    line = word;
                } else {
                    lines.push_back(word);
                    line.clear();
                }
            } else {
                line = testLine;
            }
        }

        if (!line.empty())
            lines.push_back(line);

        return lines;
    }


    void Chatbox::draw(Vector2 position, Vector2 size, int fontSize)
    {
        DrawRectangleV(position, size, CLITERAL(Color){ 80, 80, 80, 125 });

        Vector2 textPosition = { position.x + 10, position.y + size.y - fontSize };
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

        for (const auto &message : _messages) {
            if (message.timestamp + std::chrono::seconds(10) < now) {
                // it's necessarily the last message in the list, so we can pop backck
                _messages.pop_back();
                continue;
            }
            std::string fullMessage = "[" + message.sender + "]: " + message.content;
            std::vector<std::string> wrappedLines = wrapText(fullMessage, size.x - 20, fontSize, _font);

            for (auto it = wrappedLines.rbegin(); it != wrappedLines.rend(); ++it) {
                if (textPosition.y < position.y) {
                    _messages.pop_back();
                    break;
                }
                DrawTextEx(_font, it->c_str(), textPosition, fontSize, 5, message.color);
                textPosition.y -= fontSize - 5;
            }
        }
    }
}
