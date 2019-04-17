/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** list
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

static FILE *prepare_file(char *path)
{
    char *str = str_add(2, "ls -l ", path);
    FILE *file;
    size_t n = 0;

    free(path);
    file = popen(str, "r");
    free(str);
    str = NULL;
    getline(&str, &n, file);
    free(str);
    return (file);
}

static void print_directory(char *rroot, char *froot, int fd)
{
    char *path = get_path(rroot, froot, "");
    FILE *file;
    char *str = NULL;
    size_t n = 0;
    char *tmp;

    file = prepare_file(path);
    while (getline(&str, &n, file) != -1) {
        str[strlen(str) - 1] = '\0';
        tmp = str_add(2, str, "\r\n");
        write(fd, tmp, strlen(tmp));
        free(tmp);
        free(str);
        str = NULL;
    }
    pclose(file);
    if (str)
        free(str);
}

void destroy_channel(socket_t *cli)
{
    if (((ftp_cli_t *)cli->data)->mode == ACTIVE) {
        socket_destroy_no_close(((ftp_cli_t *)cli->data)->data_chan);
        ((ftp_cli_t *)cli->data)->data_chan = NULL;
    }
}

void command_list(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    pid_t pid;

    if (!user_connected(cli) || !data_channel(cli))
        return;
    pid = duplicate();
    if (pid == 0) {
        if (!wait_child_client(list, cli)) {
            write(cli->fd, CODE_425, sizeof(CODE_425) - 1);
            destroy_ftp_child(list, cli, arg);
        }
        write(cli->fd, CODE_150, sizeof(CODE_150) - 1);
        print_directory(path, ((ftp_cli_t *)cli->data)->path,
        ((socket_t *)(((ftp_cli_t *)cli->data)->data_chan->data))->fd);
        write(cli->fd, CODE_226, sizeof(CODE_226) - 1);
        destroy_ftp_child(list, cli, arg);
    }
    destroy_channel(cli);
}