/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** retr
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include "commands.h"
#include <unistd.h>
#include "utils.h"
#include "responses.h"
#include "socket.h"
#include "myftp.h"

static void download_file(int fd, socket_t *cli, char *name)
{
    int chan = ((socket_t *)(((ftp_cli_t *)cli->data)->data_chan->data))->fd;
    char buff[READ_SIZE] = {0};
    ssize_t readed;
    struct stat info = {0};

    fstat(fd, &info);
    dprintf(cli->fd, CODE_150_BIN, name, info.st_size);
    while ((readed = read(fd, buff, READ_SIZE)))
        write(chan, buff, readed);
    write(cli->fd, CODE_226_UP, sizeof(CODE_226_UP) - 1);
    close(fd);
}

static int prepare_file(char *real_root, char *fake_root, char *path)
{
    char *rpath = get_path_file(real_root, fake_root, path);
    int fd;

    if (rpath == NULL)
        return (-1);
    fd = open(rpath, O_RDONLY);
    free(rpath);
    return (fd);
}

void command_retr(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    pid_t pid;
    int fd;

    if (!user_connected(cli) || !data_channel(cli))
        return;
    fd = prepare_file(path, ((ftp_cli_t *)cli->data)->path, arg[1]);
    if (fd == -1) {
        write(cli->fd, CODE_550_OPEN, sizeof(CODE_550_OPEN) - 1);
        return;
    }
    pid = duplicate();
    if (pid == 0) {
        if (!wait_child_client(list, cli)) {
            write(cli->fd, CODE_425, sizeof(CODE_425) - 1);
            destroy_array(arg);
            destroy_ftp_child(list, cli);
        }
        download_file(fd, cli, arg[1]);
        destroy_array(arg);
        destroy_ftp_child(list, cli);
    }
}