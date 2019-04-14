/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** server_data
*/

#include <unistd.h>
#include "myftp.h"

void *init_serv_child(const socket_t *cli)
{
    printf("New FTP child %d\n", cli->fd);
    return (NULL);
}

void end_serv_child(const socket_t *cli, void *data)
{
    (void)data;
    printf("End of FTP child %d\n", cli->fd);
}

void *init_server(const socket_t *cli)
{
    printf("New FTP main %d\n", cli->fd);
    return ("main");
}

void end_server(const socket_t *cli, void *data)
{
    (void)data;
    printf("End of FTP main %d\n", cli->fd);
}