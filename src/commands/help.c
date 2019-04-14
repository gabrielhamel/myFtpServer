/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** help
*/

#include <unistd.h>
#include "myftp.h"
#include "responses.h"
#include "utils.h"
#include "commands.h"

void command_help(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    (void)arg;
    (void)path;
    (void)list;
    if (!user_connected(cli))
        return;
    write(cli->fd, CODE_214_START, sizeof(CODE_214_START) - 1);
    for (size_t i = 0; i < commands_lenght(); i++) {
        if (i == commands_lenght() - 1) {
            write(cli->fd, commands_g[i].name, strlen(commands_g[i].name));
            write(cli->fd, "\r\n", 2);
            break;
        }
        if (i % 14 == 0)
            write(cli->fd, "\r\n ", 3);
        write(cli->fd, commands_g[i].name, strlen(commands_g[i].name));
        if ((i + 1) % 14 != 0)
            write(cli->fd, " ", 1);
    }
    write(cli->fd, CODE_214_END, sizeof(CODE_214_END) - 1);
}