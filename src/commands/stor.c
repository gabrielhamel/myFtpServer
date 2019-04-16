/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** stor
*/

#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include "commands.h"
#include <unistd.h>
#include "utils.h"
#include "responses.h"
#include "socket.h"
#include "myftp.h"

static void upload_file(int fd, socket_t *cli)
{
    int chan = ((socket_t *)(((ftp_cli_t *)cli->data)->data_chan->data))->fd;
    size_t n = 0;
    char *tmp = NULL;
    FILE *file = fdopen(chan, "r");

    write(cli->fd, CODE_150_UP, sizeof(CODE_150_UP) - 1);
    while (getline(&tmp, &n, file) != -1) { // #FIXME
        write(fd, tmp, n);
        free(tmp);
        tmp = NULL;
    }
    write(cli->fd, CODE_226_UP, sizeof(CODE_226_UP) - 1);
    fclose(file);
}

void command_stor(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    pid_t pid;
    int fd;

    if (!user_connected(cli) || !data_channel(cli))
        return;
    fd = prepare_file(path, ((ftp_cli_t *)cli->data)->path, arg[1]);
    if (fd == -1) {
        write(cli->fd, CODE_553, sizeof(CODE_553) - 1);
        return;
    }
    pid = duplicate();
    if (pid == 0) {
        if (!wait_child_client(list, cli)) {
            write(cli->fd, CODE_425, sizeof(CODE_425) - 1);
            destroy_array(arg);
            destroy_ftp_child(list, cli);
        }
        upload_file(fd, cli);
        destroy_array(arg);
        destroy_ftp_child(list, cli);
    }
}