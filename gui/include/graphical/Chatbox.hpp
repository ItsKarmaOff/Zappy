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

/**
 * @struct message
 * @brief Represents a message in the chatbox with content, sender information, timestamp, and color
 * @author Gianni TUERO
 */
typedef struct message {
    std::string content;                         ///< The content of the message
    std::string sender;                          ///< The sender of the message
    std::chrono::steady_clock::time_point timestamp; ///< When the message was created
    Color color;                                 ///< The color used to display the message
} message_t;

/**
 * @file Chatbox.hpp
 * @brief The Chatbox class for managing and displaying chat messages
 */

namespace Gui {
    /**
     * @class Chatbox
     * @brief Manages the display and storage of chat messages with timed expiration
     */
    class Chatbox {
        public:
            /**
             * @brief Default constructor
             * Initializes the chatbox with default settings and loads the font
             */
            Chatbox();

            /**
             * @brief Default destructor
             */
            ~Chatbox() = default;

            /**
             * @brief Adds a new message to the chatbox
             * @param content The text content of the message
             * @param sender The name/identifier of the message sender
             * @param color The color used to display the message (default: WHITE)
             */
            void addMessage(const std::string &content, const std::string &sender, Color color = WHITE);

            /**
             * @brief Wraps text to fit within a specified width
             * @param text The text to wrap
             * @param maxWidth The maximum width for the text in pixels
             * @param fontSize The size of the font
             * @param font The font used for measuring text dimensions
             * @return Vector of strings with each line wrapped to fit the width
             */
            std::vector<std::string> wrapText(const std::string& text, int maxWidth, int fontSize, Font font);

            /**
             * @brief Draws the chatbox with all current messages
             * @param position The position where to draw the chatbox
             * @param size The size of the chatbox
             * @param fontSize The size of the font (default: scaled to screen height)
             */
            void draw(Vector2 position, Vector2 size, int fontSize = GetScreenHeight() / 30);

        private:
            size_t _maxMessages;            ///< Maximum number of messages to display
            std::deque<message_t> _messages; ///< Queue of messages
            Font _font;                     ///< Font used for rendering messages

    };
}

#endif // CHATBOX_HPP