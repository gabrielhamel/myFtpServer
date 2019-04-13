/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** myftp
*/

#ifndef MYFTP_H
#define MYFTP_H

#include <stdbool.h>
#include "socket.h"

#define DEFAULT_USER "Anonymous"

typedef struct ftp_cli_t {
} ftp_cli_t;

bool check_usage(int ac, const char **av);
char *read_line(socket_t *socket);
void launch_ftp(char *path, uint16_t port);
void manage_event(socket_list_t *list, socket_t **evt_socks, char *path);
void *init_client(const socket_t *cli);
void end_client(const socket_t *cli, void *data);
void *init_server(const socket_t *cli);
void end_server(const socket_t *cli, void *data);
bool user_is_valid(char *username, char *password);

#endif