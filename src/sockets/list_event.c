/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** list_event
*/

#include <stdlib.h>
#include <string.h>
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

socket_t **socket_list_get_event(socket_list_t *list)
{
    fd_set tmp = list->fdlist;
    int ret = select(FD_SETSIZE, &tmp, NULL, NULL, NULL);
    socket_t **tab = NULL;
    size_t idx = 0;

    if (ret == 0 || ret == -1)
        return (NULL);
    tab = malloc(sizeof(socket_t *) * (ret + 1));
    if (tab == NULL)
        return (NULL);
    memset(tab, 0, sizeof(socket_t *) * (ret + 1));
    for (int i = 0; i < FD_SETSIZE; i++)
        if (FD_ISSET(i, &tmp))
            tab[idx++] = socket_list_get_socket(list, i);
    return (tab);
}