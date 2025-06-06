/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The gui.h
*/
/**
 * @file gui.h
 * @brief The gui.h
 * @author Nicolas TORO
 */

#ifndef GUI_H_
    #define GUI_H_

    #include "server_data_structures.h"

/* Command handler functions for GUI clients */

/**
 * @brief Handles the "msz" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_msz(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "bct" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_bct(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "mct" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_mct(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "tna" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_tna(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "ppo" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_ppo(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "plv" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_plv(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "pin" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_pin(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "sgt" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_sgt(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "sst" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_sst(server_t *server, client_t *client, char **args);



/* Command sender functions for GUI clients */

/**
 * @brief Send the "msz" command to all GUI clients
 * @param server The server instance
 */
void send_msz_to_gui(server_t *server);

/**
 * @brief Send the "bct" command to all GUI clients
 * @param server The server instance
 * @param position The position of the tile to send
 */
void send_bct_to_gui(server_t *server, vector2u_t position);

/**
 * @brief Send the "tna" command to all GUI clients
 * @param server The server instance
 */
void send_tna_to_gui(server_t *server);

/**
 * @brief Send the "pnw" command to all GUI clients
 * @param server The server instance
 */
void send_pnw_to_gui(server_t *server, player_t *player);

/**
 * @brief Send the "ppo" command to all GUI clients
 * @param server The server instance
 * @param player The player whose information is being sent
 */
void send_ppo_to_gui(server_t *server, player_t *player);

/**
 * @brief Send the "pin" command to all GUI clients
 * @param server The server instance
 * @param player The player whose information is being sent
 */
void send_pin_to_gui(server_t *server, player_t *player);

/**
 * @brief Send the "pex" command to all GUI clients
 * @param server The server instance
 * @param player The player whose information is being sent
 */
void send_pex_to_gui(server_t *server, player_t *player);

/**
 * @brief Send the "pbc" command to all GUI clients
 * @param server The server instance
 * @param player The player whose information is being sent
 * @param message The message to be sent
 */
void send_pbc_to_gui(server_t *server, player_t *player, const char *message);

/**
 * @brief Send the "pic" command to all GUI clients
 * @param server The server instance
 * @param player_list The list of players to be sent
 * @param position The position of the incantation
 * @param level The level of the incantation
 */
void send_pic_to_gui(server_t *server, node_t *player_list,
    vector2u_t position, size_t level);

/**
 * @brief Send the "pie" command to all GUI clients
 * @param server The server instance
 */
void send_pie_to_gui(server_t *server);

/**
 * @brief Send the "pfk" command to all GUI clients
 * @param server The server instance
 * @param player The player whose information is being sent
 */
void send_pfk_to_gui(server_t *server, player_t *player);

/**
 * @brief Send the "pdr" command to all GUI clients
 * @param server The server instance
 * @param player The player whose information is being sent
 * @param resource_id The ID of the resource being sent
 */
void send_pdr_to_gui(server_t *server, player_t *player, size_t resource_id);

/**
 * @brief Send the "pgt" command to all GUI clients
 * @param server The server instance
 * @param player The player whose information is being sent
 * @param resource_id The ID of the resource being sent
 */
void send_pgt_to_gui(server_t *server, player_t *player, size_t resource_id);

/**
 * @brief Send the "pdi" command to all GUI clients
 * @param server The server instance
 * @param player The player whose information is being sent
 */
void send_pdi_to_gui(server_t *server, player_t *player);

/**
 * @brief Send the "enw" command to all GUI clients
 * @param server The server instance
 * @param egg The egg whose information is being sent
 * @param player The player associated with the egg
 */
void send_enw_to_gui(server_t *server, player_t *egg,
    player_t *player);

/**
 * @brief Send the "ebo" command to all GUI clients
 * @param server The server instance
 * @param egg The egg whose information is being sent
 */
void send_ebo_to_gui(server_t *server, player_t *egg);

/**
 * @brief Send the "edi" command to all GUI clients
 * @param server The server instance
 * @param egg The egg whose information is being sent
 */
void send_edi_to_gui(server_t *server, player_t *egg);

/**
 * @brief Send the "sgt" command to all GUI clients
 * @param server The server instance
 */
void send_sgt_to_gui(server_t *server);

/**
 * @brief Send the "sst" command to all GUI clients
 * @param server The server instance
 * @param time_unit The time unit to be sent
 */
void send_sst_to_gui(server_t *server, size_t time_unit);

/**
 * @brief Send the "seg" command to all GUI clients
 * @param server The server instance
 * @param team The team whose information is being sent
 */
void send_seg_to_gui(server_t *server, team_t *team);

/**
 * @brief Send the "smg" command to all GUI clients
 * @param server The server instance
 * @param message The message to be sent
 */
void send_smg_to_gui(server_t *server, const char *message);

/**
 * @brief Send the "suc" command to all GUI clients
 * @param server The server instance
 */
void send_suc_to_gui(server_t *server);

/**
 * @brief Send the "sbp" command to all GUI clients
 * @param server The server instance
 */
void send_sbp_to_gui(server_t *server);



#endif /* GUI_H_ */
