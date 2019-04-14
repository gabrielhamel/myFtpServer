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

void *init_client(const socket_t *cli)
{
    ftp_cli_t *data = malloc(sizeof(ftp_cli_t));

    write(cli->fd, CODE_220, sizeof(CODE_220));
    printf("New client %d\n", cli->fd);
    memset(data, 0, sizeof(ftp_cli_t));
    return (data);
}

void end_client(const socket_t *cli, void *data)
{
    if (data != NULL) {
        if (((ftp_cli_t *)cli->data)->username)
            free(((ftp_cli_t *)cli->data)->username);
        free(data);
    }
    write(cli->fd, CODE_221, sizeof(CODE_221));
    printf("Client %d disconnected\n", cli->fd);
}