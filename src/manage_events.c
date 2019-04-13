/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** manage_event
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "myftp.h"

static void server_event(socket_list_t *list, socket_t *server)
{
    socket_t *tmp = socket_server_accept_cli(server);

    if (tmp != NULL) {
        socket_list_add(list, tmp);
        write(tmp->fd, "220 (vsFTPd 3.0.0)\r\n", 21);
    }
}

static void client_event(socket_list_t *list, socket_t *client, char *path)
{
    char *buff = read_line(client);

    if (buff == NULL) {
        printf("Client %d disconnected\n", client->fd);
        socket_list_remove(list, client);
    }
    else {
        printf("Client %d: %s\n", client->fd, buff);
        free(buff);
    }
}

void manage_event(socket_list_t *list, socket_t **evt_socks, char *path)
{
    for (size_t i = 0; evt_socks[i] != NULL; i++)
        if (evt_socks[i]->type == SERVER)
            server_event(list, evt_socks[i]);
        else
            client_event(list, evt_socks[i], path);
}