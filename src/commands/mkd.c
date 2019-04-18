/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** mkd
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "responses.h"
#include "commands.h"
#include "socket.h"
#include "utils.h"
#include "myftp.h"

static void create_directory(socket_t *cli, char *tmp, char *name)
{
    char *new = str_add(3, tmp, "/", name);
    int ret = mkdir(new, 0775);

    free(new);
    if (ret) {
        write(cli->fd, CODE_550_MKD, sizeof(CODE_550_MKD) - 1);
        return;
    }
    dprintf(cli->fd, CODE_257_MKD, name);
}

void command_mkd(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    char *tmp;

    (void)list;
    if (!user_connected(cli))
        return;
    if (array_lenght(arg) < 2) {
        write(cli->fd, CODE_550_MKD, sizeof(CODE_550_MKD) - 1);
        return;
    }
    tmp = get_path(path, ((ftp_cli_t *)cli->data)->path, "");
    if (tmp == NULL) {
        write(cli->fd, CODE_550_MKD, sizeof(CODE_550_MKD) - 1);
        return;
    }
    create_directory(cli, tmp, arg[1]);
    free(tmp);
}