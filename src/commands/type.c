/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** type
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "responses.h"
#include "socket.h"
#include "myftp.h"
#include "commands.h"
#include "utils.h"

void command_type(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    size_t len = array_lenght(arg);

    (void)path;
    (void)list;
    if (!user_connected(cli))
        return;
    if (len < 2) {
        write(cli->fd, CODE_500_TYPE, sizeof(CODE_500_TYPE) - 1);
        return;
    }
    if (!strcasecmp(arg[1], "I"))
        write(cli->fd, CODE_200_BIN, sizeof(CODE_200_BIN) - 1);
    else if (!strcasecmp(arg[1], "A"))
        write(cli->fd, CODE_200_ASC, sizeof(CODE_200_ASC) - 1);
    else
        write(cli->fd, CODE_500_TYPE, sizeof(CODE_500_TYPE) - 1);
}