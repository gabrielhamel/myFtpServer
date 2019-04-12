/*
** EPITECH PROJECT, 2019
** bootstrap
** File description:
** socket
*/

#ifndef SOCKET_H
#define SOCKET_H

#include <netinet/in.h>
#include <stdbool.h>

typedef struct socket_t {
    int fd;
    struct sockaddr_in info;
} socket_t;

int socket_server_create(uint16_t port, int max_cli);
int socket_server_destroy(socket_t *server);
bool socket_server_have_new_client(const socket_t *server);
socket_t *socket_server_accept_cli(const socket_t *server);

#endif