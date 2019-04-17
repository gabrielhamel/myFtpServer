/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** stor
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include "commands.h"
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"
#include "responses.h"
#include "socket.h"
#include "myftp.h"

static int prepare_file(char *real_root, char *fake_root, char *path)
{
    char *real = get_path_file(real_root, fake_root, path);
    char *absolute_root = realpath(real_root, NULL);
    int tmp;

    if (real == NULL || strstr(real, absolute_root) != real) {
        if (real)
            free(real);
        free(absolute_root);
        return (-1);
    }
    tmp = creat(real, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    free(real);
    return (tmp);
}

static void upload_file(int fd, socket_t *cli)
{
    int chan = ((socket_t *)(((ftp_cli_t *)cli->data)->data_chan->data))->fd;
    char buff[READ_SIZE] = {0};
    ssize_t readed;

    write(cli->fd, CODE_150_UP, sizeof(CODE_150_UP) - 1);
    while ((readed = read(chan, buff, READ_SIZE)))
        write(fd, buff, readed);
    write(cli->fd, CODE_226_UP, sizeof(CODE_226_UP) - 1);
    close(fd);
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
            destroy_ftp_child(list, cli, arg);
        }
        upload_file(fd, cli);
        destroy_ftp_child(list, cli, arg);
    }
    destroy_channel(cli);
}