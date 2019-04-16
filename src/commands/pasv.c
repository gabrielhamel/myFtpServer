/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** pasv
*/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "commands.h"
#include "responses.h"
#include "socket.h"
#include "myftp.h"

bool data_channel(socket_t *cli)
{
    if (((ftp_cli_t *)cli->data)->data_chan == NULL) {
        write(cli->fd, CODE_425, sizeof(CODE_425) - 1);
        return (false);
    }
    return (true);
}

void command_pasv(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    socket_t *tmp;

    (void)arg;
    (void)path;
    if (!user_connected(cli))
        return;
    if (((ftp_cli_t *)cli->data)->data_chan)
        socket_list_remove(list, ((ftp_cli_t *)cli->data)->data_chan);
    tmp = socket_server_create(0, init_serv_child, end_serv_child);
    ((ftp_cli_t *)cli->data)->data_chan = tmp;
    dprintf(cli->fd, CODE_227,
    cli->info.sin_addr.s_addr & 0xff,
    cli->info.sin_addr.s_addr >> 8 & 0xff,
    cli->info.sin_addr.s_addr >> 16 & 0xff,
    cli->info.sin_addr.s_addr >> 24 & 0xff,
    tmp->info.sin_port & 0xff,
    tmp->info.sin_port >> 8 & 0xff
    );
    printf("Listening on %d\n", ntohs(tmp->info.sin_port));
}