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

static void print_directory(char *rroot, char *froot, int fd)
{
    char *path = get_path(rroot, froot, "");
    FILE *file;
    size_t n = 0;
    char *tmp;
    char *str = str_add(2, "ls -l ", path);

    free(path);
    file = popen(str, "r");
    free(str);
    getline(&str, &n, file);
    free(str);
    str = NULL;
    while (getline(&str, &n, file) != -1) {
        str[strlen(str) - 1] = '\0';
        tmp = str_add(2, str, "\r\n");
        write(fd, tmp, strlen(tmp));
        free(tmp);
        free(str);
        str = NULL;
    }
    pclose(file);
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
            destroy_array(arg);
            destroy_ftp_child(list, cli);
        }
        write(cli->fd, CODE_150, sizeof(CODE_150) - 1);
        print_directory(path, ((ftp_cli_t *)cli->data)->path,
        ((socket_t *)(((ftp_cli_t *)cli->data)->data_chan->data))->fd);
        write(cli->fd, CODE_226, sizeof(CODE_226) - 1);
        destroy_array(arg);
        destroy_ftp_child(list, cli);
    }
}