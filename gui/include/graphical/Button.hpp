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

namespace Gui {

    class Button {
        public:
            Button(const Rectangle &button);
            Button(const Vector2 &pos, const Vector2 &size);
            ~Button() = default;

            ////////////////////////////////////// GETTERS //////////////////////////////////////
            const Rectangle &getButton() const;
            const Vector2 &getPosition() const;
            const Vector2 &getSize() const;
            const std::pair<Color, Color> &getColors() const;
            const Color &getCurrentColor() const;
            const std::string &getText() const;
            const Color &getTextColor() const;
            ////////////////////////////////////// SETTERS //////////////////////////////////////
            void setButton(const Rectangle &button);
            void setPosition(const Vector2 &pos);
            void setSize(const Vector2 &size);
            void setColors(const std::pair<Color, Color> &colors);
            void setCurrentColor(const Color &color);
            void setText(const std::string &text, Color color = BLACK);
            void setTextColor(const Color &color);
            ////////////////////////////////////// UTILITY METHODS //////////////////////////////
            bool isMouseOver(Vector2 mousePos) const;
            Vector2 getCenteredPositionForText(int fontSize) const;

        private:
            Rectangle _button;
            Vector2 _pos;
            Vector2 _size;
            std::pair<Color, Color> _colors;
            Color _currentColor; // Current color for the button, can be used for hover effects

            std::string _text; // Text to display on the button, if any
            Color _textColor; // Color of the text displayed on the button

    };
};

#endif // BUTTON_HPP