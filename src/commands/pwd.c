/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** pwd
*/

#include <unistd.h>
#include <stdio.h>
#include "responses.h"
#include "socket.h"
#include "myftp.h"
#include "commands.h"

void command_pwd(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    (void)arg;
    (void)path;
    (void)list;
    if (!user_connected(cli))
        return;
    dprintf(cli->fd, CODE_257, ((ftp_cli_t *)cli->data)->path);
}