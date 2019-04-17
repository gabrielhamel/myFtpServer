/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** client
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

uint32_t convert_ip(char *ip)
{
    return (inet_addr(ip));
}

socket_t *socket_client_create(uint16_t port, uint32_t ipaddr,
void *(*ctor)(const socket_t *), void (*dtor)(const socket_t *, void *))
{
    socket_t *socket = socket_create(ctor, dtor);

    if (socket == NULL)
        return (NULL);
    socket->info.sin_port = htons(port);
    socket->info.sin_family = AF_INET;
    socket->info.sin_addr.s_addr = ipaddr;
    if (connect(socket->fd, (struct sockaddr *)&socket->info,
    sizeof(struct sockaddr_in)) == -1) {
        socket_destroy(socket);
        return (NULL);
    }
    return (socket);
}