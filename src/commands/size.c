/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** size
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

void command_size(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    char *tmp;
    char *realfile;
    struct stat info;

    (void)list;
    if (!user_connected(cli))
        return;
    if (array_lenght(arg) < 2) {
        write(cli->fd, CODE_550_FILE, sizeof(CODE_550_FILE) - 1);
        return;
    }
    tmp = get_file(path, ((ftp_cli_t *)cli->data)->path, arg[1]);
    if (tmp == NULL) {
        write(cli->fd, CODE_550_FILE, sizeof(CODE_550_FILE) - 1);
        return;
    }
    realfile = get_path(path, ((ftp_cli_t *)cli->data)->path, arg[1]);
    stat(realfile, &info);
    free(realfile);
    free(tmp);
    dprintf(cli->fd, CODE_213, info.st_size);
}