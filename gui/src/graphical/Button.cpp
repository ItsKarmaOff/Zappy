/*
** EPITECH PROJECT, 2025
** Button.cpp
** File description:
** Button in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "Button.hpp"

namespace Gui {
    Button::Button(const Rectangle &button)
    {
        setButton(button);
    }
    Button::Button(const Vector2 &pos, const Vector2 &size)
    {
        _button = {pos.x, pos.y, size.x, size.y};
        _pos = pos;
        _size = size;
        _colors = {YELLOW, DARKGRAY}; // Default colors, can be changed later
        _currentColor = _colors.first; // Default current color
    }

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

    void Button::setCurrentColor(const Color &color)
    {
        _currentColor = color;
    }

    void Button::setButton(const Rectangle &button)
    {
        _button = button;
        _pos = {button.x, button.y};
        _size = {button.width, button.height};
        _colors = {WHITE, DARKGRAY}; // Default colors, can be changed later
    }

    void Button::setPosition(const Vector2 &pos)
    {
        _pos = pos;
        _button.x = pos.x;
        _button.y = pos.y;

    }

    void Button::setSize(const Vector2 &size)
    {
        _size = size;
        _button.width = size.x;
        _button.height = size.y;
    }

    void Button::setColors(const std::pair<Color, Color> &colors)
    {
        _colors = colors;
    }

    bool Button::isMouseOver(Vector2 mousePos) const
    {
        return CheckCollisionPointRec(mousePos, _button);
    }

    void Button::setText(const std::string &text, Color color)
    {
        _text = text;
        _textColor = color;
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
    void Button::setTextColor(const Color &color)
    {
        _textColor = color;
    }
}