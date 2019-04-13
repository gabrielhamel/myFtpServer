/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** client_data
*/

#include <unistd.h>
#include "myftp.h"

void *init_client(const socket_t *cli)
{
    write(cli->fd, "220 (vsFTPd 3.0.0)\r\n", 21);
    return (NULL);
}

void end_client(const socket_t *cli, void *data)
{
    (void)data;
    write(cli->fd, "221 Goodbye.\r\n", 15);
}