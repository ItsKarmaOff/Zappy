/*
** EPITECH PROJECT, 2025
** PlayerInfo.hpp
** File description:
** PlayerInfo declaration
*/


#ifndef PLAYERINFO_HPP
    #define PLAYERINFO_HPP
#include <cstddef>
#include <map>
#include <raylib.h>



namespace Gui {
    class PlayerInfo {
        public:
            enum Orientation {
                NORTH,
                EAST,
                SOUTH,
                WEST,
            };

            enum ResourceType {
                FOOD,
                LINEMATE,
                DERAUMERE,
                SIBUR,
                MENDIANE,
                PHIRAS,
                THYSTAME
            };

            PlayerInfo() = default;
            ~PlayerInfo() = default;

            ////////////////////////////////////// GETTERS //////////////////////////////////////
            const Orientation &getOrientation() const;
            void setOrientation(Orientation orientation);
            void setOrientation(int orientation);

            const size_t &getLevel() const;
            void setLevel(size_t level);

            const Vector2 &getPos() const;
            void setPos(Vector2 pos);

            const std::map<ResourceType, size_t> &getInventory() const;
            void setInventory(const std::map<ResourceType, size_t> &inventory);
            void addResource(ResourceType type, size_t quantity);
            void removeResource(ResourceType type, size_t quantity);

        private:
            Orientation _orientation;
            size_t _level;
            Vector2 _pos;
            std::map<ResourceType, size_t> _inventory;
    };

}

#endif // PLAYERINFO_HPP