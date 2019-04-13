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

static socket_t *socket_create(void *(*ctor)(const socket_t *),
void (*dtor)(const socket_t *, void *))
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
    sock->ctor = ctor;
    sock->dtor = dtor;
    if (sock->ctor != NULL)
        sock->data = sock->ctor(sock);
    return (sock);
}

socket_t *socket_server_create(uint16_t port,
void *(*ctor)(const socket_t *), void (*dtor)(const socket_t *, void *))
{
    socket_t *socket = socket_create(ctor, dtor);

    if (socket == NULL)
        return (NULL);
    socket->info.sin_port = htons(port);
    socket->info.sin_family = AF_INET;
    socket->info.sin_addr.s_addr = INADDR_ANY;
    if (bind(socket->fd, (struct sockaddr *)&socket->info,
    sizeof(struct sockaddr_in)) == -1)
        return (NULL);
    if (listen(socket->fd, SOMAXCONN) == -1)
        return (NULL);
    socket->type = SERVER;
    return (socket);
}

int socket_destroy(socket_t *socket)
{
    if (socket->dtor != NULL)
        socket->dtor(socket, socket->data);
    shutdown(socket->fd, SHUT_RDWR);
    fclose(socket->file);
    free(socket);
    return (0);
}

socket_t *socket_server_accept_cli(socket_t *server,
void *(*ctor)(const socket_t *), void (*dtor)(const socket_t *, void *))
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
    client->ctor = ctor;
    client->dtor = dtor;
    if (client->ctor != NULL)
        client->data = client->ctor(client);
    return (client);
}