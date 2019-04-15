/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** accept
*/

#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "commands.h"
#include <unistd.h>
#include "utils.h"
#include "responses.h"
#include "socket.h"
#include "myftp.h"

bool wait_child_client(socket_list_t *list, socket_t *serv)
{
    if (((ftp_cli_t *)serv->data)->data_chan->data == NULL) {
        ((ftp_cli_t *)serv->data)->data_chan->data =
        socket_server_accept_cli(((ftp_cli_t *)serv->data)->data_chan,
        init_cli_child, end_cli_child);
        if (((ftp_cli_t *)serv->data)->data_chan->data != NULL)
            socket_list_add(list, ((ftp_cli_t *)serv->data)->data_chan->data);
        else
            return (false);
    }
    return (true);
}