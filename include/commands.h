/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** commands
*/

#ifndef COMMANDS_H
#define COMMANDS_H

#include "socket.h"

bool user_connected(socket_t *cli);

void command_quit(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_user(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_pass(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_syst(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_pwd(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_type(socket_t *cli, socket_list_t *list, char **arg, char *path);

#endif