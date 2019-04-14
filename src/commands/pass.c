/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** pass
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"
#include "responses.h"
#include "myftp.h"
#include "utils.h"

void command_pass(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    (void)path;
    (void)list;
    if (((ftp_cli_t *)cli->data)->lvl == NOT_CONNECT) {
        write(cli->fd, CODE_503, sizeof(CODE_503));
        return;
    }
    if (((ftp_cli_t *)cli->data)->lvl == CONNECTED) {
        write(cli->fd, CODE_230_ALREADY, sizeof(CODE_230_ALREADY));
        return;
    }
    if (user_is_valid(((ftp_cli_t *)cli->data)->username, arg[1])) {
        ((ftp_cli_t *)cli->data)->lvl = CONNECTED;
        write(cli->fd, CODE_230, sizeof(CODE_230));
        printf("%d User %s connected\n", cli->fd,
        ((ftp_cli_t *)cli->data)->username);
        return;
    }
    write(cli->fd, CODE_530_PASS, sizeof(CODE_530_PASS));
}