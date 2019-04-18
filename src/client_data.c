/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** client_data
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "responses.h"
#include "myftp.h"

void *init_cli_child(const socket_t *cli)
{
    printf("FTP child: New client %d\n", cli->fd);
    return ("child");
}

void end_cli_child(const socket_t *cli, void *data)
{
    (void)data;
    printf("FTP child: Client %d disconnected\n", cli->fd);
}

void *init_client(const socket_t *cli)
{
    ftp_cli_t *data = malloc(sizeof(ftp_cli_t));

    memset(data, 0, sizeof(ftp_cli_t));
    write(cli->fd, CODE_220, sizeof(CODE_220) - 1);
    printf("FTP main: New client %d\n", cli->fd);
    data->path = strdup("/");
    data->buff = strdup("");
    return (data);
}

void end_client(const socket_t *cli, void *data)
{
    if (data != NULL) {
        free(((ftp_cli_t *)cli->data)->buff);
        if (((ftp_cli_t *)cli->data)->data_chan)
            socket_destroy_no_close(((ftp_cli_t *)cli->data)->data_chan);
        if (((ftp_cli_t *)cli->data)->username)
            free(((ftp_cli_t *)cli->data)->username);
        free(((ftp_cli_t *)cli->data)->path);
        free(data);
    }
    printf("FTP main: Client %d disconnected\n", cli->fd);
}