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
bool data_channel(socket_t *cli);
size_t commands_lenght(void);
pid_t duplicate(void);

void command_quit(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_user(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_pass(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_syst(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_pwd(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_type(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_noop(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_help(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_cdup(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_size(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_cwd(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_dele(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_pasv(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_list(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_stor(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_retr(socket_t *cli, socket_list_t *list, char **arg, char *path);
void command_port(socket_t *cli, socket_list_t *list, char **arg, char *path);

#endif