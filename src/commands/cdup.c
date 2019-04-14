/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** cdup
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include "responses.h"
#include "commands.h"
#include "socket.h"
#include "myftp.h"

void command_cdup(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    char *tmp;

    (void)arg;
    (void)path;
    (void)list;
    if (!user_connected(cli))
        return;
    tmp = strdup(dirname(((ftp_cli_t *)cli->data)->path));
    free(((ftp_cli_t *)cli->data)->path);
    ((ftp_cli_t *)cli->data)->path = tmp;
    write(cli->fd, CODE_250, sizeof(CODE_250) - 1);
}