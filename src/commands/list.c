/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** list
*/

#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include "commands.h"
#include <unistd.h>
#include "utils.h"
#include "responses.h"
#include "socket.h"
#include "myftp.h"

void command_list(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    pid_t pid;

    (void)arg;
    (void)list;
    if (!user_connected(cli) || !data_channel(cli))
        return;
    pid = duplicate();
    if (pid != 0) {
        socket_list_remove(list, ((ftp_cli_t *)cli->data)->data_chan);
        ((ftp_cli_t *)cli->data)->data_chan = NULL;
    }
    else {
        write(((ftp_cli_t *)cli->data)->data_chan->fd, "salut\r\n", 7);
        exit(0);
    }
}