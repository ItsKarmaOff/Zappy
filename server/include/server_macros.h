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

    /* The default frequency of the server */
    #define DEFAULT_FREQUENCY 100

    /* The maximum port number */
    #define MAX_PORT 65535

    /* The maximum port number as a string */
    #define MAX_PORT_STR "65535"

    /* The maximum number of commands a client can have */
    #define CLIENT_MAX_COMMANDS 10

    /* The graphic team index */
    #define GRAPHIC_TEAM_INDEX 0

    /* The name of the graphic team */
    #define GRAPHIC_TEAM_NAME "GRAPHIC"

    /* The welcome message sent to clients */
    #define WELCOME_MESSAGE "WELCOME\n"

    /* The message sent to clients when an action is valid */
    #define VALID_AI "ok\n"

    /* The message sent to clients when an action is not valid */
    #define WRONG_AI "ko\n"

    /* The message sent to clients when the GUI is not valid */
    #define WRONG_GUI "suc\n"

    /**
     * @brief The message sent to clients
     * when the arguments of a command are invalid
     */
    #define INVALID_ARGS "sbp\n"

#endif /* SERVER_MACROS_H_ */
