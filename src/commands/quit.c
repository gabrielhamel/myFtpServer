/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** quit
*/

#include "socket.h"

void command_quit(socket_t *cli, socket_list_t *list, char **arg, char *path)
{
    (void)arg;
    (void)path;
    socket_list_remove(list, cli);
}