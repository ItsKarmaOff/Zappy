/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The test_ai.cpp
*/
/**
 * @file test_ai.cpp
 * @brief The test_ai.cpp
 * @author Nicolas TORO
 */

#include "tests.h"
#include "Player.hpp"

/* Example classic */
Test(create_player, test_create_player, .init = redirect_all_std)
{
    Player player("test");
}
