/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function to get the IP address of the server
*/
/**
 * @file get_ip.c
 * @brief The file containing the function to get the IP address of the server
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "network.h"

static bool connect_to_dns_server(int socket_fd,
    struct sockaddr_in *serv, struct sockaddr_in *name)
{
    socklen_t namelen = sizeof(struct sockaddr_in);

    if (inet_pton(AF_INET, GOOGLE_DNS_IP, &serv->sin_addr) <= 0)
        return false;
    if (connect(socket_fd, (const struct sockaddr *)serv, namelen) < 0)
        return false;
    if (getsockname(socket_fd, (struct sockaddr *)name, &namelen) < 0)
        return false;
    return true;
}

char *get_ip_address(void)
{
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serv = {0};
    struct sockaddr_in name = {0};
    char *address = NULL;

    if (socket_fd < 0)
        return NULL;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(DNS_PORT);
    if (!connect_to_dns_server(socket_fd, &serv, &name)) {
        close(socket_fd);
        return NULL;
    }
    address = AL(FALSE, my_calloc, INET_ADDRSTRLEN, sizeof(char));
    inet_ntop(AF_INET, &name.sin_addr, address, INET_ADDRSTRLEN);
    close(socket_fd);
    return address;
}
