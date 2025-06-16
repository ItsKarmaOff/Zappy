/*
** EPITECH PROJECT, 2025
** PauseInfo.hpp
** File description:
** PauseInfo declaration
*/

#ifndef PAUSEINFO_HPP
#define PAUSEINFO_HPP

#include <functional>
#include <map>
#include <memory>
#include "Button.hpp"
#include "raylib.h"

namespace Gui {
    class PauseInfo {
        public:
            enum ButtonIndex {
                RESUME_BUTTON,
                SETTINGS_BUTTON,
                QUIT_BUTTON
            };

            enum PauseSubscene {
                RESUME,
                SETTINGS,
                QUIT
            };

            enum ButtonSettingsIndex {
                TIME_UNIT_BUTTON,
                PLUS_BUTTON,
                MINUS_BUTTON
            };
            PauseInfo();
            ~PauseInfo();

            void setBackgroundCallbacks(std::function<void()> updateCallback,
                                       std::function<void()> drawCallback);

            void resetCallbacks();

            void update();
            void updateButtons(std::vector<Button> &buttons);
            void updateSettingsButtons(std::vector<Button> &buttons);


            void draw();
            void drawButtons(std::vector<Button> &buttons);


            std::vector<Button> &getButtons();
            std::vector<Button> &getButtonsSettings();
            PauseSubscene getCurrentSubscene() const;
            void setCurrentSubscene(PauseSubscene action);

            const int &getTimeUnit() const;
            void setTimeUnit(int timeUnit);


        private:
            std::function<void()> _updateBackgroundCallback;
            std::function<void()> _drawBackgroundCallback;

            std::map<PauseSubscene, std::vector<Button> *> _buttonsMap;
            std::vector<Button> _buttons;
            std::vector<Button> _buttonsSettings;
            PauseSubscene _currentSubscene;
            int _timeUnit;
    };
}

#endif // PAUSEINFO_HPP