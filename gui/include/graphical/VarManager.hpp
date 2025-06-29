/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The VarManager clas declaration
*/
/**
 * @file VarManager.hpp
 * @brief The VarManager class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef VARMANAGER_HPP
    #define VARMANAGER_HPP

    #include "Lib.hpp"

namespace Gui {
    class VarManager {
        public:
            VarManager() = default;
            ~VarManager() = default;

            static VarManager &getInstance() {
                static VarManager instance;
                return instance;
            }

            enum VarType {
                DEBUG_VAR,
                GAMEMODE_VAR,
            };

            void setVar(VarType var, bool value) {
                _vars[var] = value;
            }
            bool getVar(VarType var) const {
                auto it = _vars.find(var);
                if (it != _vars.end()) {
                    return it->second;
                }
                return false;
            }

        private:
            std::unordered_map<VarType, bool> _vars;
    };
}

#endif // VARMANAGER_HPP
