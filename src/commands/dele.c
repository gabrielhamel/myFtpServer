/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** dele
*/

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "responses.h"
#include "commands.h"
#include "socket.h"
#include "utils.h"
#include "myftp.h"

static void print_return(socket_t *cli, int ret)
{
    if (ret == -1)
        write(cli->fd, CODE_550_DELE, sizeof(CODE_550_DELE) - 1);
    else
        write(cli->fd, CODE_250_DEL, sizeof(CODE_250_DEL) - 1);
}

void command_dele(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    char *tmp;
    char *realfile;

    (void)list;
    if (!user_connected(cli))
        return;
    if (array_lenght(arg) < 2) {
        write(cli->fd, CODE_550_DELE, sizeof(CODE_550_DELE) - 1);
        return;
    }
    tmp = get_file(path, ((ftp_cli_t *)cli->data)->path, arg[1]);
    if (tmp == NULL) {
        write(cli->fd, CODE_550_DELE, sizeof(CODE_550_DELE) - 1);
        return;
    }
    realfile = get_path(path, ((ftp_cli_t *)cli->data)->path, arg[1]);
    print_return(cli, unlink(realfile));
    free(realfile);
    free(tmp);
}