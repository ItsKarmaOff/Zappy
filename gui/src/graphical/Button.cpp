/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The Button class implementation
*/
/**
 * @file Button.cpp
 * @brief The Button class implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "Button.hpp"

namespace Gui
{
    //////////////////////// Constructors and Destructor ///////////////////////

    Button::Button()
    {
        init();
    }

    Button::Button(const Rectangle &button)
    {
        setButton(button);
        _colors = {YELLOW, DARKGRAY}; // Default colors, can be changed later
        _currentColor = _colors.first; // Default current color
        _text = "Default";
        _textColor = WHITE; // Default text color
    }

    Button::Button(const Vector2 &pos, const Vector2 &size)
    {
        init(pos, size);
    }

    Button::Button(const std::string &text)
    {
        init();
        _text = text;
    }



    //////////////////////// Initialization Methods ////////////////////////////

    void Button::init(const Vector2 &pos, const Vector2 &size)
    {
        _button = {pos.x, pos.y, size.x, size.y};
        _pos = pos;
        _size = size;
        _colors = {YELLOW, DARKGRAY}; // Default colors, can be changed later
        _currentColor = _colors.first; // Default current color
        _text = "Default";
        _textColor = WHITE; // Default text color
    }



    //////////////////////// Getters ///////////////////////////////////////////

    const Rectangle& Button::getButton() const
    {
        return _button;
    }

    const Vector2& Button::getPosition() const
    {
        return _pos;
    }

    const Vector2& Button::getSize() const
    {
        return _size;
    }
    const std::pair<Color, Color>& Button::getColors() const
    {
        return _colors;
    }

    const Color& Button::getCurrentColor() const
    {
        return _currentColor;
    }



    // ///////////////////// Setters ///////////////////////////////////////////

    Button& Button::setCurrentColor(const Color &color)
    {
        _currentColor = color;
        return *this;
    }

    Button& Button::setButton(const Rectangle &button)
    {
        _button = button;
        _pos = {button.x, button.y};
        _size = {button.width, button.height};
        return *this;
    }

    Button& Button::setPosition(const Vector2 &pos)
    {
        _pos = pos;
        _button.x = pos.x;
        _button.y = pos.y;
        return *this;
    }

    Button& Button::setSize(const Vector2 &size)
    {
        _size = size;
        _button.width = size.x;
        _button.height = size.y;
        return *this;
    }

    Button& Button::setColors(const std::pair<Color, Color> &colors)
    {
        _colors = colors;
        return *this;
    }



    //////////////////////// Utility Methods ///////////////////////////////////

    bool Button::isMouseOver(Vector2 mousePos) const
    {
        return CheckCollisionPointRec(mousePos, _button);
    }

    Button& Button::setText(const std::string &text, Color color)
    {
        _text = text;
        _textColor = color;
        return *this;
    }

    Vector2 Button::getCenteredPositionForText(int fontSize) const
    {
        float textWidth = MeasureText(_text.c_str(), fontSize);
        float textHeight = fontSize;
        return {
            _button.x + (_button.width - textWidth) / 2,
            _button.y + (_button.height - textHeight) / 2
        };
    }

    const std::string& Button::getText() const
    {
        return _text;
    }

    const Color& Button::getTextColor() const
    {
        return _textColor;
    }

    Button& Button::setTextColor(const Color &color)
    {
        _textColor = color;
        return *this;
    }

    void Button::switchColorsIfHover(Vector2 mousePos)
    {
        setCurrentColor(isMouseOver(mousePos) ? _colors.second : _colors.first);
    }
}