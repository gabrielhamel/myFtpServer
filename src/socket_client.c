/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** socket_client
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "responses.h"
#include "myftp.h"

void *init_ftp_cli_child(const socket_t *cli)
{
    printf("FTP main: New ftp client %d\n", cli->fd);
    return (NULL);
}

void end_ftp_cli_child(const socket_t *cli, void *data)
{
    (void)data;
    printf("FTP main: Ftp client %d disconnected\n", cli->fd);
}