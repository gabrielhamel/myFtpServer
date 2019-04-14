/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** noop
*/

#include <unistd.h>
#include "responses.h"
#include "commands.h"
#include "socket.h"

void command_noop(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    (void)arg;
    (void)path;
    (void)list;
    if (!user_connected(cli))
        return;
    write(cli->fd, CODE_200_NOOP, sizeof(CODE_200_NOOP) - 1);
}