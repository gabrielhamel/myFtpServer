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

    (void)arg;
    (void)path;
    (void)list;
    if (!user_connected(cli))
        return;
    if (len < 2 || strcasecmp(arg[1], "I")) {
        write(cli->fd, CODE_500_TYPE, sizeof(CODE_500_TYPE) - 1);
        return;
    }
    write(cli->fd, CODE_200_BIN, sizeof(CODE_200_BIN) - 1);
}