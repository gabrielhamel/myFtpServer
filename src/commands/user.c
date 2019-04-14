/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** user
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"
#include "responses.h"
#include "myftp.h"
#include "utils.h"

void command_user(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    (void)path;
    (void)list;
    if (((ftp_cli_t *)cli->data)->lvl != CONNECTED && array_lenght(arg) < 2) {
        write(cli->fd, CODE_530_DENIED, sizeof(CODE_530_DENIED) - 1);
        return;
    }
    if (((ftp_cli_t *)cli->data)->lvl != CONNECTED && array_lenght(arg) >= 2) {
        ((ftp_cli_t *)cli->data)->lvl = JUST_USER;
        if (((ftp_cli_t *)cli->data)->username)
            free(((ftp_cli_t *)cli->data)->username);
        ((ftp_cli_t *)cli->data)->username = strdup(arg[1]);
        write(cli->fd, CODE_331, sizeof(CODE_331) - 1);
        return;
    }
    write(cli->fd, CODE_530_CHANGE, sizeof(CODE_530_CHANGE) - 1);
}