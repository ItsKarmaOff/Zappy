/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The PauseInfo class declaration
*/
/**
 * @file PauseInfo.hpp
 * @brief The PauseInfo class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef PAUSEINFO_HPP
    #define PAUSEINFO_HPP

    #include "AssetsManager.hpp"
    #include "Button.hpp"

namespace Gui
{
    /**
     * @class PauseInfo
     * @brief Manages the pause menu state, buttons, and interactions
     */
    class PauseInfo {
        public:

            //////////////// Enumerations //////////////////////////////////////

            /**
             * @enum ButtonIndex
             * @brief Indices for the main pause menu buttons
             */
            enum ButtonIndex {
                RESUME_BUTTON,    ///< Button to resume the game
                SETTINGS_BUTTON,  ///< Button to access settings
                QUIT_BUTTON       ///< Button to quit the game
            };

            /**
             * @enum PauseSubscene
             * @brief Represents different sub-menus within the pause screen
             */
            enum PauseSubscene {
                RESUME,    ///< Main pause menu with resume option
                SETTINGS,  ///< Settings sub-menu
                QUIT       ///< Quit confirmation sub-menu
            };

            /**
             * @enum ButtonSettingsIndex
             * @brief Indices for buttons in the settings sub-menu
             */
            enum ButtonSettingsIndex {
                TIME_UNIT_BUTTON, ///< Button displaying current time unit
                PLUS_BUTTON,      ///< Button to increase time unit
                MINUS_BUTTON,     ///< Button to decrease time unit
                VOLUME_BUTTON     ///< Slider button for adjusting volume
            };



            //////////////// Constructors and Destructor ///////////////////////

            /**
             * @brief Default constructor
             * Initializes buttons and default values for the pause menu
             */
            PauseInfo();

            /**
             * @brief Destructor
             */
            ~PauseInfo();



            //////////////// Main Methods //////////////////////////////////////
            /**
             * @brief Sets callbacks to update and draw the background behind the pause menu
             * @param updateCallback Function to update the background
             * @param drawCallback Function to draw the background
             */
            void setBackgroundCallbacks(std::function<void()> updateCallback,
                                       std::function<void()> drawCallback);

            /**
             * @brief Resets the background callbacks to nullptr
             */
            void resetCallbacks();



            //////////////// Update Methods ////////////////////////////////////

            /**
             * @brief Updates the pause menu state
             * Updates buttons and calls the background update callback if set
             */
            void update();

            /**
             * @brief Updates positions and sizes of buttons in the main pause menu
             * @param buttons Reference to the vector of buttons to update
             */
            void updateButtons(std::vector<Button> &buttons);

            /**
             * @brief Updates positions and sizes of buttons in the settings menu
             * @param buttons Reference to the vector of settings buttons to update
             */
            void updateSettingsButtons(std::vector<Button> &buttons);



            //////////////// Draw Methods //////////////////////////////////////

            /**
             * @brief Draws the pause menu
             * Calls the background draw callback and draws the appropriate buttons
             */
            void draw(AssetsManager &);

            /**
             * @brief Draws the buttons for the current subscene
             * @param buttons Reference to the vector of buttons to draw
             */
            void drawButtons(std::vector<Button> &buttons);

            /**
             * @brief Draws the volume slider in the settings menu
             * Displays a slider for adjusting the volume level
             */
            void drawVolumeSlider();



            //////////////////// Getters ///////////////////////////////////////////

            /**
             * @brief Gets the main pause menu buttons
             * @return Reference to the vector of main pause menu buttons
             */
            std::vector<Button> &getButtons();

            /**
             * @brief Gets the settings menu buttons
             * @return Reference to the vector of settings menu buttons
             */
            std::vector<Button> &getButtonsSettings();

            /**
             * @brief Gets the current subscene being displayed
             * @return The current PauseSubscene value
             */
            PauseSubscene getCurrentSubscene() const;

            /**
             * @brief Gets the current time unit value
             * @return Constant reference to the time unit value
             */
            const int &getTimeUnit() const;

            /**
             * @brief Gets the current volume level
             * @return The current volume level
             */
            int getVolume() const;



            //////////////// Setters ///////////////////////////////////////////

            /**
             * @brief Sets the current subscene to display
             * @param action The PauseSubscene to switch to
             */
            void setCurrentSubscene(PauseSubscene action);

            /**
             * @brief Sets the time unit value
             * @param timeUnit The new time unit value
             */
            void setTimeUnit(int timeUnit);

            /**
             * @brief Sets the volume level
             * @param volume The new volume level
             */
            void setVolume(int volume);



        private:

            //////////////// Private Attributes ////////////////////////////////

            std::function<void()> _updateBackgroundCallback; ///< Callback to update the background
            std::function<void()> _drawBackgroundCallback;   ///< Callback to draw the background

            std::map<PauseSubscene, std::vector<Button> *> _buttonsMap; ///< Map of subscenes to their button vectors
            std::vector<Button> _buttons;                   ///< Main pause menu buttons
            std::vector<Button> _buttonsSettings;           ///< Settings menu buttons
            PauseSubscene _currentSubscene;                 ///< Currently active subscene
            int _timeUnit;                                  ///< Time unit value for game speed

            int _volume;                                    ///< Volume level
    };
}

#endif // PAUSEINFO_HPP
