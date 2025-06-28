/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The Button class declaration
*/
/**
 * @file Button.hpp
 * @brief The Button class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef BUTTON_HPP
    #define BUTTON_HPP

    #include "Lib.hpp"
    #include <raylib.h>
    #include <raymath.h>

namespace Gui
{
    /**
     * @class Button
     * @brief Represents a button in the GUI with position, size, colors, and text
     */
    class Button {
        public:

            //////////////// Constructors and Destructor ///////////////////////

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

            /**
             * @brief Default destructor
             */
            ~Button() = default;



            //////////////// Initialization Methods ////////////////////////////

            /**
             * @brief Initialize the button with given position and size
             * @param pos Position of the button (default: {0, 0})
             * @param size Size of the button (default: {100, 100})
             */
            void init(const Vector2 &pos = {0, 0}, const Vector2 &size = {100, 100});



            //////////////// Getters ///////////////////////////////////////////

            /**
             * @brief Get the button rectangle
             * @return Rectangle representing the button area
             */
            const Rectangle &getButton() const;

            /**
             * @brief Get the position of the button
             * @return Vector2 representing the position of the button
             */
            const Vector2 &getPosition() const;

            /**
             * @brief Get the size of the button
             * @return Vector2 representing the size of the button
             */
            const Vector2 &getSize() const;

            /**
             * @brief Get the colors of the button
             * @return Pair of Colors representing the normal and hover colors of the button
             */
            const std::pair<Color, Color> &getColors() const;

            /**
             * @brief Get the current color of the button
             * @return Color representing the current color of the button
             */
            const Color &getCurrentColor() const;

            /**
             * @brief Get the text displayed on the button
             * @return String representing the text on the button
             */
            const std::string &getText() const;

            /**
             * @brief Get the color of the text displayed on the button
             * @return Color representing the text color
             */
            const Color &getTextColor() const;



            //////////////// Setters ///////////////////////////////////////////

            /**
             * @brief Set the button rectangle
             * @param button Rectangle representing the button area
             * @return Reference to the Button object for method chaining
             */
            Button &setButton(const Rectangle &button);

            /**
             * @brief Set the position of the button
             * @param pos Position of the button
             * @return Reference to the Button object for method chaining
             */
            Button &setPosition(const Vector2 &pos);

            /**
             * @brief Set the size of the button
             * @param size Size of the button
             * @return Reference to the Button object for method chaining
             */
            Button &setSize(const Vector2 &size);

            /**
             * @brief Set the colors of the button
             * @param colors Pair of Colors representing the normal and hover colors of the button
             * @return Reference to the Button object for method chaining
             */
            Button &setColors(const std::pair<Color, Color> &colors);

            /**
             * @brief Set the current color of the button
             * @param color Color to set as the current color
             * @return Reference to the Button object for method chaining
             */
            Button &setCurrentColor(const Color &color);

            /**
             * @brief Set the text displayed on the button
             * @param text Text to display on the button
             * @param color Color of the text (default: BLACK)
             * @return Reference to the Button object for method chaining
             */
            Button &setText(const std::string &text, Color color = BLACK);

            /**
             * @brief Set the color of the text displayed on the button
             * @param color Color to set for the text
             * @return Reference to the Button object for method chaining
             */
            Button &setTextColor(const Color &color);



            //////////////// Utility Methods ///////////////////////////////////

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

            //////////////// Private Attributes ////////////////////////////////

            Rectangle _button; ///< Rectangle representing the button area
            Vector2 _pos; ///< Position of the button
            Vector2 _size; ///< Size of the button
            std::pair<Color, Color> _colors; ///< Pair of colors for the button, first is normal, second is hover
            Color _currentColor; ///< Current color for the button, can be used for hover effects
            std::string _text; ///< Text to display on the button, if any
            Color _textColor; ///< Color of the text displayed on the button
    };
};

#endif // BUTTON_HPP
