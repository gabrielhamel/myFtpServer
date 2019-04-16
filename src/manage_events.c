/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** manage_event
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"
#include "myftp.h"

static void server_event(socket_list_t *list, socket_t *server)
{
    socket_t *tmp;

    if (server->data && !strcmp(server->data, "main"))
        tmp = socket_server_accept_cli(server, init_client, end_client);
    if (tmp != NULL)
        socket_list_add(list, tmp);
}

static void destroy_ftp_sock(socket_list_t *list, socket_t *cli)
{
    if (((ftp_cli_t *)cli->data)->data_chan)
        socket_list_remove(list, ((ftp_cli_t *)cli->data)->data_chan);
    ((ftp_cli_t *)cli->data)->data_chan = NULL;
    socket_list_remove(list, cli);
}

static void client_event(socket_list_t *list, socket_t *client, char *path)
{
    char **buff = read_lines(client);
    char **toks;

    if (buff == NULL)
        destroy_ftp_sock(list, client);
    else {
        for (size_t i = 0; buff[i] != NULL; i++) {
            printf("FTP main %d: %s\n", client->fd, buff[i]);
            toks = tokenize(buff[i], " ");
            if (toks != NULL)
                exec_command(client, list, toks, path);
            if (toks != NULL)
                destroy_array(toks);
        }
        destroy_array(buff);
    }
}

static void child_event(socket_list_t *list, socket_t *client)
{
    char **buff = read_lines(client);

    if (buff == NULL)
        socket_list_remove(list, client);
    else {
        for (size_t i = 0; buff[i] != NULL; i++)
            printf("FTP child %d: %s\n", client->fd, buff[i]);
        destroy_array(buff);
    }
}

void manage_event(socket_list_t *list, socket_t **evt_socks, char *path)
{
    for (size_t i = 0; evt_socks[i] != NULL; i++)
        if (evt_socks[i]->type == SERVER)
            server_event(list, evt_socks[i]);
        else if (!strcmp("child", evt_socks[i]->data))
            child_event(list, evt_socks[i]);
        else
            client_event(list, evt_socks[i], path);
}