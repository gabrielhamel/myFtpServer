/*
** EPITECH PROJECT, 2019
** bootstrap
** File description:
** socket
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "socket.h"

static socket_t *socket_create(void)
{
    socket_t *sock = malloc(sizeof(socket_t));
    int option = 1;

    if (sock == NULL)
        return (NULL);
    memset(sock, 0, sizeof(socket_t));
    sock->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->fd == -1)
        return (NULL);
    if (setsockopt(sock->fd, SOL_SOCKET, SO_REUSEADDR, &option,
    sizeof(int)) == -1)
        return (NULL);
    return (sock);
}

int socket_server_create(uint16_t port, int max_cli)
{
    socket_t *socket = socket_create();

    if (socket == NULL)
        return (-1);
    socket->info.sin_port = htons(port);
    socket->info.sin_family = AF_INET;
    socket->info.sin_addr.s_addr = INADDR_ANY;
    if (bind(socket->fd, (struct sockaddr *)&socket->info,
    sizeof(struct sockaddr_in)) == -1)
        return (-1);
    return (listen(socket->fd, max_cli));
}

int socket_server_destroy(socket_t *server)
{
    if (close(server->fd) == -1)
        return (-1);
    free(server);
    return (0);
}

bool socket_server_have_new_client(const socket_t *server)
{
    fd_set wfds;
    int ret;

    FD_ZERO(&wfds);
    FD_SET(server->fd, &wfds);
    ret = select(1, NULL, &wfds, NULL, NULL);
    if (ret == 0 || ret == -1)
        return (false);
    return (true);
}

socket_t *socket_server_accept_cli(const socket_t *server)
{
    socket_t *client = NULL;
    int fd = -1;
    socklen_t size = sizeof(struct sockaddr_in);

    fd = accept(server->fd, (struct sockaddr *)&client->info, &size);
    if (client->fd == -1)
        return (NULL);
    client = malloc(sizeof(socket_t));
    if (client == NULL)
        return (NULL);
    memset(client, 0, sizeof(socket_t));
    client->fd = fd;
    return (client);
}