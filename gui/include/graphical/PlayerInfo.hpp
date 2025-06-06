/*
** EPITECH PROJECT, 2025
** PlayerInfo.hpp
** File description:
** PlayerInfo declaration
*/


#ifndef PLAYERINFO_HPP
    #define PLAYERINFO_HPP
#include <cstddef>
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

        private:
            Orientation _orientation;
            size_t _level;
            Vector2 _pos;
    };

}

#endif // PLAYERINFO_HPP