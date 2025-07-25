/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The macros of the server
*/
/**
 * @file server_macros.h
 * @brief The macros of the server
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef SERVER_MACROS_H_
    #define SERVER_MACROS_H_

    #include "my.h"

/* Server macros */



    /* Program options */

    /**
     * @brief The default frequency of the server
     */
    #define DEFAULT_FREQUENCY 100

    /**
     * @brief The maximum port number
     */
    #define MAX_PORT 65535

    /**
     * @brief The maximum port number as a string
     */
    #define MAX_PORT_STR "65535"



    /* Network macros */

    /**
     * @brief The ip of the google DNS server
     */
    #define GOOGLE_DNS_IP "8.8.8.8"

    /**
     * @brief The default port for the DNS server
     */
    #define DNS_PORT 53



    /* Client macros */

    /**
     * @brief The default number of clients in the server
     */
    #define DEFAULT_NUMBER_OF_CLIENTS 1

    /**
     * @brief The index of the server in the poll_fds array
     */
    #define SERVER_POLL_INDEX 0

    /**
     * @brief The index of the stdin in the poll_fds array
     */
    #define STDIN_POLL_INDEX 1

    /**
     * @brief The index of the stdin client (server client)
     * in the client_list array
     */
    #define STDIN_CLIENT_INDEX 0

    /**
     * @brief The default maximum number of backlog connections
     * in the listen queue
     */
    #define DEFAULT_LISTEN_BACKLOG 128

    /**
     * @brief Gets the client at a specific index in the server's client list
     */
    #define CLIENT(server, index) ((server)->client_list[(index) - 1])



    /* Command macros */

    /**
     * @brief The maximum number of commands a client can have
     */
    #define CLIENT_MAX_COMMANDS 10

    /**
     * @brief The welcome message sent to clients
     */
    #define WELCOME_MESSAGE "WELCOME\n"

    /**
     * @brief The message sent to clients when an action is valid
     */
    #define VALID_AI "ok\n"

    /**
     * @brief /The message sent to clients when an action is not valid
     */
    #define WRONG_AI "ko\n"

    /**
     * @brief The message sent to clients when the GUI is not valid
     */
    #define WRONG_GUI "suc\n"

    /**
     * @brief The message sent to clients
     * when the arguments of a command are invalid
     */
    #define INVALID_ARGS "sbp\n"



    /* Game macros */

    /**
     * @brief The refill time unit until the next refill
     */
    #define REFILL_TIME 20.0

    /**
     * @brief Access the game map at a player's position
     */
    #define ACCESS_MAP(map, player) map[player->position.y][player->position.x]



    /* Team macros */

    /**
     * @brief The graphic team index
     */
    #define GRAPHIC_TEAM_INDEX 0

    /**
     * @brief The name of the graphic team
     */
    #define GRAPHIC_TEAM_NAME "GRAPHIC"



    /* Player macros */

    /**
     * @brief The default number of food when a player is created
     */
    #define DEFAULT_FOOD_NUMBER (10 - 1)

    /**
     * @brief The time unit for food consumption
     */
    #define FOOD_TIME_UNIT 126

    /**
     * @brief The death message sent to clients
     */
    #define DEATH_MESSAGE "dead\n"

    /**
     * @brief The maximum level a player can reach
     */
    #define MAX_PLAYER_LEVEL 8

    /**
     * @brief The number of players level max in a team to win the game
     */
    #define NUMBER_OF_PLAYER_LEVEL_MAX_TO_WIN 6

    /**
     * @brief The message send to ai when the elevation is accepted
     */
    #define ELEVATION_OK "Elevation underway\n"

    /**
     * @brief The prefix of the broadcast message sent to clients
     */
    #define BROADCAST_MESSAGE_PREFIX "message K, "

#endif /* SERVER_MACROS_H_ */
