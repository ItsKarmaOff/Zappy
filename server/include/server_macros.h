/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The server_macros.h
*/
/**
 * @file server_macros.h
 * @brief The server_macros.h
 * @author Nicolas TORO
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



    /* Team macros */

    /**
     * @brief The graphic team index
     */
    #define GRAPHIC_TEAM_INDEX 0

    /**
     * @brief The name of the graphic team
     */
    #define GRAPHIC_TEAM_NAME "GRAPHIC"



    /* Client macros */

    /**
     * @brief The index of the server in the poll_fds array
     */
    #define SERVER_POLL_INDEX 0

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

#endif /* SERVER_MACROS_H_ */
