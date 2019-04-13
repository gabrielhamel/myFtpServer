/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** commands
*/

#ifndef COMMANDS_H
#define COMMANDS_H

#include "socket.h"

void command_quit(socket_t *cli, socket_list_t *list, char **arg, char *path);

#endif