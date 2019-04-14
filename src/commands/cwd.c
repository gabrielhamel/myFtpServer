/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** cwd
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include "responses.h"
#include "commands.h"
#include "socket.h"
#include "utils.h"
#include "myftp.h"

void command_cwd(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    char *tmp;

    (void)list;
    if (!user_connected(cli))
        return;
    if (array_lenght(arg) < 2) {
        write(cli->fd, CODE_550, sizeof(CODE_550) - 1);
        return;
    }
    tmp = change_dir(path, ((ftp_cli_t *)cli->data)->path, arg[1]);
    if (tmp == NULL) {
        write(cli->fd, CODE_550, sizeof(CODE_550) - 1);
        return;
    }
    free(((ftp_cli_t *)cli->data)->path);
    ((ftp_cli_t *)cli->data)->path = tmp;
    write(cli->fd, CODE_250, sizeof(CODE_250) - 1);
}