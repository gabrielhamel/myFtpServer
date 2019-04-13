/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** server_data
*/

#include <unistd.h>
#include "myftp.h"

void *init_server(const socket_t *cli)
{
    printf("New server %d, ftp listening\n", cli->fd);
    return (NULL);
}

void end_server(const socket_t *cli, void *data)
{
    (void)data;
    printf("End of %d\n", cli->fd);
}