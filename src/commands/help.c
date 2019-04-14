/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** help
*/

#include <unistd.h>
#include <string.h>
#include "myftp.h"
#include "responses.h"
#include "utils.h"
#include "commands.h"

static void write_word(int fd, size_t i)
{
    size_t max_len = strlen(commands_g[i].name);

    for (size_t j = 0; j < commands_lenght(); j++)
        if (j % 14 == i % 14 && strlen(commands_g[j].name) > max_len)
            max_len = strlen(commands_g[j].name);
    max_len = max_len - strlen(commands_g[i].name) + 1;
    write(fd, commands_g[i].name, strlen(commands_g[i].name));
    if ((i + 1) % 14 != 0 && i != commands_lenght() - 1)
        for (size_t j = 0; j != max_len; j++)
            write(fd, " ", 1);
    if (i == commands_lenght() - 1)
        write(fd, "\r\n ", 2);
}

void command_help(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    (void)arg;
    (void)path;
    (void)list;
    if (!user_connected(cli))
        return;
    write(cli->fd, CODE_214_START, sizeof(CODE_214_START) - 1);
    for (size_t i = 0; i < commands_lenght(); i++) {
        if (i % 14 == 0)
            write(cli->fd, "\r\n ", 2);
        write_word(cli->fd, i);
    }
    write(cli->fd, CODE_214_END, sizeof(CODE_214_END) - 1);
}