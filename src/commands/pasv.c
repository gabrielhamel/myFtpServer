/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** pasv
*/

#include "commands.h"
#include "socket.h"

void command_pasv(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    (void)arg;
    (void)path;
    (void)list;
    if (!user_connected(cli))
        return;
}