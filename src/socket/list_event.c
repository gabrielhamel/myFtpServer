/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** list_event
*/

#include <stddef.h>
#include "socket.h"

socket_t *socket_list_get_socket(socket_list_t *list, int fd)
{
    socket_node_t *node = list->start;

    if (list->start == NULL)
        return (NULL);
    for (; node != NULL; node = node->next)
        if (node->socket->fd == fd)
            return (node->socket);
    return (NULL);
}

socket_t *socket_list_get_event(socket_list_t *list)
{
    fd_set tmp = list->fdlist;
    struct timeval timeout = {.tv_sec = 0, .tv_usec = SERVER_REFRESH_USEC};
    int ret = select(FD_SETSIZE, &tmp, NULL, NULL, &timeout);

    if (ret == 0 || ret == -1)
        return (NULL);
    for (int i = 0; i < FD_SETSIZE; i++)
        if (FD_ISSET(i, &tmp))
            return (socket_list_get_socket(list, i));
    return (NULL);
}