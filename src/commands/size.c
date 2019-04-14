/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** size
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "responses.h"
#include "commands.h"
#include "socket.h"
#include "myftp.h"

void command_size(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    (void)arg;
    (void)path;
    (void)list;
    if (!user_connected(cli))
        return;
}