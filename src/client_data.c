/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** client_data
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "myftp.h"

void *init_client(const socket_t *cli)
{
    ftp_cli_t *data = malloc(sizeof(ftp_cli_t));

    write(cli->fd, "220 (vsFTPd 3.0.0)\r\n", 21);
    printf("New client %d\n", cli->fd);
    memset(data, 0, sizeof(ftp_cli_t));
    return (data);
}

void end_client(const socket_t *cli, void *data)
{
    if (data != NULL)
        free(data);
    write(cli->fd, "221 Goodbye.\r\n", 15);
    printf("Client %d disconnected\n", cli->fd);
}