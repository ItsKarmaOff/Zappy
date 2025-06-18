/*
** EPITECH PROJECT, 2025
** Button.hpp
** File description:
** Button declaration
*/


#ifndef BUTTON_HPP
    #define BUTTON_HPP

    #include <raylib.h>
    #include <string>
    #include <utility>

/**
 * @file Button.hpp
 * @brief The Button class
 * @author Gianni TUERO
 */

namespace Gui {

    class Button {
        public:
            ////////////////////////////////////// CONSTRUCTORS //////////////////////////////////////
            /**
             * @brief Default constructor
             */
            Button();
            /**
             * @brief Constructor that initializes the button with a Rectangle
             * @param button Rectangle representing the button area
             */
            Button(const Rectangle &button);

            /**
             * @brief Constructor that initializes the button with position and size
             * @param pos Position of the button
             * @param size Size of the button
             */
            Button(const Vector2 &pos, const Vector2 &size);

            /**
             * @brief Constructor that initializes the button with text
             * @param text Text to display on the button
             */
            Button(const std::string &text);
            ~Button() = default;

            /**
             * @brief Initialize the button with given position and size
             * @param pos Position of the button (default: {0, 0})
             * @param size Size of the button (default: {100, 100})
             */
            void init(const Vector2 &pos = {0, 0}, const Vector2 &size = {100, 100});


            ////////////////////////////////////// GETTERS //////////////////////////////////////
            const Rectangle &getButton() const;
            const Vector2 &getPosition() const;
            const Vector2 &getSize() const;
            const std::pair<Color, Color> &getColors() const;
            const Color &getCurrentColor() const;
            const std::string &getText() const;
            const Color &getTextColor() const;
            ////////////////////////////////////// SETTERS //////////////////////////////////////
            Button &setButton(const Rectangle &button);
            Button &setPosition(const Vector2 &pos);
            Button &setSize(const Vector2 &size);
            Button &setColors(const std::pair<Color, Color> &colors);
            Button &setCurrentColor(const Color &color);
            Button &setText(const std::string &text, Color color = BLACK);
            Button &setTextColor(const Color &color);
            ////////////////////////////////////// UTILITY METHODS //////////////////////////////

            /**
             * @brief Checks if the mouse is over the button
             * @param mousePos Position of the mouse cursor
             * @return true if the mouse is over the button
             * @return false if the mouse is not over the button
             */
            bool isMouseOver(Vector2 mousePos) const;

            /**
             * @brief Gets the centered position for the text based on the button size and font size
             * @param fontSize Size of the font used for the text
             * @return Vector2 representing the centered position for the text
             */
            Vector2 getCenteredPositionForText(int fontSize) const;

            /**
             * @brief Switches the button colors if the mouse is hovering over it
             * @param mousePos Position of the mouse cursor
             */
            void switchColorsIfHover(Vector2 mousePos);

        private:
            Rectangle _button; // Rectangle representing the button area
            Vector2 _pos; // Position of the button
            Vector2 _size; // Size of the button
            std::pair<Color, Color> _colors; // Pair of colors for the button, first is normal, second is hover
            Color _currentColor; // Current color for the button, can be used for hover effects

            std::string _text; // Text to display on the button, if any
            Color _textColor; // Color of the text displayed on the button

    };
};

#endif // BUTTON_HPP