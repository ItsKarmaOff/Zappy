/*
** EPITECH PROJECT, 2025
** VarManager.hpp
** File description:
** VarManager declaration
*/


#ifndef VARMANAGER_HPP
    #define VARMANAGER_HPP

#include <unordered_map>
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