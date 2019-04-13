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
    sock->file = fdopen(sock->fd, "r");
    return (sock);
}

socket_t *socket_server_create(uint16_t port, int max_cli)
{
    socket_t *socket = socket_create();

    if (socket == NULL)
        return (NULL);
    socket->info.sin_port = htons(port);
    socket->info.sin_family = AF_INET;
    socket->info.sin_addr.s_addr = INADDR_ANY;
    if (bind(socket->fd, (struct sockaddr *)&socket->info,
    sizeof(struct sockaddr_in)) == -1)
        return (NULL);
    if (listen(socket->fd, max_cli) == -1)
        return (NULL);
    socket->type = SERVER;
    return (socket);
}

int socket_destroy(socket_t *server)
{
    shutdown(server->fd, SHUT_RDWR);
    fclose(server->file);
    free(server);
    return (0);
}

socket_t *socket_server_accept_cli(const socket_t *server)
{
    socket_t *client = malloc(sizeof(socket_t));
    int fd = -1;
    socklen_t size = sizeof(struct sockaddr_in);

    memset(client, 0, sizeof(socket_t));
    fd = accept(server->fd, (struct sockaddr *)&client->info, &size);
    if (fd == -1)
        return (NULL);
    if (client == NULL)
        return (NULL);
    client->fd = fd;
    client->type = CLIENT;
    client->file = fdopen(client->fd, "r");
    return (client);
}